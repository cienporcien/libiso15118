// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/d20/state/acdp_connect.hpp>
#include <iso15118/d20/state/dc_cable_check.hpp>

#include <iso15118/detail/d20/context_helper.hpp>
#include <iso15118/detail/d20/state/acdp_connect.hpp>
#include <iso15118/detail/helper.hpp>

namespace iso15118::d20::state {

message_20::ACDP_ConnectResponse handle_request(const message_20::ACDP_ConnectRequest& req,
                                                 const d20::Session& session, bool acdp_connect_done) {

    message_20::ACDP_ConnectResponse res;

    if (validate_and_setup_header(res.header, session, req.header.session_id) == false) {
        return response_with_code(res, message_20::ResponseCode::FAILED_UnknownSession);
    }

    if (!acdp_connect_done) {
        res.processing = message_20::Processing::Ongoing;
    } else {
        res.processing = message_20::Processing::Finished;
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void ACDP_Connect::enter() {
    ctx.log.enter_state("ACDP_Connect");
}

FsmSimpleState::HandleEventReturnType ACDP_Connect::handle_event(AllocatorType& sa, FsmEvent ev) {

    if (ev == FsmEvent::CONTROL_MESSAGE) {
        const auto control_data = ctx.get_control_event<ACDPConnectFinished>();
        if (not control_data) {
            // FIXME (aw): error handling
            return sa.HANDLED_INTERNALLY;
        }

        acdp_connect_done = *control_data;

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.get_request();

    if (const auto req = variant->get_if<message_20::ACDP_ConnectRequest>()) {
        if (not acdp_connect_initiated) {
            ctx.feedback.signal(session::feedback::Signal::START_ACDP_CONNECT);
            acdp_connect_initiated = true;

            //RDB fix this correctly
            acdp_connect_done = true;

        }

        const auto res = handle_request(*req, ctx.session, acdp_connect_done);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        if (acdp_connect_done) {
            return sa.create_simple<DC_CableCheck>(ctx);
        } else {
            return sa.HANDLED_INTERNALLY;
        }
    } else {
        ctx.log("expected ACDP_ConnectReq! But code type id: %d", variant->get_type());
        ctx.session_stopped = true;
        return sa.PASS_ON;
    }
}

} // namespace iso15118::d20::state
