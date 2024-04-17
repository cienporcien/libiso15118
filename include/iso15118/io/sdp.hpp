// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <cstdint>

namespace iso15118::io::v2gtp {
enum class Security : uint8_t {
    TLS = 0x00,
    NO_TRANSPORT_SECURITY = 0x10,
};

enum class TransportProtocol : uint8_t {
    TCP = 0x00,
    RESERVED_FOR_UDP = 0x10,
};

static constexpr auto SDP_SERVER_PORT = 15118;

enum class PayloadType : uint16_t {
    SAP = 0x8001,
    Part20Main = 0x8002,
    Part20AC = 0x8003,
    Part20DC = 0x8004,
    Part20ACDS = 0x8005,
};

//RDB Add information for SDP for Wireless
enum class P2PS_PPD : uint16_t {
    PPD_on_Infrastructure = 0x0001,
    PPD_on_EV = 0x0002,
    WPT_LF_on_Infrastructure = 0x0004,
    WPT_LF_on_EV = 0x0008,
    WPT_Cam_on_EV = 0x0010,
    ACD_U_Infrared = 0x0020,
    ACD_directed_WLAN = 0x0040,
};

enum class CouplingType : uint8_t {
    EN50696_Annex_A_2_Inverted_Pantograph_Cross = 0x00,
    EN50696_Annex_A_3_Inverted_Pantograph_Inline = 0x01,
    EN50696_Annex_A_4_Inverted_Pantograph_Dome = 0x02,
    EN50696_Annex_B_EV_Mounted_Pantograph = 0x03,
    EN50696_Annex_C_Underbody = 0x04,
    EN50696_Annex_D_SideLoading = 0x05,
    IEC61980_WPT = 0x06,
    IEC61851_26_Infrastructure_Mounted = 0x07,
    IEC61851_26_EV_Mounted = 0x08,
    IEC61851_27_ACDS = 0x07,
    Conductive_Manual = 0x08,
    Not_Applicable = 0xFF,
};

enum class DiagStatus : uint8_t {
    ongoing = 0x00,
    finished_with_EVSEID = 0x01,
    finished_without_EVSEID = 0x02,
    Error_no_SECC = 0x10,
};

} // namespace iso15118::io::v2gtp
