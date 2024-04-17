/* SPDX-License-Identifier: Apache-2.0 */
/*
 * Copyright (C) 2022 - 2023 chargebyte GmbH
 * Copyright (C) 2022 - 2023 Contributors to EVerest
 */

/*****************************************************
 *
 * @author
 * @version
 *
 * The Code is generated! Changes may be overwritten.
 *
 *****************************************************/

/**
  * @file iso20_ACDS_Datatypes.c
  * @brief Description goes here
  *
  **/
#include "iso20_ACDS_Datatypes.h"



// root elements of EXI doc
void init_iso20_acds_exiDocument(struct iso20_acds_exiDocument* exiDoc) {
    exiDoc->ACDS_VehiclePositioningReq_isUsed = 0u;
    exiDoc->ACDS_VehiclePositioningRes_isUsed = 0u;
    exiDoc->ACDS_ConnectReq_isUsed = 0u;
    exiDoc->ACDS_ConnectRes_isUsed = 0u;
    exiDoc->ACDS_DisconnectReq_isUsed = 0u;
    exiDoc->ACDS_DisconnectRes_isUsed = 0u;
    exiDoc->ACDS_SystemStatusReq_isUsed = 0u;
    exiDoc->ACDS_SystemStatusRes_isUsed = 0u;
    exiDoc->CLReqControlMode_isUsed = 0u;
    exiDoc->CLResControlMode_isUsed = 0u;
    exiDoc->Signature_isUsed = 0u;
    exiDoc->SignatureValue_isUsed = 0u;
    exiDoc->SignedInfo_isUsed = 0u;
    exiDoc->CanonicalizationMethod_isUsed = 0u;
    exiDoc->SignatureMethod_isUsed = 0u;
    exiDoc->Reference_isUsed = 0u;
    exiDoc->Transforms_isUsed = 0u;
    exiDoc->Transform_isUsed = 0u;
    exiDoc->DigestMethod_isUsed = 0u;
    exiDoc->KeyInfo_isUsed = 0u;
    exiDoc->KeyValue_isUsed = 0u;
    exiDoc->RetrievalMethod_isUsed = 0u;
    exiDoc->X509Data_isUsed = 0u;
    exiDoc->PGPData_isUsed = 0u;
    exiDoc->SPKIData_isUsed = 0u;
    exiDoc->Object_isUsed = 0u;
    exiDoc->Manifest_isUsed = 0u;
    exiDoc->SignatureProperties_isUsed = 0u;
    exiDoc->SignatureProperty_isUsed = 0u;
    exiDoc->DSAKeyValue_isUsed = 0u;
    exiDoc->RSAKeyValue_isUsed = 0u;
}
void init_iso20_acds_TransformType(struct iso20_acds_TransformType* TransformType) {
    TransformType->ANY_isUsed = 0u;
    TransformType->XPath_isUsed = 0u;
}

void init_iso20_acds_TransformsType(struct iso20_acds_TransformsType* TransformsType) {
    (void) TransformsType;
}

void init_iso20_acds_DSAKeyValueType(struct iso20_acds_DSAKeyValueType* DSAKeyValueType) {
    DSAKeyValueType->P_isUsed = 0u;
    DSAKeyValueType->Q_isUsed = 0u;
    DSAKeyValueType->G_isUsed = 0u;
    DSAKeyValueType->J_isUsed = 0u;
    DSAKeyValueType->Seed_isUsed = 0u;
    DSAKeyValueType->PgenCounter_isUsed = 0u;
}

void init_iso20_acds_X509IssuerSerialType(struct iso20_acds_X509IssuerSerialType* X509IssuerSerialType) {
    (void) X509IssuerSerialType;
}

void init_iso20_acds_DigestMethodType(struct iso20_acds_DigestMethodType* DigestMethodType) {
    DigestMethodType->ANY_isUsed = 0u;
}

void init_iso20_acds_RSAKeyValueType(struct iso20_acds_RSAKeyValueType* RSAKeyValueType) {
    (void) RSAKeyValueType;
}

void init_iso20_acds_CanonicalizationMethodType(struct iso20_acds_CanonicalizationMethodType* CanonicalizationMethodType) {
    CanonicalizationMethodType->ANY_isUsed = 0u;
}

void init_iso20_acds_SignatureMethodType(struct iso20_acds_SignatureMethodType* SignatureMethodType) {
    SignatureMethodType->HMACOutputLength_isUsed = 0u;
    SignatureMethodType->ANY_isUsed = 0u;
}

void init_iso20_acds_KeyValueType(struct iso20_acds_KeyValueType* KeyValueType) {
    KeyValueType->DSAKeyValue_isUsed = 0u;
    KeyValueType->RSAKeyValue_isUsed = 0u;
    KeyValueType->ANY_isUsed = 0u;
}

void init_iso20_acds_ReferenceType(struct iso20_acds_ReferenceType* ReferenceType) {
    ReferenceType->Id_isUsed = 0u;
    ReferenceType->Type_isUsed = 0u;
    ReferenceType->URI_isUsed = 0u;
    ReferenceType->Transforms_isUsed = 0u;
}

void init_iso20_acds_RetrievalMethodType(struct iso20_acds_RetrievalMethodType* RetrievalMethodType) {
    RetrievalMethodType->Type_isUsed = 0u;
    RetrievalMethodType->URI_isUsed = 0u;
    RetrievalMethodType->Transforms_isUsed = 0u;
}

