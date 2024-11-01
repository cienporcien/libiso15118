// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/message/acdp_connect.hpp>

#include <type_traits>

#include <iso15118/detail/variant_access.hpp>

#include <cbv2g/iso_20/iso20_ACDP_Decoder.h>
#include <cbv2g/iso_20/iso20_ACDP_Encoder.h>

namespace iso15118::message_20 {

template <> void convert(const struct iso20_acdp_ACDP_ConnectReqType& in, ACDP_ConnectRequest& out) {
    convert(in.Header, out.header);
    cb_convert_enum(in.EVElectricalChargingDeviceStatus,out.EVElectricalChargingDeviceStatus);
}

template <> void insert_type(VariantAccess& va, const struct iso20_acdp_ACDP_ConnectReqType& in) {
    va.insert_type<ACDP_ConnectRequest>(in);
}

template <> void convert(const ACDP_ConnectResponse& in, struct iso20_acdp_ACDP_ConnectResType& out) {
    init_iso20_acdp_ACDP_ConnectResType(&out);
    convert(in.header, out.Header);
    cb_convert_enum(in.response_code, out.ResponseCode);
    cb_convert_enum(in.processing, out.EVSEProcessing);
    cb_convert_enum(in.EVSEElectricalChargingDeviceStatus,out.EVSEElectricalChargingDeviceStatus);
    cb_convert_enum(in.EVSEMechanicalChargingDeviceStatus,out.EVSEMechanicalChargingDeviceStatus);
}

template <> int serialize_to_exi(const ACDP_ConnectResponse& in, exi_bitstream_t& out) {
    iso20_acdp_exiDocument doc;
    init_iso20_acdp_exiDocument(&doc);

    CB_SET_USED(doc.ACDP_ConnectRes);

    convert(in, doc.ACDP_ConnectRes);

    return encode_iso20_acdp_exiDocument(&out, &doc);
}

template <> size_t serialize(const ACDP_ConnectResponse& in, const io::StreamOutputView& out) {
    return serialize_helper(in, out);
}

} // namespace iso15118::message_20
