// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/d20/state/dc_charge_loop.hpp>
#include <iso15118/d20/state/power_delivery.hpp>
#include <iso15118/d20/state/session_stop.hpp>

#include <iso15118/detail/d20/context_helper.hpp>
#include <iso15118/detail/d20/error.hpp>
#include <iso15118/detail/d20/state/dc_pre_charge.hpp>
#include <iso15118/detail/d20/state/power_delivery.hpp>
#include <iso15118/detail/helper.hpp>

namespace iso15118::d20::state {

message_20::PowerDeliveryResponse handle_request(const message_20::PowerDeliveryRequest& req,
                                                 const d20::Session& session) {

    message_20::PowerDeliveryResponse res;

    if (validate_and_setup_header(res.header, session, req.header.session_id) == false) {
        return response_with_code(res, message_20::ResponseCode::FAILED_UnknownSession);
    }

    // Todo(sl): Add standby feature and define as everest module config
    if (req.charge_progress == message_20::PowerDeliveryRequest::Progress::Standby) {
        return response_with_code(res, message_20::ResponseCode::WARNING_StandbyNotAllowed);
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void PowerDelivery::enter() {
    ctx.log.enter_state("PowerDelivery");
}

FsmSimpleState::HandleEventReturnType PowerDelivery::handle_event(AllocatorType& sa, FsmEvent ev) {

    if (ev == FsmEvent::CONTROL_MESSAGE) {
        const auto control_data = ctx.get_control_event<PresentVoltageCurrent>();
        if (not control_data) {
            // FIXME (aw): error handling
            return sa.HANDLED_INTERNALLY;
        }

        present_voltage = control_data->voltage;

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.get_request();

    if (const auto req = variant->get_if<message_20::DC_PreChargeRequest>()) {
        const auto [res, charge_target] = handle_request(*req, ctx.session, present_voltage);

        // FIXME (aw): should we always send this charge_target, even if the res errored?
        ctx.feedback.dc_charge_target(charge_target);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        return sa.HANDLED_INTERNALLY;
    } else if (const auto req = variant->get_if<message_20::PowerDeliveryRequest>()) {
        if (req->charge_progress == message_20::PowerDeliveryRequest::Progress::Start) {
            ctx.feedback.signal(session::feedback::Signal::SETUP_FINISHED);
        }

        const auto& res = handle_request(*req, ctx.session);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        return sa.create_simple<DC_ChargeLoop>(ctx);
    } else {
        ctx.log("Expected DC_PreChargeReq or PowerDeliveryReq! But code type id: %d", variant->get_type());

        // Sequence Error
        const message_20::Type req_type = variant->get_type();

        if (req_type == message_20::Type::SessionSetupReq) {
            const auto res = handle_sequence_error<message_20::SessionSetupResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::AuthorizationSetupReq) {
            const auto res = handle_sequence_error<message_20::AuthorizationSetupResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::AuthorizationReq) {
            const auto res = handle_sequence_error<message_20::AuthorizationResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::ServiceDiscoveryReq) {
            const auto res = handle_sequence_error<message_20::ServiceDiscoveryResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::ServiceDetailReq) {
            const auto res = handle_sequence_error<message_20::ServiceDetailResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::ServiceSelectionReq) {
            const auto res = handle_sequence_error<message_20::ServiceSelectionResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::DC_ChargeParameterDiscoveryReq) {
            const auto res = handle_sequence_error<message_20::DC_ChargeParameterDiscoveryResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::ScheduleExchangeReq) {
            const auto res = handle_sequence_error<message_20::ScheduleExchangeResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::DC_CableCheckReq) {
            const auto res = handle_sequence_error<message_20::DC_CableCheckResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::DC_ChargeLoopReq) {
            const auto res = handle_sequence_error<message_20::DC_ChargeLoopResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::DC_WeldingDetectionReq) {
            const auto res = handle_sequence_error<message_20::DC_WeldingDetectionResponse>(ctx.session);
            ctx.respond(res);
        } else if (req_type == message_20::Type::SessionStopReq) {
            const auto res = handle_sequence_error<message_20::SessionStopResponse>(ctx.session);
            ctx.respond(res);
        }

        ctx.session_stopped = true;
        return sa.PASS_ON;
    }
}

} // namespace iso15118::d20::state