void init_iso20_acds_X509DataType(struct iso20_acds_X509DataType* X509DataType) {
    X509DataType->X509IssuerSerial_isUsed = 0u;
    X509DataType->X509SKI_isUsed = 0u;
    X509DataType->X509SubjectName_isUsed = 0u;
    X509DataType->X509Certificate_isUsed = 0u;
    X509DataType->X509CRL_isUsed = 0u;
    X509DataType->ANY_isUsed = 0u;
}

void init_iso20_acds_PGPDataType(struct iso20_acds_PGPDataType* PGPDataType) {
    PGPDataType->choice_1_isUsed = 0u;
    PGPDataType->choice_2_isUsed = 0u;
}

void init_iso20_acds_SPKIDataType(struct iso20_acds_SPKIDataType* SPKIDataType) {
    SPKIDataType->ANY_isUsed = 0u;
}

void init_iso20_acds_SignedInfoType(struct iso20_acds_SignedInfoType* SignedInfoType) {
    SignedInfoType->Reference.arrayLen = 0u;
    SignedInfoType->Id_isUsed = 0u;
}

void init_iso20_acds_SignatureValueType(struct iso20_acds_SignatureValueType* SignatureValueType) {
    SignatureValueType->Id_isUsed = 0u;
}

void init_iso20_acds_KeyInfoType(struct iso20_acds_KeyInfoType* KeyInfoType) {
    KeyInfoType->Id_isUsed = 0u;
    KeyInfoType->KeyName_isUsed = 0u;
    KeyInfoType->KeyValue_isUsed = 0u;
    KeyInfoType->RetrievalMethod_isUsed = 0u;
    KeyInfoType->X509Data_isUsed = 0u;
    KeyInfoType->PGPData_isUsed = 0u;
    KeyInfoType->SPKIData_isUsed = 0u;
    KeyInfoType->MgmtData_isUsed = 0u;
    KeyInfoType->ANY_isUsed = 0u;
}

void init_iso20_acds_ObjectType(struct iso20_acds_ObjectType* ObjectType) {
    ObjectType->Encoding_isUsed = 0u;
    ObjectType->Id_isUsed = 0u;
    ObjectType->MimeType_isUsed = 0u;
    ObjectType->ANY_isUsed = 0u;
}

void init_iso20_acds_SignatureType(struct iso20_acds_SignatureType* SignatureType) {
    SignatureType->Id_isUsed = 0u;
    SignatureType->KeyInfo_isUsed = 0u;
    SignatureType->Object_isUsed = 0u;
}

void init_iso20_acds_RationalNumberType(struct iso20_acds_RationalNumberType* RationalNumberType) {
    (void) RationalNumberType;
}

void init_iso20_acds_MessageHeaderType(struct iso20_acds_MessageHeaderType* MessageHeaderType) {
    MessageHeaderType->Signature_isUsed = 0u;
}

void init_iso20_acds_SignaturePropertyType(struct iso20_acds_SignaturePropertyType* SignaturePropertyType) {
    SignaturePropertyType->Id_isUsed = 0u;
    SignaturePropertyType->ANY_isUsed = 0u;
}

void init_iso20_acds_EVTechnicalStatusType(struct iso20_acds_EVTechnicalStatusType* EVTechnicalStatusType) {
    EVTechnicalStatusType->EVImmobilized_isUsed = 0u;
    EVTechnicalStatusType->EVUWBStrength_isUsed = 0u;
    EVTechnicalStatusType->EVCPStatus_isUsed = 0u;
    EVTechnicalStatusType->EVSOC_isUsed = 0u;
    EVTechnicalStatusType->EVErrorCode_isUsed = 0u;
    EVTechnicalStatusType->EVTimeout_isUsed = 0u;
}

void init_iso20_acds_ACDS_VehiclePositioningReqType(struct iso20_acds_ACDS_VehiclePositioningReqType* ACDS_VehiclePositioningReqType) {
    (void) ACDS_VehiclePositioningReqType;
}

void init_iso20_acds_ACDS_VehiclePositioningResType(struct iso20_acds_ACDS_VehiclePositioningResType* ACDS_VehiclePositioningResType) {
    (void) ACDS_VehiclePositioningResType;
}

void init_iso20_acds_ACDS_ConnectReqType(struct iso20_acds_ACDS_ConnectReqType* ACDS_ConnectReqType) {
    (void) ACDS_ConnectReqType;
}

void init_iso20_acds_ACDS_ConnectResType(struct iso20_acds_ACDS_ConnectResType* ACDS_ConnectResType) {
    (void) ACDS_ConnectResType;
}

void init_iso20_acds_ACDS_SystemStatusReqType(struct iso20_acds_ACDS_SystemStatusReqType* ACDS_SystemStatusReqType) {
    (void) ACDS_SystemStatusReqType;
}

void init_iso20_acds_ACDS_SystemStatusResType(struct iso20_acds_ACDS_SystemStatusResType* ACDS_SystemStatusResType) {
    (void) ACDS_SystemStatusResType;
}

void init_iso20_acds_CLReqControlModeType(struct iso20_acds_CLReqControlModeType* CLReqControlModeType) {
    (void) CLReqControlModeType;
}

void init_iso20_acds_CLResControlModeType(struct iso20_acds_CLResControlModeType* CLResControlModeType) {
    (void) CLResControlModeType;
}

void init_iso20_acds_ManifestType(struct iso20_acds_ManifestType* ManifestType) {
    ManifestType->Reference.arrayLen = 0u;
    ManifestType->Id_isUsed = 0u;
}

void init_iso20_acds_SignaturePropertiesType(struct iso20_acds_SignaturePropertiesType* SignaturePropertiesType) {
    SignaturePropertiesType->Id_isUsed = 0u;
}


