// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/d20/state/acds_disconnect.hpp>
#include <iso15118/d20/state/session_stop.hpp>

#include <iso15118/detail/d20/context_helper.hpp>
#include <iso15118/detail/d20/state/acds_disconnect.hpp>
#include <iso15118/detail/helper.hpp>

namespace iso15118::d20::state {

message_20::ACDS_DisconnectResponse handle_request(const message_20::ACDS_DisconnectRequest& req,
                                                 const d20::Session& session, bool acds_disconnect_done) {

    message_20::ACDS_DisconnectResponse res;

    if (validate_and_setup_header(res.header, session, req.header.session_id) == false) {
        return response_with_code(res, message_20::ResponseCode::FAILED_UnknownSession);
    }

    if (!acds_disconnect_done) {
        res.processing = message_20::Processing::Ongoing;
    } else {
        res.processing = message_20::Processing::Finished;
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void ACDS_Disconnect::enter() {
    ctx.log.enter_state("ACDS_Disconnect");
}

FsmSimpleState::HandleEventReturnType ACDS_Disconnect::handle_event(AllocatorType& sa, FsmEvent ev) {

    if (ev == FsmEvent::CONTROL_MESSAGE) {
        const auto control_data = ctx.get_control_event<ACDSDisconnectFinished>();
        if (not control_data) {
            // FIXME (aw): error handling
            return sa.HANDLED_INTERNALLY;
        }

        acds_disconnect_done = *control_data;

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.get_request();

    if (const auto req = variant->get_if<message_20::ACDS_DisconnectRequest>()) {
        if (not acds_disconnect_initiated) {
            ctx.feedback.signal(session::feedback::Signal::START_ACDS_DISCONNECT);
            acds_disconnect_initiated = true;

            //RDB fix this correctly
            acds_disconnect_done = true;
        }

        const auto res = handle_request(*req, ctx.session, acds_disconnect_done);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        if (acds_disconnect_done) {
            return sa.create_simple<SessionStop>(ctx);
        } else {
            return sa.HANDLED_INTERNALLY;
        }
    } else {
        ctx.log("expected ACDS_DisconnectReq! But code type id: %d", variant->get_type());
        ctx.session_stopped = true;
        return sa.PASS_ON;
    }
}

} // namespace iso15118::d20::state
