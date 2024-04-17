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
    out.ContactWindowXc = in.ContactWindowXc;
    out.ContactWindowYc = in.ContactWindowYc;
    out.EVInChargePosition = in.EVInChargePosition;
    out.EVRelativeXDeviation = in.EVRelativeXDeviation;
    out.EVRelativeYDeviation = in.EVRelativeYDeviation;
    out.EVSEPositioningSupport = in.EVSEPositioningSupport;
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

} // namespace iso15118::message_20
