// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/tbd_controller.hpp>

#include <algorithm>
#include <chrono>
#include <cstdio>

#include <iso15118/io/connection_plain.hpp>
#include <iso15118/io/connection_ssl.hpp>
#include <iso15118/io/ipv6_endpoint.hpp>
#include <iso15118/session/iso.hpp>

#include <iso15118/detail/helper.hpp>

namespace iso15118 {

TbdController::TbdController(TbdConfig config_, session::feedback::Callbacks callbacks_, d20::EvseSetupConfig setup_) :
    config(std::move(config_)), callbacks(std::move(callbacks_)), evse_setup(std::move(setup_)) {

    if (config.enable_sdp_server) {
        sdp_server = std::make_unique<io::SdpServer>();
        poll_manager.register_fd(sdp_server->get_fd(), [this]() { handle_sdp_server_input(); });
    }
}

void TbdController::loop() {
    static constexpr auto POLL_MANAGER_TIMEOUT_MS = 50;

    if (not config.enable_sdp_server) {
        auto connection = std::make_unique<io::ConnectionPlain>(poll_manager, config.interface_name);
        session =
            std::make_unique<Session>(std::move(connection), std::move(d20::SessionConfig(evse_setup)), callbacks);
    }

    auto next_event = get_current_time_point();

    while (true) {
        const auto poll_timeout_ms = get_timeout_ms_until(next_event, POLL_MANAGER_TIMEOUT_MS);
        poll_manager.poll(poll_timeout_ms);

        next_event = offset_time_point_by_ms(get_current_time_point(), POLL_MANAGER_TIMEOUT_MS);

        if (session) {
            const auto next_session_event = session->poll();
            next_event = std::min(next_event, next_session_event);
            if (session->is_finished()) {
                session.reset();

                if (not config.enable_sdp_server) {
                    auto connection = std::make_unique<io::ConnectionPlain>(poll_manager, config.interface_name);
                    session = std::make_unique<Session>(std::move(connection),
                                                        std::move(d20::SessionConfig(evse_setup)), callbacks);
                }
            }
        }
    }
}

void TbdController::send_control_event(const d20::ControlEvent& event) {
    if (session) {
        session->push_control_event(event);
    }
}

void TbdController::update_authorization_services(const std::vector<message_20::Authorization>& services,
                                                  bool cert_install_service) {

    evse_setup.enable_certificate_install_service = cert_install_service;

    if (services.empty()) {
        logf_warning("The authorization services are not updated because services are empty!");
        return;
    }
    evse_setup.authorization_services = services;
}

void TbdController::update_dc_limits(const d20::DcTransferLimits& limits) {

    evse_setup.dc_limits = limits;

    if (session) {
        session->push_control_event(limits);
    }
}

void TbdController::handle_sdp_server_input() {

    //RDB Check here if the interface is wireless, and handle SDP differently if so.
    char protocol[IFNAMSIZ]  = {0};
    bool IsWireless = false; //invert logic for testing on a wired if
    if(check_wireless(config.interface_name.c_str(),protocol) == 1){
        IsWireless = true;
    }  

    
    auto request = sdp_server.get_peer_request(IsWireless);

    if (not request) {
        return;
    }

    // RDB Here we get the PPD position, and see if the Pairing and Positioning Device (PPD) is within the Communications Pairing Space (CPS)
    // If so, we can continue as usual, if not we simply ignore this sdp request.
    if (Is_PPD_in_CPS) {
 

        switch (config.tls_negotiation_strategy) {
        case config::TlsNegotiationStrategy::ACCEPT_CLIENT_OFFER:
            // nothing to change
            break;
        case config::TlsNegotiationStrategy::ENFORCE_TLS:
            request.security = io::v2gtp::Security::TLS;
            break;
        case config::TlsNegotiationStrategy::ENFORCE_NO_TLS:
            request.security = io::v2gtp::Security::NO_TRANSPORT_SECURITY;
            break;
        }

        auto connection = [this](bool secure_connection) -> std::unique_ptr<io::IConnection> {
            if (secure_connection) {
                return std::make_unique<io::ConnectionSSL>(poll_manager, config.interface_name, config.ssl);
            } else {
                return std::make_unique<io::ConnectionPlain>(poll_manager, config.interface_name);
            }
        }(request.security == io::v2gtp::Security::TLS);

    session = std::make_unique<Session>(std::move(connection), std::move(d20::SessionConfig(evse_setup)), callbacks);
        const auto ipv6_endpoint = connection->get_public_endpoint();

        // Todo(sl): Check if session_config is empty
        const auto& new_session = sessions.emplace_back(std::move(connection), session_config, callbacks);

        sdp_server.send_response(request, ipv6_endpoint, IsWireless, true);
    }
    else{

        io::Ipv6EndPoint null_end_point;
        bzero(&null_end_point, sizeof(null_end_point));

        // Send an response with DiagStatus=Ongoing, this indicates to the vehicle that the PPD is not within the CPS
        // and communication cannot start. The vehicle will wait 250ms and try again.
        sdp_server.send_response(request, null_end_point, IsWireless, false);
    }
}


int TbdController::check_wireless(const char* ifname, char* protocol) {
  int sock = -1;
  struct iwreq pwrq;
  memset(&pwrq, 0, sizeof(pwrq));
  strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return 0;
  }

  if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
    if (protocol) strncpy(protocol, pwrq.u.name, IFNAMSIZ);
    close(sock);
    return 1;
  }

  close(sock);
  return 0;
}


} // namespace iso15118
