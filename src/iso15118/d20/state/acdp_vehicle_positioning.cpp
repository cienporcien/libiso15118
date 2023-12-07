// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/d20/state/acdp_vehicle_positioning.hpp>
#include <iso15118/d20/state/authorization_setup.hpp>

#include <iso15118/detail/d20/context_helper.hpp>
#include <iso15118/detail/d20/state/acdp_vehicle_positioning.hpp>
#include <iso15118/detail/helper.hpp>

namespace iso15118::d20::state {

message_20::ACDP_VehiclePositioningResponse handle_request(const message_20::ACDP_VehiclePositioningRequest& req,
                                                 const d20::Session& session, bool vehicle_positioning_done) {

    message_20::ACDP_VehiclePositioningResponse res;

    if (validate_and_setup_header(res.header, session, req.header.session_id) == false) {
        return response_with_code(res, message_20::ResponseCode::FAILED_UnknownSession);
    }

    if (vehicle_positioning_done) {
        res.processing = message_20::Processing::Ongoing;
    } else {
        res.processing = message_20::Processing::Finished;
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void ACDP_VehiclePositioning::enter() {
    ctx.log.enter_state("ACDP_VehiclePositioning");
}

FsmSimpleState::HandleEventReturnType ACDP_VehiclePositioning::handle_event(AllocatorType& sa, FsmEvent ev) {

    if (ev == FsmEvent::CONTROL_MESSAGE) {
        const auto control_data = ctx.get_control_event<VehiclePositioningFinished>();
        if (not control_data) {
            // FIXME (aw): error handling
            return sa.HANDLED_INTERNALLY;
        }

        vehicle_positioning_done = *control_data;

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.get_request();

    if (const auto req = variant->get_if<message_20::ACDP_VehiclePositioningRequest>()) {
        if (not vehicle_positioning_initiated) {
            ctx.feedback.signal(session::feedback::Signal::START_VEHICLE_POSITIONING);
            vehicle_positioning_initiated = true;
        }

        const auto res = handle_request(*req, ctx.session, vehicle_positioning_done);

        ctx.respond(res);

        if (res.response_code >= message_20::ResponseCode::FAILED) {
            ctx.session_stopped = true;
            return sa.PASS_ON;
        }

        if (vehicle_positioning_done) {
            return sa.create_simple<AuthorizationSetup>(ctx);
        } else {
            return sa.HANDLED_INTERNALLY;
        }
    } else {
        ctx.log("expected ACDP_VehiclePositioningReq! But code type id: %d", variant->get_type());
        ctx.session_stopped = true;
        return sa.PASS_ON;
    }
}

} // namespace iso15118::d20::state
