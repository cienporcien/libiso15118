// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/message/acds_connect.hpp>

#include <type_traits>

#include <iso15118/detail/variant_access.hpp>

#include <exi/cb/iso20_ACDS_Decoder.h>
#include <exi/cb/iso20_ACDS_Encoder.h>

namespace iso15118::message_20 {

template <> void convert(const struct iso20_acds_ACDS_ConnectReqType& in, ACDS_ConnectRequest& out) {
    convert(in.Header, out.header);
    cb_convert_enum(in.EVElectricalChargingDeviceStatus,out.EVElectricalChargingDeviceStatus);
}

template <> void insert_type(VariantAccess& va, const struct iso20_acds_ACDS_ConnectReqType& in) {
    va.insert_type<ACDS_ConnectRequest>(in);
}

template <> void convert(const ACDS_ConnectResponse& in, struct iso20_acds_ACDS_ConnectResType& out) {
    init_iso20_acds_ACDS_ConnectResType(&out);
    convert(in.header, out.Header);
    cb_convert_enum(in.response_code, out.ResponseCode);
    cb_convert_enum(in.processing, out.EVSEProcessing);
    cb_convert_enum(in.EVSEElectricalChargingDeviceStatus,out.EVSEElectricalChargingDeviceStatus);
    cb_convert_enum(in.EVSEMechanicalChargingDeviceStatus,out.EVSEMechanicalChargingDeviceStatus);
}

template <> int serialize_to_exi(const ACDS_ConnectResponse& in, exi_bitstream_t& out) {
    iso20_acds_exiDocument doc;
    init_iso20_acds_exiDocument(&doc);

    CB_SET_USED(doc.ACDS_ConnectRes);

    convert(in, doc.ACDS_ConnectRes);

    return encode_iso20_acds_exiDocument(&out, &doc);
}

template <> size_t serialize(const ACDS_ConnectResponse& in, const io::StreamOutputView& out) {
    return serialize_helper(in, out);
}

} // namespace iso15118::message_20
