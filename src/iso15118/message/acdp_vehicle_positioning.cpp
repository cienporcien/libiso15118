// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#include <iso15118/message/acdp_vehicle_positioning.hpp>

#include <type_traits>

#include <iso15118/detail/variant_access.hpp>

#include <exi/cb/iso20_ACDP_Decoder.h>
#include <exi/cb/iso20_ACDP_Encoder.h>

namespace iso15118::message_20 {

template <> void convert(const struct iso20_acdp_ACDP_VehiclePositioningReqType& in, ACDP_VehiclePositioningRequest& out) {
    convert(in.Header, out.header);
    out.EVMobilityStatus=in.EVMobilityStatus;
    out.EVPositioningSupport=in.EVPositioningSupport;
}

template <> void insert_type(VariantAccess& va, const struct iso20_acdp_ACDP_VehiclePositioningReqType& in) {
    va.insert_type<ACDP_VehiclePositioningRequest>(in);
}

template <> void convert(const ACDP_VehiclePositioningResponse& in, struct iso20_acdp_ACDP_VehiclePositioningResType& out) {
    init_iso20_acdp_ACDP_VehiclePositioningResType(&out);
    convert(in.header, out.Header);
    cb_convert_enum(in.response_code, out.ResponseCode);
    cb_convert_enum(in.processing, out.EVSEProcessing);
}

template <> int serialize_to_exi(const ACDP_VehiclePositioningResponse& in, exi_bitstream_t& out) {
    iso20_acdp_exiDocument doc;
    init_iso20_acdp_exiDocument(&doc);

    CB_SET_USED(doc.ACDP_VehiclePositioningRes);

    convert(in, doc.ACDP_VehiclePositioningRes);

    return encode_iso20_acdp_exiDocument(&out, &doc);
}

template <> size_t serialize(const ACDP_VehiclePositioningResponse& in, const io::StreamOutputView& out) {
    return serialize_helper(in, out);
}

char * generate_json_ACDP_VehiclePositioningReq()
{
    //create a stream for serializing
    uint8_t doc_raw[1024];

    exi_bitstream_t exi_stream_out;
    size_t pos1 = 0;
    int errn = 0;
    exi_bitstream_init(&exi_stream_out, reinterpret_cast<uint8_t*>(doc_raw), sizeof(doc_raw), pos1, nullptr);

    iso20_acdp_exiDocument doc;
    init_iso20_acdp_exiDocument(&doc);

    CB_SET_USED(doc.ACDP_VehiclePositioningReq);
    doc.ACDP_VehiclePositioningReq.EVMobilityStatus=true;
    doc.ACDP_VehiclePositioningReq.EVPositioningSupport=false;
    encode_iso20_acdp_exiDocument(&exi_stream_out, &doc);

    //Convert to a string we can use in Josev
    static constexpr auto ESCAPED_BYTE_CHAR_COUNT = 5;
    auto payload_string_buffer = std::make_unique<char[]>(exi_stream_out.data_size * ESCAPED_BYTE_CHAR_COUNT + 1);
    int i;
    for (i = 0; i < exi_bitstream_get_length(&exi_stream_out); ++i) {
        snprintf(payload_string_buffer.get() + i * ESCAPED_BYTE_CHAR_COUNT, ESCAPED_BYTE_CHAR_COUNT + 1, ",0x%02hx",
                 exi_stream_out.data[i]);
    }
    errn=0;
    return NULL;
    
}



} // namespace iso15118::message_20
