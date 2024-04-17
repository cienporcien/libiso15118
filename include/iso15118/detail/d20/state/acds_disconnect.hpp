// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <iso15118/d20/session.hpp>
#include <iso15118/message/acds_disconnect.hpp>

namespace iso15118::d20::state {

message_20::ACDS_DisconnectResponse handle_request(const message_20::ACDS_DisconnectRequest& req,
                                                 const d20::Session& session, bool acds_disconnect_done);

} // namespace iso15118::d20::state
