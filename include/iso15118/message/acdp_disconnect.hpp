// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include "common.hpp"
#include "acdp_connect.hpp"

namespace iso15118::message_20 {


struct ACDP_DisconnectRequest {
    Header header;
    electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus;
};


struct ACDP_DisconnectResponse {

    ACDP_DisconnectResponse() : processing(Processing::Ongoing){};

    Header header;
    ResponseCode response_code;
    Processing processing;
    electricalChargingDeviceStatusType EVSEElectricalChargingDeviceStatus;
    mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus;

};

} // namespace iso15118::message_20
