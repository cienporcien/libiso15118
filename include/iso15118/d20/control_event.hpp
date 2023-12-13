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

using ControlEvent = std::variant<CableCheckFinished, PresentVoltageCurrent, AuthorizationResponse, VehiclePositioningFinished, ACDPConnectFinished, ACDPDisconnectFinished>;

} // namespace iso15118::d20
