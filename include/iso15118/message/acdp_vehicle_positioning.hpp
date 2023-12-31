// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include "common.hpp"

namespace iso15118::message_20 {

//hack to get a json string for JOSEV
char * generate_json_ACDP_VehiclePositioningReq();


struct ACDP_VehiclePositioningRequest {
    Header header;
    // EVMobilityStatus, boolean
    int EVMobilityStatus;
    // EVPositioningSupport, boolean
    int EVPositioningSupport;
};

struct ACDP_VehiclePositioningResponse {

    ACDP_VehiclePositioningResponse() : processing(Processing::Ongoing){};

    Header header;
    ResponseCode response_code;

    Processing processing;
    int EVSEPositioningSupport;
    // EVRelativeXDeviation, short (base: int)
    int16_t EVRelativeXDeviation;
    // EVRelativeYDeviation, short (base: int)
    int16_t EVRelativeYDeviation;
    // ContactWindowXc, short (base: int)
    int16_t ContactWindowXc;
    // ContactWindowYc, short (base: int)
    int16_t ContactWindowYc;
    // EVInChargePosition, boolean
    int EVInChargePosition;
};

} // namespace iso15118::message_20
