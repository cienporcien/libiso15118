// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/d20/state/acdp_disconnect.hpp>
#include <iso15118/d20/state/session_stop.hpp>

#include <iso15118/detail/d20/context_helper.hpp>
#include <iso15118/detail/d20/state/acdp_disconnect.hpp>
#include <iso15118/detail/helper.hpp>

namespace iso15118::d20::state {

message_20::ACDP_DisconnectResponse handle_request(const message_20::ACDP_DisconnectRequest& req,
                                                 const d20::Session& session, bool acdp_disconnect_done) {

    message_20::ACDP_DisconnectResponse res;

    if (validate_and_setup_header(res.header, session, req.header.session_id) == false) {
        return response_with_code(res, message_20::ResponseCode::FAILED_UnknownSession);
    }

    if (!acdp_disconnect_done) {
        res.processing = message_20::Processing::Ongoing;
    } else {
        res.processing = message_20::Processing::Finished;
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void ACDP_Disconnect::enter() {
    ctx.log.enter_state("ACDP_Disconnect");
}

FsmSimpleState::HandleEventReturnType ACDP_Disconnect::handle_event(AllocatorType& sa, FsmEvent ev) {

    if (ev == FsmEvent::CONTROL_MESSAGE) {
        const auto control_data = ctx.get_control_event<ACDPDisconnectFinished>();
        if (not control_data) {
            // FIXME (aw): error handling
            return sa.HANDLED_INTERNALLY;
        }

        acdp_disconnect_done = *control_data;

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.get_request();

    if (const auto req = variant->get_if<message_20::ACDP_DisconnectRequest>()) {
        if (not acdp_disconnect_initiated) {
            ctx.feedback.signal(session::feedback::Signal::START_ACDP_DISCONNECT);
            acdp_disconnect_initiated = true;

            //RDB fix this correctly
            acdp_disconnect_done = true;
        }

        const auto res = handle_request(*req, ctx.session, acdp_disconnect_done);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        if (acdp_disconnect_done) {
            return sa.create_simple<SessionStop>(ctx);
        } else {
            return sa.HANDLED_INTERNALLY;
        }
    } else {
        ctx.log("expected ACDP_DisconnectReq! But code type id: %d", variant->get_type());
        ctx.session_stopped = true;
        return sa.PASS_ON;
    }
}

} // namespace iso15118::d20::state
