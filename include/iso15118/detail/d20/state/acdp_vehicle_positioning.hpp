// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <iso15118/d20/session.hpp>
#include <iso15118/message/acdp_vehicle_positioning.hpp>

namespace iso15118::d20::state {

message_20::ACDP_VehiclePositioningResponse handle_request(const message_20::ACDP_VehiclePositioningRequest& req,
                                                 const d20::Session& session, bool vehicle_positioning_done);

} // namespace iso15118::d20::state
