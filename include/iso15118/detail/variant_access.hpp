// SPDX-License-Identifier: Apache-2.0
// Copyright 2023 Pionix GmbH and Contributors to EVerest
#pragma once

#include <cassert>

#include <iso15118/message/variant.hpp>

#include "cb_exi.hpp"

//RDB add the ACDP datatypes to fix the issue with ConnectRes/Req and DisconnectRes/Req having the same xsd
#include <cbv2g/iso_20/iso20_ACDP_Datatypes.h>


namespace iso15118::message_20 {

struct VariantAccess {
    // input
    exi_bitstream_t input_stream;

    // output
    void*& data;
    iso15118::message_20::Type& type;
    iso15118::message_20::Variant::CustomDeleter& custom_deleter;
    std::string& error;

    template <typename MessageType, typename CbExiMessageType> void insert_type(const CbExiMessageType& in) {
        assert(data == nullptr);

        data = new MessageType;
        type = iso15118::message_20::TypeTrait<MessageType>::type;
        custom_deleter = [](void* ptr) { delete static_cast<MessageType*>(ptr); };

        convert(in, *static_cast<MessageType*>(data));
    };
};

template <typename CbExiMessageType> void insert_type(VariantAccess& va, const CbExiMessageType&);

} // namespace iso15118::message_20

// RDB fix for issue with ConnectRes/Req and DisconnectRes/Req having the same xsd
        //  The type of doc.ACDP_DisconnectRes is exactly the same as doc.ACDP_ConnectRes
        //     struct iso20_acdp_exiDocument {
        // union {
        //     struct iso20_acdp_ACDP_VehiclePositioningReqType ACDP_VehiclePositioningReq;
        //     struct iso20_acdp_ACDP_VehiclePositioningResType ACDP_VehiclePositioningRes;
        //     struct iso20_acdp_ACDP_ConnectReqType ACDP_ConnectReq;
        //     struct iso20_acdp_ACDP_ConnectResType ACDP_ConnectRes;
        //     struct iso20_acdp_ACDP_ConnectReqType ACDP_DisconnectReq;
        //     struct iso20_acdp_ACDP_ConnectResType ACDP_DisconnectRes;
        // This means that it is impossible to differentiate between the two based on the type (which is what this does)
        // e.g.
        // template <> void insert_type(VariantAccess& va, const struct iso20_acdp_ACDP_ConnectReqType& in) {
        //     va.insert_type<ACDP_DisconnectRequest>(in);
        // } is the same as:
        // template <> void insert_type(VariantAccess& va, const struct iso20_acdp_ACDP_ConnectReqType& in) {
        //     va.insert_type<ACDP_ConnectRequest>(in);
        // }
        // and we get a duplicate function error when trying to link. 

        // To fix this, create a new type called 
        //struct iso20_acdp_ACDP_DisconnectResType and copy everything to it and try again.  

struct iso20_acdp_ACDP_DisconnectReqType {
    // Header, MessageHeaderType
    struct iso20_acdp_MessageHeaderType Header;
    // EVElectricalChargingDeviceStatus, electricalChargingDeviceStatusType (base: string)
    iso20_acdp_electricalChargingDeviceStatusType EVElectricalChargingDeviceStatus;

};
