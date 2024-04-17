// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <variant>

namespace iso15118::d20 {
class CableCheckFinished {
public:
    explicit CableCheckFinished(bool success_) : success(success_) {
    }

    operator bool() const {
        return success;
    }

private:
    bool success;
};

struct PresentVoltageCurrent {
    float voltage;
    float current;
};

class AuthorizationResponse {
public:
    explicit AuthorizationResponse(bool authorized_) : authorized(authorized_) {
    }

    operator bool() const {
        return authorized;
    }

private:
    bool authorized;
};

class StopCharging {
public:
    explicit StopCharging(bool stop_) : stop(stop_) {
    }

    operator bool() const {
        return stop;
    }

private:
    bool stop;
};

struct PresentVehiclePosition {
    bool evse_positioning_support;
    short ev_relative_x_deviation;
    short ev_relative_y_deviation;
    short contact_window_xc;
    short contact_window_yc;
    bool ev_in_charge_position;
    //short ev_relative_Z_deviation;  //need the Z to indicate whether the reading is good.
};


class VehiclePositioningFinished {
public:
    explicit VehiclePositioningFinished(bool success_) : success(success_) {
    }

    operator bool() const {
        return success;
    }

private:
    bool success;
};

class ACDPConnectFinished {
public:
    explicit ACDPConnectFinished(bool success_) : success(success_) {
    }

    operator bool() const {
        return success;
    }

private:
    bool success;
};

class ACDPDisconnectFinished {
public:
    explicit ACDPDisconnectFinished(bool success_) : success(success_) {
    }

    operator bool() const {
        return success;
    }

private:
    bool success;
};

using ControlEvent = std::variant<CableCheckFinished, PresentVoltageCurrent, AuthorizationResponse, StopCharging, PresentVehiclePosition, VehiclePositioningFinished, ACDPConnectFinished, ACDPDisconnectFinished>;

} // namespace iso15118::d20
