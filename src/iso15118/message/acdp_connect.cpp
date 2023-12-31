// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/message/acdp_connect.hpp>

#include <type_traits>

#include <iso15118/detail/variant_access.hpp>

#include <exi/cb/iso20_ACDP_Decoder.h>
#include <exi/cb/iso20_ACDP_Encoder.h>

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

char * generate_json_ACDP_ConnectReq()
{
    //create a stream for serializing
    uint8_t doc_raw[1024];

    exi_bitstream_t exi_stream_out;
    size_t pos1 = 0;
    int errn = 0;
    exi_bitstream_init(&exi_stream_out, reinterpret_cast<uint8_t*>(doc_raw), sizeof(doc_raw), pos1, nullptr);

    iso20_acdp_exiDocument doc;
    init_iso20_acdp_exiDocument(&doc);

    CB_SET_USED(doc.ACDP_ConnectReq);

    doc.ACDP_ConnectReq.EVElectricalChargingDeviceStatus=iso20_acdp_electricalChargingDeviceStatusType_State_B;
    encode_iso20_acdp_exiDocument(&exi_stream_out, &doc);

    //Convert to a string we can use in Josev
    static constexpr auto ESCAPED_BYTE_CHAR_COUNT = 4;
    auto payload_string_buffer = std::make_unique<char[]>(exi_stream_out.data_size * ESCAPED_BYTE_CHAR_COUNT + 1);
    int i;
    for (i = 0; i < exi_bitstream_get_length(&exi_stream_out); ++i) {
        snprintf(payload_string_buffer.get() + i * ESCAPED_BYTE_CHAR_COUNT, ESCAPED_BYTE_CHAR_COUNT + 1, "\\x%02hx",
                 exi_stream_out.data[i]);
    }
    errn=0;
    return NULL;
    
}

} // namespace iso15118::message_20
