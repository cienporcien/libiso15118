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

    //Add the PPD Position information to the response
//    res.EVRelativeXDeviation = 
//    res.EVRelativeXDeviation = 


    if (vehicle_positioning_done) {
        res.processing = message_20::Processing::Finished;
    } else {
        res.processing = message_20::Processing::Ongoing;
    }

    return response_with_code(res, message_20::ResponseCode::OK);
}

void ACDP_VehiclePositioning::enter() {
    ctx.log.enter_state("ACDP_VehiclePositioning");
}

FsmSimpleState::HandleEventReturnType ACDP_VehiclePositioning::handle_event(AllocatorType& sa, FsmEvent ev) {

    // It looks like we need to receive more information about the PPD position here...
    if (ev == FsmEvent::CONTROL_MESSAGE) {

        if (const auto control_data = ctx.get_control_event<PresentVehiclePosition>()) {
            ev_relative_x_deviation = control_data->ev_relative_x_deviation;
            ev_relative_y_deviation = control_data->ev_relative_y_deviation;
            contact_window_xc = control_data->contact_window_xc;
            contact_window_yc = control_data->contact_window_yc;
            evse_positioning_support = control_data->evse_positioning_support;
            ev_in_charge_position = control_data->ev_in_charge_position;
        } else {
            // FIXME (aw): error handling
        }

        return sa.HANDLED_INTERNALLY;
    }

    if (ev != FsmEvent::V2GTP_MESSAGE) {
        return sa.PASS_ON;
    }

    const auto variant = ctx.pull_request();

    if (const auto req = variant->get_if<message_20::ACDP_VehiclePositioningRequest>()) {
        if (not vehicle_positioning_initiated) {
            ctx.feedback.signal(session::feedback::Signal::START_VEHICLE_POSITIONING);
            vehicle_positioning_initiated = true;

            //RDB TODO fix this up to work properly.
            vehicle_positioning_done=false;
        }

        //The vehicle decides when it is in position by setting EVMobilityStatus to true when in position.
        // or, the vehicle can override the evse by sending EVPositioningSupport=true and EVMobilityStatus=true
        if (req->EVMobilityStatus == true && ev_in_charge_position == true){
            vehicle_positioning_done = true;
        }

        if (req->EVMobilityStatus == true && req->EVPositioningSupport == true){
            vehicle_positioning_done = true;
        }

        auto res = handle_request(*req, ctx.session, vehicle_positioning_done);

        //Easier to access the data here than passing everything to the handle_request...
        res.ContactWindowXc = contact_window_xc;
        res.ContactWindowYc = contact_window_yc;
        res.EVRelativeXDeviation = ev_relative_x_deviation;
        res.EVRelativeYDeviation = ev_relative_y_deviation;
        res.EVSEPositioningSupport = evse_positioning_support;
        res.EVInChargePosition = ev_in_charge_position;
 
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
