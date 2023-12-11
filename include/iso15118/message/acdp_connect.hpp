// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include "common.hpp"

namespace iso15118::message_20 {

typedef enum {
    electricalChargingDeviceStatusType_State_A = 0,
    electricalChargingDeviceStatusType_State_B = 1,
    electricalChargingDeviceStatusType_State_C = 2,
    electricalChargingDeviceStatusType_State_D = 3
} electricalChargingDeviceStatusType;

typedef enum {
    mechanicalChargingDeviceStatusType_Home = 0,
    mechanicalChargingDeviceStatusType_Moving = 1,
    mechanicalChargingDeviceStatusType_EndPosition = 2
} mechanicalChargingDeviceStatusType;


struct ACDP_ConnectRequest {
    Header header;
    electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus;
};



struct ACDP_ConnectResponse {

    ACDP_ConnectResponse() : processing(Processing::Ongoing){};

    Header header;
    ResponseCode response_code;
    Processing processing;
    electricalChargingDeviceStatusType EVSEElectricalChargingDeviceStatus;
    mechanicalChargingDeviceStatusType EVSEMechanicalChargingDeviceStatus;

};

} // namespace iso15118::message_20
