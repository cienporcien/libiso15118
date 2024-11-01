// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <iso15118/d20/session.hpp>
#include <iso15118/message/acdp_connect.hpp>

namespace iso15118::d20::state {

message_20::ACDP_ConnectResponse handle_request(const message_20::ACDP_ConnectRequest& req,
                                                 const d20::Session& session, bool acdp_connect_done);

} // namespace iso15118::d20::state
