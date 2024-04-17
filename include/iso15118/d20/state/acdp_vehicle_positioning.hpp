// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include "../fsm.hpp"

namespace iso15118::d20::state {

struct ACDP_VehiclePositioning : public FsmSimpleState {
    using FsmSimpleState::FsmSimpleState;

    void enter() final;

    HandleEventReturnType handle_event(AllocatorType&, FsmEvent) final;

private:
    bool vehicle_positioning_initiated{false};
    bool vehicle_positioning_done{false};

    bool evse_positioning_support{false};
    short ev_relative_x_deviation{0};
    short ev_relative_y_deviation{0};
    short contact_window_xc{0};
    short contact_window_yc{0};
    bool ev_in_charge_position{0};

};

} // namespace iso15118::d20::state
