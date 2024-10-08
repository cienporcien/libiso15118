// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/session/feedback.hpp>

#include <iso15118/detail/helper.hpp>

namespace iso15118::session {

Feedback::Feedback(feedback::Callbacks callbacks_) : callbacks(std::move(callbacks_)) {
}

void Feedback::signal(feedback::Signal signal) const {
    call_if_available(callbacks.signal, signal);
}

void Feedback::dc_charge_target(const feedback::DcChargeTarget& charge_target) const {
    call_if_available(callbacks.dc_charge_target, charge_target);
}

void Feedback::dc_max_limits(const feedback::DcMaximumLimits& max_limits) const {
    call_if_available(callbacks.dc_max_limits, max_limits);
}

void Feedback::v2g_message(const message_20::Type& v2g_message) const {
    call_if_available(callbacks.v2g_message, v2g_message);
}

void Feedback::evcc_id(const std::string& evccid) const {
    call_if_available(callbacks.evccid, evccid);
}

void Feedback::selected_protocol(const std::string& selected_protocol_) const {
    call_if_available(callbacks.selected_protocol, selected_protocol_);
}

void Feedback::display_parameters(const feedback::DisplayParameters& display_parameters_) const {
    call_if_available(callbacks.display_parameters, display_parameters_);
}

} // namespace iso15118::session
