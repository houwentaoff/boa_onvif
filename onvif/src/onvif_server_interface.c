/*!
 *****************************************************************************
 ** \file        packages/onvif/src/onvif_server_interface.c
 **
 ** \version     $Id$
 **
 ** \brief       Onvif interface implementation.
 **
 ** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
 **              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
 **              OMMISSIONS
 **
 ** (C) Copyright 2012-2014 by GOKE MICROELECTRONICS CO.,LTD
 **
 *****************************************************************************
 */


#include "onvif_common.h"

/* #####   TYPE DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ######################### */
//extern GkIpc_OnvifInf g_GkIpc_OnvifInf;


/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */


/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */


#define ONVIF_SERVER_CALL()    printf("onvifs: call %s, path=%s\r\n", __func__, soap->path)

#define ONVIF_RETURN_OK(soap, namespaces)   \
    ONVIF_SERVER_CALL();    \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);  \
return SOAP_OK;

#define ONVIF_NOTSUPPORTED_FUNC(soap, namespaces)   \
    ONVIF_SERVER_CALL();    \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);  \
return soap_receiver_fault_subcode(soap, "ter:ActionNotSupported", "Optional Action Not Implemented ", "The requested action is optional and is not implemented by the device.");

#define      ONVIF_PROCESS_ERROR(soap, namespaces)     \
    ONVIF_SERVER_CALL();    \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);  \
return soap_receiver_fault_subcode(soap, "ter:Action is Supported but run error", "Optional Action Set Error ", "please check server print");

#define      ONVIF_SENDER_ERROR(soap, namespaces, faultsubcodeQName, faultstring, faultdetailXML)        \
    ONVIF_SERVER_CALL();    \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);  \
return soap_sender_fault_subcode(soap, faultsubcodeQName, faultstring, faultdetailXML);

#define     ONVIF_RECEIVER_ERROR(soap, namespaces, faultsubcodeQName, faultstring, faultdetailXML)       \
    ONVIF_SERVER_CALL();    \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);  \
return soap_receiver_fault_subcode(soap, faultsubcodeQName, faultstring, faultdetailXML);


#define      ONVIF_SENDER_2ERROR(soap, namespaces, faultsubcodeQName, faultsubcodeQName1, faultstring, faultdetailXML)   \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);                                                     \
return soap_sender_2fault_subcode(soap, faultsubcodeQName,                                                      \
       faultsubcodeQName1, faultstring, faultdetailXML);

#define      ONVIF_RECEIVER_2ERROR(soap, namespaces, faultsubcodeQName, faultsubcodeQName1, faultstring, faultdetailXML) \
if(namespaces!=NULL) soap_set_namespaces(soap, namespaces);                                                     \
return soap_receiver_2fault_subcode(soap, faultsubcodeQName,                                                    \
       faultsubcodeQName1, faultstring, faultdetailXML);




char DefaultContinuousPanTiltVelocitySpace[] = "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace";
char DefaultContinuousZoomVelocitySpace[] = "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace";

struct tt__FloatRange PanTiltXRange = {
	1, 10	
};

struct tt__FloatRange PanTiltYRange = {
	1, 10	
};

struct tt__Space2DDescription PanTiltRange = {
 	"http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace",
	&PanTiltXRange,
	&PanTiltYRange
};

struct tt__PanTiltLimits PanTiltLimits = {
	&PanTiltRange
};

struct tt__FloatRange ZoomXRange = {
	1, 10	
};

struct tt__Space1DDescription ZoomRange = {
 	"http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace",
	&ZoomXRange,
};

struct tt__ZoomLimits ZoomLimits = {
	&ZoomRange
};



/*PTZ Configuration*/
struct tt__PTZConfiguration PTZConfiguration[PTZ_CONFIGURATIONS_NUM] = {
	{
		"PTZ-Config",
		2,
		"PTZ-Token",
		"Hdwlink HSD PTZ",
		NULL,
		NULL,
		NULL,
		NULL,
		DefaultContinuousPanTiltVelocitySpace,
		DefaultContinuousZoomVelocitySpace,
		NULL,
		NULL,
		&PanTiltLimits,
		&ZoomLimits,
		NULL,
		NULL
	}
};






/******************************函数定义******************************/

//填充onvif服务端接口

/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
 \******************************************************************************/

SOAP_FMAC5 int SOAP_FMAC6 SOAP_ENV__Fault(struct soap* soap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}





SOAP_FMAC5 int SOAP_FMAC6 __wsdd__ProbeMatches(struct soap* soap, struct wsdd__ProbeMatchesType *wsdd__ProbeMatches){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Resolve(struct soap* soap, struct wsdd__ResolveType *wsdd__Resolve){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__ResolveMatches(struct soap* soap, struct wsdd__ResolveMatchesType *wsdd__ResolveMatches){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 SOAP_ENV__Fault_bk(struct soap* soap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetSupportedActions(struct soap* soap, struct _ns1__GetSupportedActions *ns1__GetSupportedActions, struct _ns1__GetSupportedActionsResponse *ns1__GetSupportedActionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetActions(struct soap* soap, struct _ns1__GetActions *ns1__GetActions, struct _ns1__GetActionsResponse *ns1__GetActionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__CreateActions(struct soap* soap, struct _ns1__CreateActions *ns1__CreateActions, struct _ns1__CreateActionsResponse *ns1__CreateActionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__DeleteActions(struct soap* soap, struct _ns1__DeleteActions *ns1__DeleteActions, struct _ns1__DeleteActionsResponse *ns1__DeleteActionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__ModifyActions(struct soap* soap, struct _ns1__ModifyActions *ns1__ModifyActions, struct _ns1__ModifyActionsResponse *ns1__ModifyActionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetServiceCapabilities(struct soap* soap, struct _ns1__GetServiceCapabilities *ns1__GetServiceCapabilities, struct _ns1__GetServiceCapabilitiesResponse *ns1__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__GetActionTriggers(struct soap* soap, struct _ns1__GetActionTriggers *ns1__GetActionTriggers, struct _ns1__GetActionTriggersResponse *ns1__GetActionTriggersResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__CreateActionTriggers(struct soap* soap, struct _ns1__CreateActionTriggers *ns1__CreateActionTriggers, struct _ns1__CreateActionTriggersResponse *ns1__CreateActionTriggersResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__DeleteActionTriggers(struct soap* soap, struct _ns1__DeleteActionTriggers *ns1__DeleteActionTriggers, struct _ns1__DeleteActionTriggersResponse *ns1__DeleteActionTriggersResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns1__ModifyActionTriggers(struct soap* soap, struct _ns1__ModifyActionTriggers *ns1__ModifyActionTriggers, struct _ns1__ModifyActionTriggersResponse *ns1__ModifyActionTriggersResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetServiceCapabilities(struct soap* soap, struct _ns2__GetServiceCapabilities *ns2__GetServiceCapabilities, struct _ns2__GetServiceCapabilitiesResponse *ns2__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointInfoList(struct soap* soap, struct _ns2__GetAccessPointInfoList *ns2__GetAccessPointInfoList, struct _ns2__GetAccessPointInfoListResponse *ns2__GetAccessPointInfoListResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointInfo(struct soap* soap, struct _ns2__GetAccessPointInfo *ns2__GetAccessPointInfo, struct _ns2__GetAccessPointInfoResponse *ns2__GetAccessPointInfoResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAreaInfoList(struct soap* soap, struct _ns2__GetAreaInfoList *ns2__GetAreaInfoList, struct _ns2__GetAreaInfoListResponse *ns2__GetAreaInfoListResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAreaInfo(struct soap* soap, struct _ns2__GetAreaInfo *ns2__GetAreaInfo, struct _ns2__GetAreaInfoResponse *ns2__GetAreaInfoResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__GetAccessPointState(struct soap* soap, struct _ns2__GetAccessPointState *ns2__GetAccessPointState, struct _ns2__GetAccessPointStateResponse *ns2__GetAccessPointStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__EnableAccessPoint(struct soap* soap, struct _ns2__EnableAccessPoint *ns2__EnableAccessPoint, struct _ns2__EnableAccessPointResponse *ns2__EnableAccessPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__DisableAccessPoint(struct soap* soap, struct _ns2__DisableAccessPoint *ns2__DisableAccessPoint, struct _ns2__DisableAccessPointResponse *ns2__DisableAccessPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns2__ExternalAuthorization(struct soap* soap, struct _ns2__ExternalAuthorization *ns2__ExternalAuthorization, struct _ns2__ExternalAuthorizationResponse *ns2__ExternalAuthorizationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__GetServiceCapabilities(struct soap* soap, struct _ns4__GetServiceCapabilities *ns4__GetServiceCapabilities, struct _ns4__GetServiceCapabilitiesResponse *ns4__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__GetDoorInfoList(struct soap* soap, struct _ns4__GetDoorInfoList *ns4__GetDoorInfoList, struct _ns4__GetDoorInfoListResponse *ns4__GetDoorInfoListResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__GetDoorInfo(struct soap* soap, struct _ns4__GetDoorInfo *ns4__GetDoorInfo, struct _ns4__GetDoorInfoResponse *ns4__GetDoorInfoResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__GetDoorState(struct soap* soap, struct _ns4__GetDoorState *ns4__GetDoorState, struct _ns4__GetDoorStateResponse *ns4__GetDoorStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__AccessDoor(struct soap* soap, struct _ns4__AccessDoor *ns4__AccessDoor, struct _ns4__AccessDoorResponse *ns4__AccessDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__LockDoor(struct soap* soap, struct _ns4__LockDoor *ns4__LockDoor, struct _ns4__LockDoorResponse *ns4__LockDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__UnlockDoor(struct soap* soap, struct _ns4__UnlockDoor *ns4__UnlockDoor, struct _ns4__UnlockDoorResponse *ns4__UnlockDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__BlockDoor(struct soap* soap, struct _ns4__BlockDoor *ns4__BlockDoor, struct _ns4__BlockDoorResponse *ns4__BlockDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__LockDownDoor(struct soap* soap, struct _ns4__LockDownDoor *ns4__LockDownDoor, struct _ns4__LockDownDoorResponse *ns4__LockDownDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__LockDownReleaseDoor(struct soap* soap, struct _ns4__LockDownReleaseDoor *ns4__LockDownReleaseDoor, struct _ns4__LockDownReleaseDoorResponse *ns4__LockDownReleaseDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__LockOpenDoor(struct soap* soap, struct _ns4__LockOpenDoor *ns4__LockOpenDoor, struct _ns4__LockOpenDoorResponse *ns4__LockOpenDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__LockOpenReleaseDoor(struct soap* soap, struct _ns4__LockOpenReleaseDoor *ns4__LockOpenReleaseDoor, struct _ns4__LockOpenReleaseDoorResponse *ns4__LockOpenReleaseDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns4__DoubleLockDoor(struct soap* soap, struct _ns4__DoubleLockDoor *ns4__DoubleLockDoor, struct _ns4__DoubleLockDoorResponse *ns4__DoubleLockDoorResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetServiceCapabilities(struct soap* soap, struct _ns5__GetServiceCapabilities *ns5__GetServiceCapabilities, struct _ns5__GetServiceCapabilitiesResponse *ns5__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__CreateRSAKeyPair(struct soap* soap, struct _ns5__CreateRSAKeyPair *ns5__CreateRSAKeyPair, struct _ns5__CreateRSAKeyPairResponse *ns5__CreateRSAKeyPairResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetKeyStatus(struct soap* soap, struct _ns5__GetKeyStatus *ns5__GetKeyStatus, struct _ns5__GetKeyStatusResponse *ns5__GetKeyStatusResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetPrivateKeyStatus(struct soap* soap, struct _ns5__GetPrivateKeyStatus *ns5__GetPrivateKeyStatus, struct _ns5__GetPrivateKeyStatusResponse *ns5__GetPrivateKeyStatusResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetAllKeys(struct soap* soap, struct _ns5__GetAllKeys *ns5__GetAllKeys, struct _ns5__GetAllKeysResponse *ns5__GetAllKeysResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__DeleteKey(struct soap* soap, struct _ns5__DeleteKey *ns5__DeleteKey, struct _ns5__DeleteKeyResponse *ns5__DeleteKeyResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__CreatePKCS10CSR(struct soap* soap, struct _ns5__CreatePKCS10CSR *ns5__CreatePKCS10CSR, struct _ns5__CreatePKCS10CSRResponse *ns5__CreatePKCS10CSRResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__CreateSelfSignedCertificate(struct soap* soap, struct _ns5__CreateSelfSignedCertificate *ns5__CreateSelfSignedCertificate, struct _ns5__CreateSelfSignedCertificateResponse *ns5__CreateSelfSignedCertificateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__UploadCertificate(struct soap* soap, struct _ns5__UploadCertificate *ns5__UploadCertificate, struct _ns5__UploadCertificateResponse *ns5__UploadCertificateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetCertificate(struct soap* soap, struct _ns5__GetCertificate *ns5__GetCertificate, struct _ns5__GetCertificateResponse *ns5__GetCertificateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetAllCertificates(struct soap* soap, struct _ns5__GetAllCertificates *ns5__GetAllCertificates, struct _ns5__GetAllCertificatesResponse *ns5__GetAllCertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__DeleteCertificate(struct soap* soap, struct _ns5__DeleteCertificate *ns5__DeleteCertificate, struct _ns5__DeleteCertificateResponse *ns5__DeleteCertificateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__CreateCertificationPath(struct soap* soap, struct _ns5__CreateCertificationPath *ns5__CreateCertificationPath, struct _ns5__CreateCertificationPathResponse *ns5__CreateCertificationPathResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetCertificationPath(struct soap* soap, struct _ns5__GetCertificationPath *ns5__GetCertificationPath, struct _ns5__GetCertificationPathResponse *ns5__GetCertificationPathResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetAllCertificationPaths(struct soap* soap, struct _ns5__GetAllCertificationPaths *ns5__GetAllCertificationPaths, struct _ns5__GetAllCertificationPathsResponse *ns5__GetAllCertificationPathsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__DeleteCertificationPath(struct soap* soap, struct _ns5__DeleteCertificationPath *ns5__DeleteCertificationPath, struct _ns5__DeleteCertificationPathResponse *ns5__DeleteCertificationPathResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__AddServerCertificateAssignment(struct soap* soap, struct _ns5__AddServerCertificateAssignment *ns5__AddServerCertificateAssignment, struct _ns5__AddServerCertificateAssignmentResponse *ns5__AddServerCertificateAssignmentResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__RemoveServerCertificateAssignment(struct soap* soap, struct _ns5__RemoveServerCertificateAssignment *ns5__RemoveServerCertificateAssignment, struct _ns5__RemoveServerCertificateAssignmentResponse *ns5__RemoveServerCertificateAssignmentResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__ReplaceServerCertificateAssignment(struct soap* soap, struct _ns5__ReplaceServerCertificateAssignment *ns5__ReplaceServerCertificateAssignment, struct _ns5__ReplaceServerCertificateAssignmentResponse *ns5__ReplaceServerCertificateAssignmentResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __ns5__GetAssignedServerCertificates(struct soap* soap, struct _ns5__GetAssignedServerCertificates *ns5__GetAssignedServerCertificates, struct _ns5__GetAssignedServerCertificatesResponse *ns5__GetAssignedServerCertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetServiceCapabilities(struct soap* soap, struct _tad__GetServiceCapabilities *tad__GetServiceCapabilities, struct _tad__GetServiceCapabilitiesResponse *tad__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__DeleteAnalyticsEngineControl(struct soap* soap, struct _tad__DeleteAnalyticsEngineControl *tad__DeleteAnalyticsEngineControl, struct _tad__DeleteAnalyticsEngineControlResponse *tad__DeleteAnalyticsEngineControlResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__CreateAnalyticsEngineControl(struct soap* soap, struct _tad__CreateAnalyticsEngineControl *tad__CreateAnalyticsEngineControl, struct _tad__CreateAnalyticsEngineControlResponse *tad__CreateAnalyticsEngineControlResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetAnalyticsEngineControl(struct soap* soap, struct _tad__SetAnalyticsEngineControl *tad__SetAnalyticsEngineControl, struct _tad__SetAnalyticsEngineControlResponse *tad__SetAnalyticsEngineControlResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineControl(struct soap* soap, struct _tad__GetAnalyticsEngineControl *tad__GetAnalyticsEngineControl, struct _tad__GetAnalyticsEngineControlResponse *tad__GetAnalyticsEngineControlResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineControls(struct soap* soap, struct _tad__GetAnalyticsEngineControls *tad__GetAnalyticsEngineControls, struct _tad__GetAnalyticsEngineControlsResponse *tad__GetAnalyticsEngineControlsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngine(struct soap* soap, struct _tad__GetAnalyticsEngine *tad__GetAnalyticsEngine, struct _tad__GetAnalyticsEngineResponse *tad__GetAnalyticsEngineResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngines(struct soap* soap, struct _tad__GetAnalyticsEngines *tad__GetAnalyticsEngines, struct _tad__GetAnalyticsEnginesResponse *tad__GetAnalyticsEnginesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetVideoAnalyticsConfiguration(struct soap* soap, struct _tad__SetVideoAnalyticsConfiguration *tad__SetVideoAnalyticsConfiguration, struct _tad__SetVideoAnalyticsConfigurationResponse *tad__SetVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__SetAnalyticsEngineInput(struct soap* soap, struct _tad__SetAnalyticsEngineInput *tad__SetAnalyticsEngineInput, struct _tad__SetAnalyticsEngineInputResponse *tad__SetAnalyticsEngineInputResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineInput(struct soap* soap, struct _tad__GetAnalyticsEngineInput *tad__GetAnalyticsEngineInput, struct _tad__GetAnalyticsEngineInputResponse *tad__GetAnalyticsEngineInputResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsEngineInputs(struct soap* soap, struct _tad__GetAnalyticsEngineInputs *tad__GetAnalyticsEngineInputs, struct _tad__GetAnalyticsEngineInputsResponse *tad__GetAnalyticsEngineInputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsDeviceStreamUri(struct soap* soap, struct _tad__GetAnalyticsDeviceStreamUri *tad__GetAnalyticsDeviceStreamUri, struct _tad__GetAnalyticsDeviceStreamUriResponse *tad__GetAnalyticsDeviceStreamUriResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetVideoAnalyticsConfiguration(struct soap* soap, struct _tad__GetVideoAnalyticsConfiguration *tad__GetVideoAnalyticsConfiguration, struct _tad__GetVideoAnalyticsConfigurationResponse *tad__GetVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__CreateAnalyticsEngineInputs(struct soap* soap, struct _tad__CreateAnalyticsEngineInputs *tad__CreateAnalyticsEngineInputs, struct _tad__CreateAnalyticsEngineInputsResponse *tad__CreateAnalyticsEngineInputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__DeleteAnalyticsEngineInputs(struct soap* soap, struct _tad__DeleteAnalyticsEngineInputs *tad__DeleteAnalyticsEngineInputs, struct _tad__DeleteAnalyticsEngineInputsResponse *tad__DeleteAnalyticsEngineInputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tad__GetAnalyticsState(struct soap* soap, struct _tad__GetAnalyticsState *tad__GetAnalyticsState, struct _tad__GetAnalyticsStateResponse *tad__GetAnalyticsStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__GetSupportedRules(struct soap* soap, struct _tan__GetSupportedRules *tan__GetSupportedRules, struct _tan__GetSupportedRulesResponse *tan__GetSupportedRulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__CreateRules(struct soap* soap, struct _tan__CreateRules *tan__CreateRules, struct _tan__CreateRulesResponse *tan__CreateRulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__DeleteRules(struct soap* soap, struct _tan__DeleteRules *tan__DeleteRules, struct _tan__DeleteRulesResponse *tan__DeleteRulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__GetRules(struct soap* soap, struct _tan__GetRules *tan__GetRules, struct _tan__GetRulesResponse *tan__GetRulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__ModifyRules(struct soap* soap, struct _tan__ModifyRules *tan__ModifyRules, struct _tan__ModifyRulesResponse *tan__ModifyRulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__GetServiceCapabilities(struct soap* soap, struct _tan__GetServiceCapabilities *tan__GetServiceCapabilities, struct _tan__GetServiceCapabilitiesResponse *tan__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__GetSupportedAnalyticsModules(struct soap* soap, struct _tan__GetSupportedAnalyticsModules *tan__GetSupportedAnalyticsModules, struct _tan__GetSupportedAnalyticsModulesResponse *tan__GetSupportedAnalyticsModulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__CreateAnalyticsModules(struct soap* soap, struct _tan__CreateAnalyticsModules *tan__CreateAnalyticsModules, struct _tan__CreateAnalyticsModulesResponse *tan__CreateAnalyticsModulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__DeleteAnalyticsModules(struct soap* soap, struct _tan__DeleteAnalyticsModules *tan__DeleteAnalyticsModules, struct _tan__DeleteAnalyticsModulesResponse *tan__DeleteAnalyticsModulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__GetAnalyticsModules(struct soap* soap, struct _tan__GetAnalyticsModules *tan__GetAnalyticsModules, struct _tan__GetAnalyticsModulesResponse *tan__GetAnalyticsModulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tan__ModifyAnalyticsModules(struct soap* soap, struct _tan__ModifyAnalyticsModules *tan__ModifyAnalyticsModules, struct _tan__ModifyAnalyticsModulesResponse *tan__ModifyAnalyticsModulesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Hello(struct soap* soap, struct wsdd__HelloType tdn__Hello, struct wsdd__ResolveType *tdn__HelloResponse)
{

    FUN_IN();

    return SOAP_OK; 

    FUN_OUT();

    //    ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Bye(struct soap* soap, struct wsdd__ByeType tdn__Bye, struct wsdd__ResolveType *tdn__ByeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tdn__Probe(struct soap* soap, struct wsdd__ProbeType tdn__Probe, struct wsdd__ProbeMatchesType *tdn__ProbeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}


SOAP_FMAC5 int SOAP_FMAC6 __tds__UpgradeSystemFirmware(struct soap* soap, struct _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, struct _tds__UpgradeSystemFirmwareResponse *tds__UpgradeSystemFirmwareResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}


SOAP_FMAC5 int SOAP_FMAC6 __tds__RestoreSystem(struct soap* soap, struct _tds__RestoreSystem *tds__RestoreSystem, struct _tds__RestoreSystemResponse *tds__RestoreSystemResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemBackup(struct soap* soap, struct _tds__GetSystemBackup *tds__GetSystemBackup, struct _tds__GetSystemBackupResponse *tds__GetSystemBackupResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}


SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemSupportInformation(struct soap* soap, struct _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, struct _tds__GetSystemSupportInformationResponse *tds__GetSystemSupportInformationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}


SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteDiscoveryMode(struct soap* soap, struct _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, struct _tds__GetRemoteDiscoveryModeResponse *tds__GetRemoteDiscoveryModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteDiscoveryMode(struct soap* soap, struct _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, struct _tds__SetRemoteDiscoveryModeResponse *tds__SetRemoteDiscoveryModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDPAddresses(struct soap* soap, struct _tds__GetDPAddresses *tds__GetDPAddresses, struct _tds__GetDPAddressesResponse *tds__GetDPAddressesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetEndpointReference(struct soap* soap, struct _tds__GetEndpointReference *tds__GetEndpointReference, struct _tds__GetEndpointReferenceResponse *tds__GetEndpointReferenceResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteUser(struct soap* soap, struct _tds__GetRemoteUser *tds__GetRemoteUser, struct _tds__GetRemoteUserResponse *tds__GetRemoteUserResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap* soap, struct _tds__SetRemoteUser *tds__SetRemoteUser, struct _tds__SetRemoteUserResponse *tds__SetRemoteUserResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}



SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDPAddresses(struct soap* soap, struct _tds__SetDPAddresses *tds__SetDPAddresses, struct _tds__SetDPAddressesResponse *tds__SetDPAddressesResponse)
{
    FUN_IN();

    FUN_OUT();

    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetAccessPolicy(struct soap* soap, struct _tds__GetAccessPolicy *tds__GetAccessPolicy, struct _tds__GetAccessPolicyResponse *tds__GetAccessPolicyResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetAccessPolicy(struct soap* soap, struct _tds__SetAccessPolicy *tds__SetAccessPolicy, struct _tds__SetAccessPolicyResponse *tds__SetAccessPolicyResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateCertificate(struct soap* soap, struct _tds__CreateCertificate *tds__CreateCertificate, struct _tds__CreateCertificateResponse *tds__CreateCertificateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificates(struct soap* soap, struct _tds__GetCertificates *tds__GetCertificates, struct _tds__GetCertificatesResponse *tds__GetCertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificatesStatus(struct soap* soap, struct _tds__GetCertificatesStatus *tds__GetCertificatesStatus, struct _tds__GetCertificatesStatusResponse *tds__GetCertificatesStatusResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetCertificatesStatus(struct soap* soap, struct _tds__SetCertificatesStatus *tds__SetCertificatesStatus, struct _tds__SetCertificatesStatusResponse *tds__SetCertificatesStatusResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteCertificates(struct soap* soap, struct _tds__DeleteCertificates *tds__DeleteCertificates, struct _tds__DeleteCertificatesResponse *tds__DeleteCertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetPkcs10Request(struct soap* soap, struct _tds__GetPkcs10Request *tds__GetPkcs10Request, struct _tds__GetPkcs10RequestResponse *tds__GetPkcs10RequestResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificates(struct soap* soap, struct _tds__LoadCertificates *tds__LoadCertificates, struct _tds__LoadCertificatesResponse *tds__LoadCertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetClientCertificateMode(struct soap* soap, struct _tds__GetClientCertificateMode *tds__GetClientCertificateMode, struct _tds__GetClientCertificateModeResponse *tds__GetClientCertificateModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetClientCertificateMode(struct soap* soap, struct _tds__SetClientCertificateMode *tds__SetClientCertificateMode, struct _tds__SetClientCertificateModeResponse *tds__SetClientCertificateModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRelayOutputs(struct soap* soap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse)
{

    FUN_IN();

    FUN_OUT();

    return SOAP_OK;    
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputSettings(struct soap* soap, struct _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, struct _tds__SetRelayOutputSettingsResponse *tds__SetRelayOutputSettingsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputState(struct soap* soap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SendAuxiliaryCommand(struct soap* soap, struct _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, struct _tds__SendAuxiliaryCommandResponse *tds__SendAuxiliaryCommandResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCACertificates(struct soap* soap, struct _tds__GetCACertificates *tds__GetCACertificates, struct _tds__GetCACertificatesResponse *tds__GetCACertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificateWithPrivateKey(struct soap* soap, struct _tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, struct _tds__LoadCertificateWithPrivateKeyResponse *tds__LoadCertificateWithPrivateKeyResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificateInformation(struct soap* soap, struct _tds__GetCertificateInformation *tds__GetCertificateInformation, struct _tds__GetCertificateInformationResponse *tds__GetCertificateInformationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCACertificates(struct soap* soap, struct _tds__LoadCACertificates *tds__LoadCACertificates, struct _tds__LoadCACertificatesResponse *tds__LoadCACertificatesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateDot1XConfiguration(struct soap* soap, struct _tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, struct _tds__CreateDot1XConfigurationResponse *tds__CreateDot1XConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDot1XConfiguration(struct soap* soap, struct _tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, struct _tds__SetDot1XConfigurationResponse *tds__SetDot1XConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfiguration(struct soap* soap, struct _tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, struct _tds__GetDot1XConfigurationResponse *tds__GetDot1XConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfigurations(struct soap* soap, struct _tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, struct _tds__GetDot1XConfigurationsResponse *tds__GetDot1XConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteDot1XConfiguration(struct soap* soap, struct _tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, struct _tds__DeleteDot1XConfigurationResponse *tds__DeleteDot1XConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Capabilities(struct soap* soap, struct _tds__GetDot11Capabilities *tds__GetDot11Capabilities, struct _tds__GetDot11CapabilitiesResponse *tds__GetDot11CapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Status(struct soap* soap, struct _tds__GetDot11Status *tds__GetDot11Status, struct _tds__GetDot11StatusResponse *tds__GetDot11StatusResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__ScanAvailableDot11Networks(struct soap* soap, struct _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, struct _tds__ScanAvailableDot11NetworksResponse *tds__ScanAvailableDot11NetworksResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemUris(struct soap* soap, struct _tds__GetSystemUris *tds__GetSystemUris, struct _tds__GetSystemUrisResponse *tds__GetSystemUrisResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartFirmwareUpgrade(struct soap* soap, struct _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, struct _tds__StartFirmwareUpgradeResponse *tds__StartFirmwareUpgradeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__StartSystemRestore(struct soap* soap, struct _tds__StartSystemRestore *tds__StartSystemRestore, struct _tds__StartSystemRestoreResponse *tds__StartSystemRestoreResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__PullMessages(struct soap* soap, struct _tev__PullMessages *tev__PullMessages, struct _tev__PullMessagesResponse *tev__PullMessagesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Seek(struct soap* soap, struct _tev__Seek *tev__Seek, struct _tev__SeekResponse *tev__SeekResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__SetSynchronizationPoint(struct soap* soap, struct _tev__SetSynchronizationPoint *tev__SetSynchronizationPoint, struct _tev__SetSynchronizationPointResponse *tev__SetSynchronizationPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__GetServiceCapabilities(struct soap* soap, struct _tev__GetServiceCapabilities *tev__GetServiceCapabilities, struct _tev__GetServiceCapabilitiesResponse *tev__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__CreatePullPointSubscription(struct soap* soap, struct _tev__CreatePullPointSubscription *tev__CreatePullPointSubscription, struct _tev__CreatePullPointSubscriptionResponse *tev__CreatePullPointSubscriptionResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__GetEventProperties(struct soap* soap, struct _tev__GetEventProperties *tev__GetEventProperties, struct _tev__GetEventPropertiesResponse *tev__GetEventPropertiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Renew(struct soap* soap, struct _wsnt__Renew *wsnt__Renew, struct _wsnt__RenewResponse *wsnt__RenewResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Unsubscribe(struct soap* soap, struct _wsnt__Unsubscribe *wsnt__Unsubscribe, struct _wsnt__UnsubscribeResponse *wsnt__UnsubscribeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Subscribe(struct soap* soap, struct _wsnt__Subscribe *wsnt__Subscribe, struct _wsnt__SubscribeResponse *wsnt__SubscribeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__GetCurrentMessage(struct soap* soap, struct _wsnt__GetCurrentMessage *wsnt__GetCurrentMessage, struct _wsnt__GetCurrentMessageResponse *wsnt__GetCurrentMessageResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Notify(struct soap* soap, struct _wsnt__Notify *wsnt__Notify){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__GetMessages(struct soap* soap, struct _wsnt__GetMessages *wsnt__GetMessages, struct _wsnt__GetMessagesResponse *wsnt__GetMessagesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__DestroyPullPoint(struct soap* soap, struct _wsnt__DestroyPullPoint *wsnt__DestroyPullPoint, struct _wsnt__DestroyPullPointResponse *wsnt__DestroyPullPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Notify_(struct soap* soap, struct _wsnt__Notify *wsnt__Notify){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__CreatePullPoint(struct soap* soap, struct _wsnt__CreatePullPoint *wsnt__CreatePullPoint, struct _wsnt__CreatePullPointResponse *wsnt__CreatePullPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Renew_(struct soap* soap, struct _wsnt__Renew *wsnt__Renew, struct _wsnt__RenewResponse *wsnt__RenewResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__Unsubscribe_(struct soap* soap, struct _wsnt__Unsubscribe *wsnt__Unsubscribe, struct _wsnt__UnsubscribeResponse *wsnt__UnsubscribeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__PauseSubscription(struct soap* soap, struct _wsnt__PauseSubscription *wsnt__PauseSubscription, struct _wsnt__PauseSubscriptionResponse *wsnt__PauseSubscriptionResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tev__ResumeSubscription(struct soap* soap, struct _wsnt__ResumeSubscription *wsnt__ResumeSubscription, struct _wsnt__ResumeSubscriptionResponse *wsnt__ResumeSubscriptionResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetServiceCapabilities(struct soap* soap, struct _timg__GetServiceCapabilities *timg__GetServiceCapabilities, struct _timg__GetServiceCapabilitiesResponse *timg__GetServiceCapabilitiesResponse)
{
    printf("[%d] __timg__GetServiceCapabilities start !\n", __LINE__);

    timg__GetServiceCapabilitiesResponse->Capabilities = (struct timg__Capabilities *)soap_malloc(soap, sizeof(struct timg__Capabilities));
    timg__GetServiceCapabilitiesResponse->Capabilities->__size = 1;
    timg__GetServiceCapabilitiesResponse->Capabilities->__any = NULL; 
    timg__GetServiceCapabilitiesResponse->Capabilities->ImageStabilization = (enum xsd__boolean *)soap_malloc(soap, sizeof(enum xsd__boolean));
    *timg__GetServiceCapabilitiesResponse->Capabilities->ImageStabilization = xsd__boolean__true_; 
    timg__GetServiceCapabilitiesResponse->Capabilities->__anyAttribute = NULL;

    printf("[%d] __timg__GetServiceCapabilities exit !\n", __LINE__);

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetImagingSettings(struct soap* soap, struct _timg__GetImagingSettings *timg__GetImagingSettings, struct _timg__GetImagingSettingsResponse *timg__GetImagingSettingsResponse)
{
	int blcMode = 0;
	int gain = 0;
	int shutterTime = 0;
	int shutterTimeMin = 0;
	int shutterTimeMax = 0;
	int sensorGainMax = 0;
	int wbRGain = 0;
	int wbBGain = 0;

    printf("[%d] __timg__GetImagingSettings start !\n", __LINE__);

    /*check video source token*/
    if ((timg__GetImagingSettings->VideoSourceToken == NULL) ||
            (strcmp(timg__GetImagingSettings->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))

    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:Nosource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

    timg__GetImagingSettingsResponse->ImagingSettings = (struct tt__ImagingSettings20 *)soap_malloc(soap, sizeof(struct tt__ImagingSettings20));

    /*BLC*/	
    blcMode = imagingGetBLCMode();
    timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation = (struct tt__BacklightCompensation20 *)soap_malloc(soap, sizeof(struct tt__BacklightCompensation20));
    if (blcMode == 0)/*0-disable, 1-enable*/
    {	
        timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation->Mode = tt__BacklightCompensationMode__OFF;
    }
    else
    {
        timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation->Mode = tt__BacklightCompensationMode__ON;
    }
    timg__GetImagingSettingsResponse->ImagingSettings->BacklightCompensation->Level = NULL;

    /*Brightness*/
    timg__GetImagingSettingsResponse->ImagingSettings->Brightness = (float *)soap_malloc(soap, sizeof(float));
    *timg__GetImagingSettingsResponse->ImagingSettings->Brightness = imagingGetBrightness();

    /*ColorSaturation*/
    timg__GetImagingSettingsResponse->ImagingSettings->ColorSaturation = (float *)soap_malloc(soap, sizeof(float));
    *timg__GetImagingSettingsResponse->ImagingSettings->ColorSaturation = imagingGetColorSaturation();

    /*Contrast*/		
    timg__GetImagingSettingsResponse->ImagingSettings->Contrast = (float *)soap_malloc(soap, sizeof(float));
    *timg__GetImagingSettingsResponse->ImagingSettings->Contrast = imagingGetContrast();

    /*Exposure*/
    timg__GetImagingSettingsResponse->ImagingSettings->Exposure = (struct tt__Exposure20 *)soap_malloc(soap, sizeof(struct tt__Exposure20));
    if(imagingGetExposureMode() == 0)
    {		
        timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Mode = tt__ExposureMode__MANUAL;
    }
    else
    {
        timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Mode = tt__ExposureMode__AUTO;
    }

	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Priority  = NULL;
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Window = NULL;
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MinExposureTime = (float *)soap_malloc(soap, sizeof(float));	
	if(imagingGetAEShutterTimeMin(&shutterTimeMin) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MinExposureTime = shutterTimeMin;	
	}
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MaxExposureTime = (float *)soap_malloc(soap, sizeof(float));
	if(imagingGetAEShutterTimeMax(&shutterTimeMax) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MaxExposureTime = shutterTimeMax;
	}
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MinGain = NULL;
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MaxGain = (float *)soap_malloc(soap, sizeof(float));
	if(imagingGetAEGainMax(&sensorGainMax) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MaxGain = sensorGainMax;
	}
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MinIris = NULL;
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->MaxIris = NULL;
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->ExposureTime = (float *)soap_malloc(soap, sizeof(float));	
	if(imagingGetMEShutterTime(&shutterTime) == 0)
	{	
		*timg__GetImagingSettingsResponse->ImagingSettings->Exposure->ExposureTime = shutterTime;
	}
	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Gain = (float *)soap_malloc(soap, sizeof(float));	
	if(imagingGetMEGain(&gain) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Gain = gain;
	}

	timg__GetImagingSettingsResponse->ImagingSettings->Exposure->Iris = NULL;

    /*Focus*/
	timg__GetImagingSettingsResponse->ImagingSettings->Focus = (struct tt__FocusConfiguration20 *)soap_malloc(soap, sizeof(struct tt__FocusConfiguration20));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->AutoFocusMode = tt__AutoFocusMode__AUTO;
	//timg__GetImagingSettingsResponse->ImagingSettings->Focus->DefaultSpeed = (float *)soap_malloc(soap, sizeof(float));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->DefaultSpeed = NULL;
	//timg__GetImagingSettingsResponse->ImagingSettings->Focus->NearLimit = (float *)soap_malloc(soap, sizeof(float));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->NearLimit = NULL;
	//timg__GetImagingSettingsResponse->ImagingSettings->Focus->FarLimit = (float *)soap_malloc(soap, sizeof(float));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->FarLimit = NULL;
	//timg__GetImagingSettingsResponse->ImagingSettings->Focus->Extension = (tt__FocusConfiguration20Extension *)soap_malloc(soap, sizeof(tt__FocusConfiguration20Extension));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->Extension = NULL;
	//timg__GetImagingSettingsResponse->ImagingSettings->Focus->__anyAttribute = (char *)soap_malloc(soap, sizeof(char));
	timg__GetImagingSettingsResponse->ImagingSettings->Focus->__anyAttribute = NULL;

	/*IrCut*/
	timg__GetImagingSettingsResponse->ImagingSettings->IrCutFilter = (enum tt__IrCutFilterMode *)soap_malloc(soap, sizeof(enum tt__IrCutFilterMode));;
	*timg__GetImagingSettingsResponse->ImagingSettings->IrCutFilter = tt__IrCutFilterMode__AUTO;

	/*Sharpness*/	
	timg__GetImagingSettingsResponse->ImagingSettings->Sharpness = (float *)soap_malloc(soap, sizeof(float));
	*timg__GetImagingSettingsResponse->ImagingSettings->Sharpness = imagingGetSharpness();

	/*DynamicRange*/	
	timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange = (struct tt__WideDynamicRange20 *)soap_malloc(soap, sizeof(struct tt__WideDynamicRange20));;
	timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange->Mode = tt__WideDynamicMode__ON;
	timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange->Level = (float *)soap_malloc(soap, sizeof(float));	
	*timg__GetImagingSettingsResponse->ImagingSettings->WideDynamicRange->Level = 100;

	/*WhiteBalance*/
	timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance = (struct tt__WhiteBalance20 *)soap_malloc(soap, sizeof(struct tt__WhiteBalance20));;
	if(imagingGetWhiteBalanceMode() == 0)
	{
		timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->Mode = tt__WhiteBalanceMode__MANUAL;
	}
	else
	{
		timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->Mode = tt__WhiteBalanceMode__AUTO;
	}
	timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CrGain = (float *)soap_malloc(soap, sizeof(float));	
	if(imagingGetWhiteBalanceRgain(&wbRGain) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CrGain = wbRGain;
	}
	timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CbGain = (float *)soap_malloc(soap, sizeof(float));
	if(imagingGetWhiteBalanceBgain(&wbBGain) == 0)
	{
		*timg__GetImagingSettingsResponse->ImagingSettings->WhiteBalance->CbGain = wbBGain;		
	}

	/*Extension*/
	timg__GetImagingSettingsResponse->ImagingSettings->Extension = NULL;

	timg__GetImagingSettingsResponse->ImagingSettings->__anyAttribute = NULL;

	printf("[%d] __timg__GetImagingSettings exit !\n", __LINE__);

	//return soap_receiver_fault_subcode(soap, "ter:ActionNotSupported", "Optional Action Not Implemented ", "The requested VideoSource does not support imaging settings.");

	return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __timg__SetImagingSettings(struct soap* soap, struct _timg__SetImagingSettings *timg__SetImagingSettings, struct _timg__SetImagingSettingsResponse *timg__SetImagingSettingsResponse)
{
	int retVal      = 0;
	int gain        = 0;
	int shutterTime = 0;	
	int shutterTimeMin = 0;
	int shutterTimeMax = 0;
	int sensorGainMax = 0;
	int rGain = 0;
	int bGain = 0;

	printf("[%d] __timg__SetImagingSettings start !\n", __LINE__);

    /*check video source token*/
	if ((timg__SetImagingSettings->VideoSourceToken == NULL) ||
            (strcmp(timg__SetImagingSettings->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:Nosource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

	/*check input parameters*/
	if ((timg__SetImagingSettings->ImagingSettings == NULL) || (timg__SetImagingSettings->ForcePersistence == NULL))
	{				
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:SettingsInvalid", "The requested settings are incorrect.", NULL);
		return SOAP_OK;
	}


	/*BLC*/
	if(timg__SetImagingSettings->ImagingSettings->BacklightCompensation != NULL)
	{
	    if(timg__SetImagingSettings->ImagingSettings->BacklightCompensation->Mode != imagingGetBLCMode())
	    {
			retVal = imagingSetBLCMode(timg__SetImagingSettings->ImagingSettings->BacklightCompensation->Mode);
			if(retVal != 0)
			{
				ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
				return SOAP_OK;
			}
		}
	}

	/*Brightness*/
	if(timg__SetImagingSettings->ImagingSettings->Brightness != NULL)
	{
	    if(*timg__SetImagingSettings->ImagingSettings->Brightness != imagingGetBrightness())
		{
			retVal = imagingSetBrightness(*timg__SetImagingSettings->ImagingSettings->Brightness);
			if(retVal != 0)
			{
				ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
				return SOAP_OK;
			}	
		}	
	}

	/*Color Saturation*/
	if(timg__SetImagingSettings->ImagingSettings->ColorSaturation != NULL)
	{
	    if(*timg__SetImagingSettings->ImagingSettings->ColorSaturation != imagingGetColorSaturation())
		{
			retVal = imagingSetColorSaturation(*timg__SetImagingSettings->ImagingSettings->ColorSaturation);
			if(retVal != 0)
			{
				ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
				return SOAP_OK;
			}	
		}
	}

	/*Contrast*/
	if(timg__SetImagingSettings->ImagingSettings->Contrast != NULL)
	{
	    if(*timg__SetImagingSettings->ImagingSettings->Contrast != imagingGetContrast())
		{
			retVal = imagingSetContrast(*timg__SetImagingSettings->ImagingSettings->Contrast);
			if(retVal != 0)
			{
				ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
				return SOAP_OK;
			}	
		}
	}

	/*Exposure*/	
	if(timg__SetImagingSettings->ImagingSettings->Exposure != NULL)
	{
	    /*mode*/
	    if(imagingGetExposureMode() == 0)
		{
			if(timg__SetImagingSettings->ImagingSettings->Exposure->Mode != tt__ExposureMode__MANUAL)
			{
				retVal = imagingSetExposureMode(1);				
				sleep(1);
				if(retVal != 0)
				{
					ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
					return SOAP_OK;
				}
			}
		}
		else
		{
			if(timg__SetImagingSettings->ImagingSettings->Exposure->Mode != tt__ExposureMode__AUTO)
			{
			   	retVal = imagingSetExposureMode(0);
				sleep(1);
				if(retVal != 0)
				{
					ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
					return SOAP_OK;
				}
			}
		}

		/*Auto Mode*/
		if(timg__SetImagingSettings->ImagingSettings->Exposure->Mode ==  tt__ExposureMode__AUTO)
		{
		    /*AE Min exposure time*/
			if(timg__SetImagingSettings->ImagingSettings->Exposure->MinExposureTime != NULL)
			{
				if(imagingGetAEShutterTimeMin(&shutterTimeMin) == 0)
				{
					if(shutterTimeMin != *timg__SetImagingSettings->ImagingSettings->Exposure->MinExposureTime)
					{
						retVal = imagingSetAEShutterTimeMin(*timg__SetImagingSettings->ImagingSettings->Exposure->MinExposureTime);
						if( retVal != 0)
						{
							ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
							return SOAP_OK;
						}
					}
				}
			}
			/*AE Max exposure time*/
			if(timg__SetImagingSettings->ImagingSettings->Exposure->MaxExposureTime != NULL)
			{
				if(imagingGetAEShutterTimeMax(&shutterTimeMax) == 0)
				{
					if(shutterTimeMax != *timg__SetImagingSettings->ImagingSettings->Exposure->MaxExposureTime)
					{
						retVal = imagingSetAEShutterTimeMax(*timg__SetImagingSettings->ImagingSettings->Exposure->MaxExposureTime);
						if( retVal != 0)
						{
							ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
							return SOAP_OK;
						}
					}
				}
			}
			/*AE Max sensor gain*/
			if(timg__SetImagingSettings->ImagingSettings->Exposure->MaxGain != NULL)
			{
				if(imagingGetAEGainMax(&sensorGainMax) == 0)
				{
					if(sensorGainMax != *timg__SetImagingSettings->ImagingSettings->Exposure->MaxGain)
					{
						retVal = imagingSetAEGainMax(*timg__SetImagingSettings->ImagingSettings->Exposure->MaxGain);
						if( retVal != 0)
						{
							ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
							return SOAP_OK;
						}
					}
				}
			}
		}
		/*Manual Mode*/
		if(timg__SetImagingSettings->ImagingSettings->Exposure->Mode ==  tt__ExposureMode__MANUAL)
		{
			/*exposure time*/
			if(timg__SetImagingSettings->ImagingSettings->Exposure->ExposureTime != NULL)
			{
				if(imagingGetMEShutterTime(&shutterTime) == 0)
				{
					if(shutterTime != *timg__SetImagingSettings->ImagingSettings->Exposure->ExposureTime)
					{
					    retVal = imagingSetMEShutterTime(*timg__SetImagingSettings->ImagingSettings->Exposure->ExposureTime);
						if( retVal != 0)
						{
							ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
							return SOAP_OK;
						}
					}
				}
			}
			/*gain*/
			if(timg__SetImagingSettings->ImagingSettings->Exposure->Gain != NULL)
			{
				if(imagingGetMEGain(&gain) == 0)
				{
				    if(gain != *timg__SetImagingSettings->ImagingSettings->Exposure->Gain)
					{
						retVal = imagingSetMEGain(*timg__SetImagingSettings->ImagingSettings->Exposure->Gain);
						if( retVal != 0)
						{
							ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
							return SOAP_OK;
						}
					}
				}
			}
			/*iris*/
		}
	}
	
	/*Sharpness*/
	if(timg__SetImagingSettings->ImagingSettings->Sharpness != NULL)
	{
	    if(*timg__SetImagingSettings->ImagingSettings->Sharpness != imagingGetSharpness())
		{
			retVal = imagingSetSharpness(*timg__SetImagingSettings->ImagingSettings->Sharpness);
			if(retVal != 0)
			{
				ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
				return SOAP_OK;
			}	
		}
	}

	/*WhiteBalance*/
	if(timg__SetImagingSettings->ImagingSettings->WhiteBalance != NULL)
	{
		if(timg__SetImagingSettings->ImagingSettings->WhiteBalance->Mode == tt__WhiteBalanceMode__AUTO)
		{				
			if(imagingGetWhiteBalanceMode() == 0)
			{
				imagingSetWhiteBalanceMode(1);
			}
		}

		if(timg__SetImagingSettings->ImagingSettings->WhiteBalance->Mode == tt__WhiteBalanceMode__MANUAL)
		{
			if(imagingGetWhiteBalanceMode() == 1)
			{
				imagingSetWhiteBalanceMode(0);
				sleep(1);
			}

			imagingGetWhiteBalanceRgain(&rGain);
			imagingGetWhiteBalanceBgain(&bGain);
			
			if((rGain != *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CrGain) ||
				(bGain != *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CbGain))
			{
			    bGain = *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CbGain; 
				rGain = *timg__SetImagingSettings->ImagingSettings->WhiteBalance->CrGain;				
				if(imagingSetWhiteBalanceGain(rGain,bGain) != 0)
				{
					ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:ActionNotSupported", "ter:NoImagingForSource", "The requested VideoSource doest not support imaging settings.", NULL);
					return SOAP_OK;
				}
			}
		}
	}
	
	printf("[%d] __timg__SetImagingSettings exit !\n", __LINE__);

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetOptions(struct soap* soap, struct _timg__GetOptions *timg__GetOptions, struct _timg__GetOptionsResponse *timg__GetOptionsResponse)
{
	printf("[%d] __timg__GetOptions start !\n", __LINE__);

    /*check video source token*/
	if ((timg__GetOptions->VideoSourceToken == NULL) ||
            (strcmp(timg__GetOptions->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {       
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
        return SOAP_OK;
	}

	timg__GetOptionsResponse->ImagingOptions = (struct tt__ImagingOptions20 *)soap_malloc(soap, sizeof(struct tt__ImagingOptions20));

    /*BLC*/
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation   = (struct tt__BacklightCompensationOptions20 *)soap_malloc(soap, sizeof(struct tt__BacklightCompensationOptions20));
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation->__sizeMode = 2;		
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation->Mode = (enum tt__BacklightCompensationMode *)soap_malloc(soap, sizeof(enum tt__BacklightCompensationMode)*2);
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation->Mode[0] = tt__BacklightCompensationMode__ON;
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation->Mode[1] = tt__BacklightCompensationMode__OFF;
	timg__GetOptionsResponse->ImagingOptions->BacklightCompensation->Level= NULL;

    /*Brightness*/
	timg__GetOptionsResponse->ImagingOptions->Brightness = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Brightness->Max = 255;
	timg__GetOptionsResponse->ImagingOptions->Brightness->Min = -255;

    /*ColorSaturation*/
	timg__GetOptionsResponse->ImagingOptions->ColorSaturation = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->ColorSaturation->Max = 255;
	timg__GetOptionsResponse->ImagingOptions->ColorSaturation->Min = 0;
	
    /*Contrast*/
	timg__GetOptionsResponse->ImagingOptions->Contrast = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Contrast->Max = 128;
	timg__GetOptionsResponse->ImagingOptions->Contrast->Min = 0;

	/*Exposure*/	
	timg__GetOptionsResponse->ImagingOptions->Exposure = (struct tt__ExposureOptions20 *)soap_malloc(soap, sizeof(struct tt__ExposureOptions20));
    timg__GetOptionsResponse->ImagingOptions->Exposure->__sizeMode = 2; 
	timg__GetOptionsResponse->ImagingOptions->Exposure->Mode = (enum tt__ExposureMode *)soap_malloc(soap, sizeof(enum tt__ExposureMode)*2);
	timg__GetOptionsResponse->ImagingOptions->Exposure->Mode[0] = tt__ExposureMode__AUTO;	
	timg__GetOptionsResponse->ImagingOptions->Exposure->Mode[1] = tt__ExposureMode__MANUAL;
	timg__GetOptionsResponse->ImagingOptions->Exposure->__sizePriority = 0;
	timg__GetOptionsResponse->ImagingOptions->Exposure->Priority = NULL;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MinExposureTime = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Exposure->MinExposureTime->Max = 8000;
    timg__GetOptionsResponse->ImagingOptions->Exposure->MinExposureTime->Min = 120;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MaxExposureTime = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Exposure->MaxExposureTime->Max = 100;
    timg__GetOptionsResponse->ImagingOptions->Exposure->MaxExposureTime->Min = 1;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MinGain = NULL;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MaxGain = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Exposure->MaxGain->Max = 60;
    timg__GetOptionsResponse->ImagingOptions->Exposure->MaxGain->Min = 0;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MinIris = NULL;
	timg__GetOptionsResponse->ImagingOptions->Exposure->MaxIris = NULL;
	timg__GetOptionsResponse->ImagingOptions->Exposure->ExposureTime = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Exposure->ExposureTime->Max = 8000;
    timg__GetOptionsResponse->ImagingOptions->Exposure->ExposureTime->Min = 1;
	timg__GetOptionsResponse->ImagingOptions->Exposure->Gain = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Exposure->Gain->Max = 60;
    timg__GetOptionsResponse->ImagingOptions->Exposure->Gain->Min = 0;
	timg__GetOptionsResponse->ImagingOptions->Exposure->Iris = NULL;

    /*Focus*/
	timg__GetOptionsResponse->ImagingOptions->Focus = (struct tt__FocusOptions20 *)soap_malloc(soap, sizeof(struct tt__FocusOptions20));
	timg__GetOptionsResponse->ImagingOptions->Focus->__sizeAutoFocusModes = 2;
	timg__GetOptionsResponse->ImagingOptions->Focus->AutoFocusModes = (enum tt__AutoFocusMode *)soap_malloc(soap, sizeof(enum tt__AutoFocusMode)*2);
	timg__GetOptionsResponse->ImagingOptions->Focus->AutoFocusModes[0] = tt__AutoFocusMode__AUTO;
	timg__GetOptionsResponse->ImagingOptions->Focus->AutoFocusModes[1] = tt__AutoFocusMode__MANUAL;
	timg__GetOptionsResponse->ImagingOptions->Focus->DefaultSpeed = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Focus->DefaultSpeed->Max = 100;
    timg__GetOptionsResponse->ImagingOptions->Focus->DefaultSpeed->Min = 0;
	timg__GetOptionsResponse->ImagingOptions->Focus->NearLimit = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Focus->NearLimit->Max = 100;
    timg__GetOptionsResponse->ImagingOptions->Focus->NearLimit->Min = 0;
	timg__GetOptionsResponse->ImagingOptions->Focus->FarLimit = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Focus->FarLimit->Max = 100;
    timg__GetOptionsResponse->ImagingOptions->Focus->FarLimit->Min = 0;
	timg__GetOptionsResponse->ImagingOptions->Focus->Extension = NULL;

	/*IrCut*/
	timg__GetOptionsResponse->ImagingOptions->__sizeIrCutFilterModes = 3;
	timg__GetOptionsResponse->ImagingOptions->IrCutFilterModes = (enum tt__IrCutFilterMode *)soap_malloc(soap, sizeof(enum tt__IrCutFilterMode)*3);
	timg__GetOptionsResponse->ImagingOptions->IrCutFilterModes[0] = tt__IrCutFilterMode__ON;
	timg__GetOptionsResponse->ImagingOptions->IrCutFilterModes[1] = tt__IrCutFilterMode__OFF;
	timg__GetOptionsResponse->ImagingOptions->IrCutFilterModes[2] = tt__IrCutFilterMode__AUTO;

	/*Sharpness*/
	timg__GetOptionsResponse->ImagingOptions->Sharpness = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->Sharpness->Max = 255;
	timg__GetOptionsResponse->ImagingOptions->Sharpness->Min = 0;

    /*WideDynamicMode*/
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange = (struct tt__WideDynamicRangeOptions20 *)soap_malloc(soap, sizeof(struct tt__WideDynamicRangeOptions20));
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->__sizeMode = 2;	
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Mode = (enum tt__WideDynamicMode *)soap_malloc(soap, sizeof(enum tt__WideDynamicMode)*2);
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Mode[0] = tt__WideDynamicMode__OFF;
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Mode[1] = tt__WideDynamicMode__ON;
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Level = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Level->Max = 100;
	timg__GetOptionsResponse->ImagingOptions->WideDynamicRange->Level->Min = 0;

	/*WhiteBalance*/
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance = (struct tt__WhiteBalanceOptions20 *)soap_malloc(soap, sizeof(struct tt__WhiteBalanceOptions20));
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->__sizeMode = 2;		
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->Mode = (enum tt__WhiteBalanceMode *)soap_malloc(soap, sizeof(enum tt__WhiteBalanceMode)*2);
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->Mode[0] = tt__WhiteBalanceMode__AUTO;
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->Mode[1] = tt__WhiteBalanceMode__MANUAL;	
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YrGain = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YrGain->Max = 16384;	
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YrGain->Min = 1;
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YbGain = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YbGain->Max = 16384;	
	timg__GetOptionsResponse->ImagingOptions->WhiteBalance->YbGain->Min = 1;

	/*Extension*/
	timg__GetOptionsResponse->ImagingOptions->Extension = NULL;
	
	timg__GetOptionsResponse->ImagingOptions->__anyAttribute = NULL;

	printf("[%d] __timg__GetOptions exit !\n", __LINE__);

	//return soap_receiver_fault_subcode(soap, "ter:ActionNotSupported", "Optional Action Not Implemented ", "The requested VideoSource does not support imaging settings.");

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__Move(struct soap* soap, struct _timg__Move *timg__Move, struct _timg__MoveResponse *timg__MoveResponse)
{
	printf("[%d] __timg__Move start !\n", __LINE__);

	/*check video source token*/
	if ((timg__Move->VideoSourceToken == NULL) ||
            (strcmp(timg__Move->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {		
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

    /*check input parameter:Focus*/
	if(timg__Move->Focus == NULL)
	{
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

    /*AbsoluteFocus*/
	if(timg__Move->Focus->Absolute != NULL)
	{	    
		printf("input parameter:AbsoluteFocus!\n");
		ONVIF_RECEIVER_ERROR(soap, NULL, "ter:ActionNotSupported", "The requested VideoSource does not support imaging settings.", NULL);
	}
	/*RelativeFocus*/
	else if(timg__Move->Focus->Relative != NULL)
	{		
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}
	/*ContinuousFocus*/
	else if(timg__Move->Focus->Continuous != NULL)
	{
		printf("input parameter:ContinuousFocus!\n");
		/*move continuous*/
	}
	else
    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.",NULL);
		return SOAP_OK;
	}
    
	printf("[%d] __timg__Move exit !\n", __LINE__);

	return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __timg__Stop(struct soap* soap, struct _timg__Stop *timg__Stop, struct _timg__StopResponse *timg__StopResponse)
{
	printf("[%d] __timg__Stop start !\n", __LINE__);

	/*check video source token*/
	if ((timg__Stop->VideoSourceToken == NULL) ||
            (strcmp(timg__Stop->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

	/*stop all ongoing movements of lense.*/

	printf("[%d] __timg__Stop exit !\n", __LINE__);

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetStatus(struct soap* soap, struct _timg__GetStatus *timg__GetStatus, struct _timg__GetStatusResponse *timg__GetStatusResponse)
{
	printf("[%d] __timg__GetStatus start !\n", __LINE__);

	/*check video source token*/
	if ((timg__GetStatus->VideoSourceToken == NULL) ||
            (strcmp(timg__GetStatus->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

	/*response*/
	timg__GetStatusResponse->Status = (struct tt__ImagingStatus20 *)soap_malloc(soap, sizeof(struct tt__ImagingStatus20));	
	
	timg__GetStatusResponse->Status->FocusStatus20 = (struct tt__FocusStatus20 *)soap_malloc(soap, sizeof(struct tt__FocusStatus20));
	timg__GetStatusResponse->Status->FocusStatus20->Position = 0;/*dummy*/
	timg__GetStatusResponse->Status->FocusStatus20->MoveStatus = tt__MoveStatus__IDLE;/*dummy*/
	timg__GetStatusResponse->Status->FocusStatus20->Error = NULL;
	timg__GetStatusResponse->Status->FocusStatus20->Extension = NULL;
	timg__GetStatusResponse->Status->FocusStatus20->__anyAttribute = NULL;

    /*Extension*/
	timg__GetStatusResponse->Status->Extension = NULL; 
	
	timg__GetStatusResponse->Status->__anyAttribute = NULL; 

	printf("[%d] __timg__GetStatus exit !\n", __LINE__);

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __timg__GetMoveOptions(struct soap* soap, struct _timg__GetMoveOptions *timg__GetMoveOptions, struct _timg__GetMoveOptionsResponse *timg__GetMoveOptionsResponse)
{
	printf("[%d] __timg__GetMoveOptions start !\n", __LINE__);

	/*check video source token*/
	if ((timg__GetMoveOptions->VideoSourceToken == NULL) ||
            (strcmp(timg__GetMoveOptions->VideoSourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[0].SourceToken) != 0))
    {
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoSource", "The requested VideoSource does not exit.", NULL);
		return SOAP_OK;
	}

    /*Response*/
	timg__GetMoveOptionsResponse->MoveOptions = (struct tt__MoveOptions20 *)soap_malloc(soap, sizeof(struct tt__MoveOptions20));

	/*Absolute*/
	timg__GetMoveOptionsResponse->MoveOptions->Absolute = (struct tt__AbsoluteFocusOptions *)soap_malloc(soap, sizeof(struct tt__AbsoluteFocusOptions));
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Position = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Position->Min = 0;
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Position->Max = 100;
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Speed = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Speed->Min = 0;
	timg__GetMoveOptionsResponse->MoveOptions->Absolute->Speed->Max = 100;

	/*Relative*/
	timg__GetMoveOptionsResponse->MoveOptions->Relative = NULL;

	/*Continuous*/
	timg__GetMoveOptionsResponse->MoveOptions->Continuous = (struct tt__ContinuousFocusOptions *)soap_malloc(soap, sizeof(struct tt__ContinuousFocusOptions));
	timg__GetMoveOptionsResponse->MoveOptions->Continuous->Speed = (struct tt__FloatRange *)soap_malloc(soap, sizeof(struct tt__FloatRange));
	timg__GetMoveOptionsResponse->MoveOptions->Continuous->Speed->Min = 1;
	timg__GetMoveOptionsResponse->MoveOptions->Continuous->Speed->Max = 1;	

	printf("[%d] __timg__GetMoveOptions exit !\n", __LINE__);

	return SOAP_OK;
	
}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetServiceCapabilities(struct soap* soap, struct _tls__GetServiceCapabilities *tls__GetServiceCapabilities, struct _tls__GetServiceCapabilitiesResponse *tls__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetLayout(struct soap* soap, struct _tls__GetLayout *tls__GetLayout, struct _tls__GetLayoutResponse *tls__GetLayoutResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetLayout(struct soap* soap, struct _tls__SetLayout *tls__SetLayout, struct _tls__SetLayoutResponse *tls__SetLayoutResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetDisplayOptions(struct soap* soap, struct _tls__GetDisplayOptions *tls__GetDisplayOptions, struct _tls__GetDisplayOptionsResponse *tls__GetDisplayOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetPaneConfigurations(struct soap* soap, struct _tls__GetPaneConfigurations *tls__GetPaneConfigurations, struct _tls__GetPaneConfigurationsResponse *tls__GetPaneConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__GetPaneConfiguration(struct soap* soap, struct _tls__GetPaneConfiguration *tls__GetPaneConfiguration, struct _tls__GetPaneConfigurationResponse *tls__GetPaneConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetPaneConfigurations(struct soap* soap, struct _tls__SetPaneConfigurations *tls__SetPaneConfigurations, struct _tls__SetPaneConfigurationsResponse *tls__SetPaneConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__SetPaneConfiguration(struct soap* soap, struct _tls__SetPaneConfiguration *tls__SetPaneConfiguration, struct _tls__SetPaneConfigurationResponse *tls__SetPaneConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__CreatePaneConfiguration(struct soap* soap, struct _tls__CreatePaneConfiguration *tls__CreatePaneConfiguration, struct _tls__CreatePaneConfigurationResponse *tls__CreatePaneConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tls__DeletePaneConfiguration(struct soap* soap, struct _tls__DeletePaneConfiguration *tls__DeletePaneConfiguration, struct _tls__DeletePaneConfigurationResponse *tls__DeletePaneConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetServiceCapabilities(struct soap* soap, struct _tmd__GetServiceCapabilities *tmd__GetServiceCapabilities, struct _tmd__GetServiceCapabilitiesResponse *tmd__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputOptions(struct soap* soap, struct _tmd__GetRelayOutputOptions *tmd__GetRelayOutputOptions, struct _tmd__GetRelayOutputOptionsResponse *tmd__GetRelayOutputOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSources(struct soap* soap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputs(struct soap* soap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

/**
 * @brief 最重要的是token的填冲
 *
 * @param soap
 * @param trt__GetVideoSources
 * @param trt__GetVideoSourcesResponse
 *
 * @return 
 */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSources(struct soap* soap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse)
{
    int i,sourceNum;
    printf("start __tmd__GetVideoSources:\n");
    sourceNum = g_GkIpc_OnvifInf.VideoSourceNum;;
    trt__GetVideoSourcesResponse->__sizeVideoSources = sourceNum;
    trt__GetVideoSourcesResponse->VideoSources = (struct tt__VideoSource *)soap_malloc(soap, sizeof(struct tt__VideoSource) * sourceNum);
    memset(trt__GetVideoSourcesResponse->VideoSources, 0, sizeof(struct tt__VideoSource)*sourceNum);
    for(i = 0; i < sourceNum; i++){
        trt__GetVideoSourcesResponse->VideoSources[i].Framerate = 30;
        trt__GetVideoSourcesResponse->VideoSources[i].Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds != NULL){
            trt__GetVideoSourcesResponse->VideoSources[i].Resolution->Width = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->width;
            trt__GetVideoSourcesResponse->VideoSources[i].Resolution->Height = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->height;
            trt__GetVideoSourcesResponse->VideoSources[i].token = (char *)soap_malloc(soap, sizeof(char)*INFO_LENGTH);
            strcpy(trt__GetVideoSourcesResponse->VideoSources[i].token,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken);
            trt__GetVideoSourcesResponse->VideoSources[i].Imaging = NULL;
            trt__GetVideoSourcesResponse->VideoSources[i].Extension = NULL;
            trt__GetVideoSourcesResponse->VideoSources[i].__anyAttribute = NULL;
        }
    }
    printf("end __tmd__GetVideoSources\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputs(struct soap* soap, struct _tmd__GetVideoOutputs *tmd__GetVideoOutputs, struct _tmd__GetVideoOutputsResponse *tmd__GetVideoOutputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfiguration(struct soap* soap, struct _tmd__GetVideoSourceConfiguration *tmd__GetVideoSourceConfiguration, struct _tmd__GetVideoSourceConfigurationResponse *tmd__GetVideoSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfiguration(struct soap* soap, struct _tmd__GetVideoOutputConfiguration *tmd__GetVideoOutputConfiguration, struct _tmd__GetVideoOutputConfigurationResponse *tmd__GetVideoOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfiguration(struct soap* soap, struct _tmd__GetAudioSourceConfiguration *tmd__GetAudioSourceConfiguration, struct _tmd__GetAudioSourceConfigurationResponse *tmd__GetAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfiguration(struct soap* soap, struct _tmd__GetAudioOutputConfiguration *tmd__GetAudioOutputConfiguration, struct _tmd__GetAudioOutputConfigurationResponse *tmd__GetAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoSourceConfiguration(struct soap* soap, struct _tmd__SetVideoSourceConfiguration *tmd__SetVideoSourceConfiguration, struct _tmd__SetVideoSourceConfigurationResponse *tmd__SetVideoSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoOutputConfiguration(struct soap* soap, struct _tmd__SetVideoOutputConfiguration *tmd__SetVideoOutputConfiguration, struct _tmd__SetVideoOutputConfigurationResponse *tmd__SetVideoOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioSourceConfiguration(struct soap* soap, struct _tmd__SetAudioSourceConfiguration *tmd__SetAudioSourceConfiguration, struct _tmd__SetAudioSourceConfigurationResponse *tmd__SetAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioOutputConfiguration(struct soap* soap, struct _tmd__SetAudioOutputConfiguration *tmd__SetAudioOutputConfiguration, struct _tmd__SetAudioOutputConfigurationResponse *tmd__SetAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfigurationOptions(struct soap* soap, struct _tmd__GetVideoSourceConfigurationOptions *tmd__GetVideoSourceConfigurationOptions, struct _tmd__GetVideoSourceConfigurationOptionsResponse *tmd__GetVideoSourceConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfigurationOptions(struct soap* soap, struct _tmd__GetVideoOutputConfigurationOptions *tmd__GetVideoOutputConfigurationOptions, struct _tmd__GetVideoOutputConfigurationOptionsResponse *tmd__GetVideoOutputConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfigurationOptions(struct soap* soap, struct _tmd__GetAudioSourceConfigurationOptions *tmd__GetAudioSourceConfigurationOptions, struct _tmd__GetAudioSourceConfigurationOptionsResponse *tmd__GetAudioSourceConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfigurationOptions(struct soap* soap, struct _tmd__GetAudioOutputConfigurationOptions *tmd__GetAudioOutputConfigurationOptions, struct _tmd__GetAudioOutputConfigurationOptionsResponse *tmd__GetAudioOutputConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputs(struct soap* soap, struct _tds__GetRelayOutputs *tds__GetRelayOutputs, struct _tds__GetRelayOutputsResponse *tds__GetRelayOutputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputSettings(struct soap* soap, struct _tmd__SetRelayOutputSettings *tmd__SetRelayOutputSettings, struct _tmd__SetRelayOutputSettingsResponse *tmd__SetRelayOutputSettingsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputState(struct soap* soap, struct _tds__SetRelayOutputState *tds__SetRelayOutputState, struct _tds__SetRelayOutputStateResponse *tds__SetRelayOutputStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetDigitalInputs(struct soap* soap, struct _tmd__GetDigitalInputs *tmd__GetDigitalInputs, struct _tmd__GetDigitalInputsResponse *tmd__GetDigitalInputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPorts(struct soap* soap, struct _tmd__GetSerialPorts *tmd__GetSerialPorts, struct _tmd__GetSerialPortsResponse *tmd__GetSerialPortsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfiguration(struct soap* soap, struct _tmd__GetSerialPortConfiguration *tmd__GetSerialPortConfiguration, struct _tmd__GetSerialPortConfigurationResponse *tmd__GetSerialPortConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetSerialPortConfiguration(struct soap* soap, struct _tmd__SetSerialPortConfiguration *tmd__SetSerialPortConfiguration, struct _tmd__SetSerialPortConfigurationResponse *tmd__SetSerialPortConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfigurationOptions(struct soap* soap, struct _tmd__GetSerialPortConfigurationOptions *tmd__GetSerialPortConfigurationOptions, struct _tmd__GetSerialPortConfigurationOptionsResponse *tmd__GetSerialPortConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tmd__SendReceiveSerialCommand(struct soap* soap, struct _tmd__SendReceiveSerialCommand *tmd__SendReceiveSerialCommand, struct _tmd__SendReceiveSerialCommandResponse *tmd__SendReceiveSerialCommandResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

static int getPTZPresetNum(char* name, const char* prefix)
{
	int num = 0;

	if (strlen(name) > strlen(prefix)) {
		if(NULL != strstr(name, prefix)) {
			num = atoi((char*)(name + strlen(prefix)));
		}
	}
	if (num > 0) {
		return num;
	}
	num = atoi(name);
	if (num > 0) {
		return num;
	}
	
	return num;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetServiceCapabilities(struct soap* soap, struct _tptz__GetServiceCapabilities *tptz__GetServiceCapabilities, struct _tptz__GetServiceCapabilitiesResponse *tptz__GetServiceCapabilitiesResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurations(struct soap* soap, struct _tptz__GetConfigurations *tptz__GetConfigurations, struct _tptz__GetConfigurationsResponse *tptz__GetConfigurationsResponse)
{
	tptz__GetConfigurationsResponse->__sizePTZConfiguration = PTZ_CONFIGURATIONS_NUM;
	tptz__GetConfigurationsResponse->PTZConfiguration = PTZConfiguration;

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresets(struct soap* soap, struct _tptz__GetPresets *tptz__GetPresets, struct _tptz__GetPresetsResponse *tptz__GetPresetsResponse)
{
	int i = 0;
	node *onvifPTZNode;
	
	onvifPTZNode = head;	
	preset_size = Get_Presets(onvifPTZNode);
	if(preset_size > 0) {
		tptz__GetPresetsResponse->__sizePreset = preset_size;
		tptz__GetPresetsResponse->Preset = (struct tt__PTZPreset*)soap_malloc(soap, sizeof(struct tt__PTZPreset) * preset_size);
		memset(tptz__GetPresetsResponse->Preset, 0, sizeof(struct tt__PTZPreset) * preset_size);

		for(i=0; i < preset_size; i++) {
			onvifPTZNode = onvifPTZNode->Next;
			tptz__GetPresetsResponse->Preset[i].Name = onvifPTZNode->Preset.PresetName; 
			tptz__GetPresetsResponse->Preset[i].token = onvifPTZNode->Preset.PresetToken;
		}
	}
	else {
		tptz__GetPresetsResponse->Preset = NULL;
	}

	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetPreset(struct soap* soap, struct _tptz__SetPreset *tptz__SetPreset, struct _tptz__SetPresetResponse *tptz__SetPresetResponse)
{
	Preset *onvifPreset;
	int num = 0;

	tptz__SetPresetResponse->PresetToken = (char*)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
	if (NULL != tptz__SetPreset->ProfileToken) {
		printf("__tptz__SetPreset profile token %s\n", tptz__SetPreset->ProfileToken);
	}
	else {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", NULL);
	}
	
	if (NULL != tptz__SetPreset->PresetName) {
		printf("__tptz__SetPreset Preset Name %s\n", tptz__SetPreset->PresetName);
		num = getPTZPresetNum(tptz__SetPreset->PresetName, ONVIF_PTZ_PRESET_NAME_PREFIX);
	}
	if(NULL != tptz__SetPreset->PresetToken && !num) {
		printf("__tptz__SetPreset Preset Token %s\n", tptz__SetPreset->PresetToken);
		num = getPTZPresetNum(tptz__SetPreset->PresetToken, ONVIF_PTZ_PRESET_TOKEN_PREFIX);
	}
	
	if(num <= 0) {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidPresetName", NULL);
	}

	onvifPreset = (Preset*)soap_malloc(soap, sizeof(Preset));
	memset(onvifPreset, 0, sizeof(onvifPreset));
	onvifPreset->Num = num;
	memcpy(onvifPreset->ProfileToken, tptz__SetPreset->ProfileToken, strlen(tptz__SetPreset->ProfileToken));
	if(tptz__SetPreset->PresetToken == NULL) {
		sprintf(onvifPreset->PresetToken, "%s%d", ONVIF_PTZ_PRESET_TOKEN_PREFIX, num);
	}
	else {
		memcpy(onvifPreset->PresetToken, tptz__SetPreset->PresetToken, strlen(tptz__SetPreset->PresetToken));
	}
	if(tptz__SetPreset->PresetName == NULL) {
		sprintf(tptz__SetPreset->PresetName, "%s%d", ONVIF_PTZ_PRESET_NAME_PREFIX, num);
	}
	else {
		memcpy(onvifPreset->PresetName, tptz__SetPreset->PresetName, strlen(tptz__SetPreset->PresetName));
	}
	memcpy(tptz__SetPresetResponse->PresetToken, onvifPreset->PresetToken, strlen(onvifPreset->PresetToken));
	
	if(!Add_Preset(onvifPreset)) {
		Set_Pesets();
	}
	else{
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:The preset already exists", NULL);
	}
	
	return SOAP_OK;

	
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RemovePreset(struct soap* soap, struct _tptz__RemovePreset *tptz__RemovePreset, struct _tptz__RemovePresetResponse *tptz__RemovePresetResponse)
{
	Preset *onvifPreset;
	int num;

	if (NULL != tptz__RemovePreset->ProfileToken) {
		printf("__tptz__SetPreset profile token %s\n", tptz__RemovePreset->ProfileToken);
	}
	else {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", NULL);
	}
	if (NULL != tptz__RemovePreset->PresetToken) {
		printf("__tptz__SetPreset Preset Token %s\n", tptz__RemovePreset->PresetToken);
		num = getPTZPresetNum(tptz__RemovePreset->PresetToken, ONVIF_PTZ_PRESET_TOKEN_PREFIX);		
	}
	else {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoToken", NULL);
	}

	if(num <= 0) {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidPresetToken", NULL);
	}
		
	onvifPreset = (Preset*)soap_malloc(soap, sizeof(Preset));
	memset(onvifPreset, 0, sizeof(onvifPreset));
	onvifPreset->Num = num;
	memcpy(onvifPreset->ProfileToken, tptz__RemovePreset->ProfileToken, strlen(tptz__RemovePreset->ProfileToken));
	memcpy(onvifPreset->PresetToken, tptz__RemovePreset->PresetToken, strlen(tptz__RemovePreset->PresetToken));

	if(!Delete_Preset(onvifPreset)) {
		Set_Pesets();
	}
	else {
		ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:The preset not exists", NULL);
	}
	
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoPreset(struct soap* soap, struct _tptz__GotoPreset *tptz__GotoPreset, struct _tptz__GotoPresetResponse *tptz__GotoPresetResponse)
{
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetStatus(struct soap* soap, struct _tptz__GetStatus *tptz__GetStatus, struct _tptz__GetStatusResponse *tptz__GetStatusResponse)
{	
	tptz__GetStatusResponse->PTZStatus = (struct tt__PTZStatus*)soap_malloc(soap, sizeof(struct tt__PTZStatus));
	memset(tptz__GetStatusResponse->PTZStatus, 0, sizeof(struct tt__PTZStatus));	

	time(&tptz__GetStatusResponse->PTZStatus->UtcTime);
	
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfiguration(struct soap* soap, struct _tptz__GetConfiguration *tptz__GetConfiguration, struct _tptz__GetConfigurationResponse *tptz__GetConfigurationResponse)
{
	int i = 0;

	for(i = 0; i < PTZ_CONFIGURATIONS_NUM; i++) {
		if(!strcmp(tptz__GetConfiguration->PTZConfigurationToken, PTZConfiguration[i].token)){
			tptz__GetConfigurationResponse->PTZConfiguration = &PTZConfiguration[i];
			break;
		}	
	}

	if(i == PTZ_CONFIGURATIONS_NUM) {
		 ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:No such Config", NULL);
	}
	return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNodes(struct soap* soap, struct _tptz__GetNodes *tptz__GetNodes, struct _tptz__GetNodesResponse *tptz__GetNodesResponse)
{
    tptz__GetNodesResponse->__sizePTZNode = 1;
    tptz__GetNodesResponse->PTZNode = (struct tt__PTZNode*)soap_malloc(soap, tptz__GetNodesResponse->__sizePTZNode * sizeof(struct tt__PTZNode));
    memset(tptz__GetNodesResponse->PTZNode, 0 ,tptz__GetNodesResponse->__sizePTZNode * sizeof(struct tt__PTZNode));

    tptz__GetNodesResponse->PTZNode->token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);	
    strcpy(tptz__GetNodesResponse->PTZNode->token, "Hdwlink HSD PTZ");

    tptz__GetNodesResponse->PTZNode->Name = (char *)soap_malloc(soap, sizeof(char) * PTZ_DEVICE_NAME);
    strcpy(tptz__GetNodesResponse->PTZNode->Name, "Hdwlink HSD PTZ");

    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces = (struct tt__PTZSpaces*)soap_malloc(soap, sizeof(struct tt__PTZSpaces));	
    memset(tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces, 0 ,sizeof(struct tt__PTZSpaces));

    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->__sizeContinuousPanTiltVelocitySpace = 1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace = (struct tt__Space2DDescription*)soap_malloc(soap, sizeof(struct tt__Space2DDescription));
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace");
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange->Min = -1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange->Max= 1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange->Min = -1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange->Max= 1;

    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->__sizeContinuousZoomVelocitySpace= 1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace = (struct tt__Space1DDescription*)soap_malloc(soap, sizeof(struct tt__Space1DDescription));
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace");
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange->Min = -1;
    tptz__GetNodesResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange->Max= 1;

    tptz__GetNodesResponse->PTZNode->MaximumNumberOfPresets = 64;

    tptz__GetNodesResponse->PTZNode->HomeSupported = xsd__boolean__false_;

    tptz__GetNodesResponse->PTZNode->Extension = (struct tt__PTZNodeExtension*)soap_malloc(soap, sizeof(struct tt__PTZNodeExtension));	
    tptz__GetNodesResponse->PTZNode->Extension->__size = 0;
    tptz__GetNodesResponse->PTZNode->Extension->__any = NULL;
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour = (struct tt__PTZPresetTourSupported*)soap_malloc(soap, sizeof(struct tt__PTZPresetTourSupported));	
    memset(tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour, 0 ,sizeof(struct tt__PTZPresetTourSupported));
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->MaximumNumberOfPresetTours = 4;
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->__sizePTZPresetTourOperation = 3;
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation = \
                                                                                              (enum tt__PTZPresetTourOperation*)soap_malloc(soap, tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->__sizePTZPresetTourOperation * sizeof(enum tt__PTZPresetTourOperation));
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[0] = tt__PTZPresetTourOperation__Start;
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[1] = tt__PTZPresetTourOperation__Stop;
    tptz__GetNodesResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[2] = tt__PTZPresetTourOperation__Pause;

    tptz__GetNodesResponse->PTZNode->Extension->Extension = NULL;

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetNode(struct soap* soap, struct _tptz__GetNode *tptz__GetNode, struct _tptz__GetNodeResponse *tptz__GetNodeResponse)
{
    if(!strcmp(tptz__GetNode->NodeToken, "Hdwlink HSD PTZ")) {
        tptz__GetNodeResponse->PTZNode = (struct tt__PTZNode*)soap_malloc(soap, sizeof(struct tt__PTZNode));
        memset(tptz__GetNodeResponse->PTZNode, 0 ,sizeof(struct tt__PTZNode));

        tptz__GetNodeResponse->PTZNode->token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);	
        strcpy(tptz__GetNodeResponse->PTZNode->token, "Hdwlink HSD PTZ");

        tptz__GetNodeResponse->PTZNode->Name = (char *)soap_malloc(soap, sizeof(char) * PTZ_DEVICE_NAME);
        strcpy(tptz__GetNodeResponse->PTZNode->Name, "Hdwlink HSD PTZ");

        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces = (struct tt__PTZSpaces*)soap_malloc(soap, sizeof(struct tt__PTZSpaces));	
        memset(tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces, 0 ,sizeof(struct tt__PTZSpaces));

        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->__sizeContinuousPanTiltVelocitySpace = 1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace = (struct tt__Space2DDescription*)soap_malloc(soap, sizeof(struct tt__Space2DDescription));
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
        strcpy(tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace");
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange->Min = -1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->XRange->Max= 1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange->Min = -1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousPanTiltVelocitySpace->YRange->Max= 1;

        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->__sizeContinuousZoomVelocitySpace= 1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace = (struct tt__Space1DDescription*)soap_malloc(soap, sizeof(struct tt__Space1DDescription));
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
        strcpy(tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace");
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange->Min = -1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->ContinuousZoomVelocitySpace->XRange->Max= 1;

        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->__sizePanTiltSpeedSpace= 1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace = (struct tt__Space1DDescription*)soap_malloc(soap, sizeof(struct tt__Space1DDescription));
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
        strcpy(tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace->URI, "http://www.onvif.org/ver10/tptz/PanTiltSpaces/GenericSpeedSpace");
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace->XRange->Min = -1;
        tptz__GetNodeResponse->PTZNode->SupportedPTZSpaces->PanTiltSpeedSpace->XRange->Max= 1;

        tptz__GetNodeResponse->PTZNode->MaximumNumberOfPresets = 64;

        tptz__GetNodeResponse->PTZNode->HomeSupported = xsd__boolean__false_;

        tptz__GetNodeResponse->PTZNode->Extension = (struct tt__PTZNodeExtension*)soap_malloc(soap, sizeof(struct tt__PTZNodeExtension));	
        tptz__GetNodeResponse->PTZNode->Extension->__size = 0;
        tptz__GetNodeResponse->PTZNode->Extension->__any = NULL;
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour = (struct tt__PTZPresetTourSupported*)soap_malloc(soap, sizeof(struct tt__PTZPresetTourSupported));	
        memset(tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour, 0 ,sizeof(struct tt__PTZPresetTourSupported));
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->MaximumNumberOfPresetTours = 4;
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->__sizePTZPresetTourOperation = 3;
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation = \
                                                                                                 (enum tt__PTZPresetTourOperation*)soap_malloc(soap, tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->__sizePTZPresetTourOperation * sizeof(enum tt__PTZPresetTourOperation));
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[0] = tt__PTZPresetTourOperation__Start;
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[1] = tt__PTZPresetTourOperation__Stop;
        tptz__GetNodeResponse->PTZNode->Extension->SupportedPresetTour->PTZPresetTourOperation[2] = tt__PTZPresetTourOperation__Pause;

        tptz__GetNodeResponse->PTZNode->Extension->Extension = NULL;
    }
    else {
        goto invalid_arg;
    }
    return SOAP_OK;

invalid_arg:
    ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:No such PTZ node", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetConfiguration(struct soap* soap, struct _tptz__SetConfiguration *tptz__SetConfiguration, struct _tptz__SetConfigurationResponse *tptz__SetConfigurationResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetConfigurationOptions(struct soap* soap, struct _tptz__GetConfigurationOptions *tptz__GetConfigurationOptions, struct _tptz__GetConfigurationOptionsResponse *tptz__GetConfigurationOptionsResponse)
{
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions = (struct tt__PTZConfigurationOptions*)soap_malloc(soap, sizeof(struct tt__PTZConfigurationOptions));
    memset(tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions, 0 , sizeof(struct tt__PTZConfigurationOptions));

    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces = (struct tt__PTZSpaces*)soap_malloc(soap, sizeof(struct tt__PTZSpaces));
    memset(tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces, 0 , sizeof(struct tt__PTZSpaces));

    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->__sizeContinuousPanTiltVelocitySpace = 1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace = (struct tt__Space2DDescription*)soap_malloc(soap, sizeof(struct tt__Space2DDescription));
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/PanTiltSpaces/VelocityGenericSpace");
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->XRange->Min = -1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->XRange->Max= 1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->YRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->YRange->Min = -1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousPanTiltVelocitySpace->YRange->Max= 1;

    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->__sizeContinuousZoomVelocitySpace = 1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace = (struct tt__Space1DDescription*)soap_malloc(soap, sizeof(struct tt__Space1DDescription));
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace->URI = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace->URI, "http://www.onvif.org/ver10/tptz/ZoomSpaces/VelocityGenericSpace");
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace->XRange = (struct tt__FloatRange*)soap_malloc(soap, sizeof(struct tt__FloatRange));	
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace->XRange->Min = -1;
    tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->Spaces->ContinuousZoomVelocitySpace->XRange->Max= 1;

		tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->PTZTimeout = (struct tt__DurationRange*)soap_malloc(soap, sizeof(struct tt__DurationRange));
		tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->PTZTimeout->Min = 10;
		tptz__GetConfigurationOptionsResponse->PTZConfigurationOptions->PTZTimeout->Max = 1000;

    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GotoHomePosition(struct soap* soap, struct _tptz__GotoHomePosition *tptz__GotoHomePosition, struct _tptz__GotoHomePositionResponse *tptz__GotoHomePositionResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SetHomePosition(struct soap* soap, struct _tptz__SetHomePosition *tptz__SetHomePosition, struct _tptz__SetHomePositionResponse *tptz__SetHomePositionResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__ContinuousMove(struct soap* soap, struct _tptz__ContinuousMove *tptz__ContinuousMove, struct _tptz__ContinuousMoveResponse *tptz__ContinuousMoveResponse)
{	
	if (NULL != tptz__ContinuousMove->Velocity->PanTilt) {
		if (NULL != tptz__ContinuousMove->Velocity->PanTilt->space)
			printf("__tptz__ContinuousMove pantilt x:%f y:%f space:%s", \
						tptz__ContinuousMove->Velocity->PanTilt->x, \
						tptz__ContinuousMove->Velocity->PanTilt->y, \
						tptz__ContinuousMove->Velocity->PanTilt->space);
		else
			printf("__tptz__ContinuousMove pantilt x:%f y:%f", \
						tptz__ContinuousMove->Velocity->PanTilt->x, \
						tptz__ContinuousMove->Velocity->PanTilt->y);
	}
	if (NULL != tptz__ContinuousMove->Velocity->Zoom) {
		if (NULL != tptz__ContinuousMove->Velocity->Zoom->space)
			printf("__tptz__ContinuousMove Zoom x:%f space:%s",
						tptz__ContinuousMove->Velocity->Zoom->x, \
						tptz__ContinuousMove->Velocity->Zoom->space); \
		else
			printf("__tptz__ContinuousMove Zoom x:%f",
						tptz__ContinuousMove->Velocity->Zoom->x); 
	}
	printf(" start __tptz__ContinuousMove\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RelativeMove(struct soap* soap, struct _tptz__RelativeMove *tptz__RelativeMove, struct _tptz__RelativeMoveResponse *tptz__RelativeMoveResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__SendAuxiliaryCommand(struct soap* soap, struct _tptz__SendAuxiliaryCommand *tptz__SendAuxiliaryCommand, struct _tptz__SendAuxiliaryCommandResponse *tptz__SendAuxiliaryCommandResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__AbsoluteMove(struct soap* soap, struct _tptz__AbsoluteMove *tptz__AbsoluteMove, struct _tptz__AbsoluteMoveResponse *tptz__AbsoluteMoveResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__Stop(struct soap* soap, struct _tptz__Stop *tptz__Stop, struct _tptz__StopResponse *tptz__StopResponse)
{
	return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTours(struct soap* soap, struct _tptz__GetPresetTours *tptz__GetPresetTours, struct _tptz__GetPresetToursResponse *tptz__GetPresetToursResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTour(struct soap* soap, struct _tptz__GetPresetTour *tptz__GetPresetTour, struct _tptz__GetPresetTourResponse *tptz__GetPresetTourResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetPresetTourOptions(struct soap* soap, struct _tptz__GetPresetTourOptions *tptz__GetPresetTourOptions, struct _tptz__GetPresetTourOptionsResponse *tptz__GetPresetTourOptionsResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__CreatePresetTour(struct soap* soap, struct _tptz__CreatePresetTour *tptz__CreatePresetTour, struct _tptz__CreatePresetTourResponse *tptz__CreatePresetTourResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__ModifyPresetTour(struct soap* soap, struct _tptz__ModifyPresetTour *tptz__ModifyPresetTour, struct _tptz__ModifyPresetTourResponse *tptz__ModifyPresetTourResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__OperatePresetTour(struct soap* soap, struct _tptz__OperatePresetTour *tptz__OperatePresetTour, struct _tptz__OperatePresetTourResponse *tptz__OperatePresetTourResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__RemovePresetTour(struct soap* soap, struct _tptz__RemovePresetTour *tptz__RemovePresetTour, struct _tptz__RemovePresetTourResponse *tptz__RemovePresetTourResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tptz__GetCompatibleConfigurations(struct soap* soap, struct _tptz__GetCompatibleConfigurations *tptz__GetCompatibleConfigurations, struct _tptz__GetCompatibleConfigurationsResponse *tptz__GetCompatibleConfigurationsResponse)
{
	ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetServiceCapabilities(struct soap* soap, struct _trc__GetServiceCapabilities *trc__GetServiceCapabilities, struct _trc__GetServiceCapabilitiesResponse *trc__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateRecording(struct soap* soap, struct _trc__CreateRecording *trc__CreateRecording, struct _trc__CreateRecordingResponse *trc__CreateRecordingResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteRecording(struct soap* soap, struct _trc__DeleteRecording *trc__DeleteRecording, struct _trc__DeleteRecordingResponse *trc__DeleteRecordingResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordings(struct soap* soap, struct _trc__GetRecordings *trc__GetRecordings, struct _trc__GetRecordingsResponse *trc__GetRecordingsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingConfiguration(struct soap* soap, struct _trc__SetRecordingConfiguration *trc__SetRecordingConfiguration, struct _trc__SetRecordingConfigurationResponse *trc__SetRecordingConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingConfiguration(struct soap* soap, struct _trc__GetRecordingConfiguration *trc__GetRecordingConfiguration, struct _trc__GetRecordingConfigurationResponse *trc__GetRecordingConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingOptions(struct soap* soap, struct _trc__GetRecordingOptions *trc__GetRecordingOptions, struct _trc__GetRecordingOptionsResponse *trc__GetRecordingOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateTrack(struct soap* soap, struct _trc__CreateTrack *trc__CreateTrack, struct _trc__CreateTrackResponse *trc__CreateTrackResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteTrack(struct soap* soap, struct _trc__DeleteTrack *trc__DeleteTrack, struct _trc__DeleteTrackResponse *trc__DeleteTrackResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetTrackConfiguration(struct soap* soap, struct _trc__GetTrackConfiguration *trc__GetTrackConfiguration, struct _trc__GetTrackConfigurationResponse *trc__GetTrackConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetTrackConfiguration(struct soap* soap, struct _trc__SetTrackConfiguration *trc__SetTrackConfiguration, struct _trc__SetTrackConfigurationResponse *trc__SetTrackConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__CreateRecordingJob(struct soap* soap, struct _trc__CreateRecordingJob *trc__CreateRecordingJob, struct _trc__CreateRecordingJobResponse *trc__CreateRecordingJobResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__DeleteRecordingJob(struct soap* soap, struct _trc__DeleteRecordingJob *trc__DeleteRecordingJob, struct _trc__DeleteRecordingJobResponse *trc__DeleteRecordingJobResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobs(struct soap* soap, struct _trc__GetRecordingJobs *trc__GetRecordingJobs, struct _trc__GetRecordingJobsResponse *trc__GetRecordingJobsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingJobConfiguration(struct soap* soap, struct _trc__SetRecordingJobConfiguration *trc__SetRecordingJobConfiguration, struct _trc__SetRecordingJobConfigurationResponse *trc__SetRecordingJobConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobConfiguration(struct soap* soap, struct _trc__GetRecordingJobConfiguration *trc__GetRecordingJobConfiguration, struct _trc__GetRecordingJobConfigurationResponse *trc__GetRecordingJobConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__SetRecordingJobMode(struct soap* soap, struct _trc__SetRecordingJobMode *trc__SetRecordingJobMode, struct _trc__SetRecordingJobModeResponse *trc__SetRecordingJobModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trc__GetRecordingJobState(struct soap* soap, struct _trc__GetRecordingJobState *trc__GetRecordingJobState, struct _trc__GetRecordingJobStateResponse *trc__GetRecordingJobStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetServiceCapabilities(struct soap* soap, struct _trp__GetServiceCapabilities *trp__GetServiceCapabilities, struct _trp__GetServiceCapabilitiesResponse *trp__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetReplayUri(struct soap* soap, struct _trp__GetReplayUri *trp__GetReplayUri, struct _trp__GetReplayUriResponse *trp__GetReplayUriResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trp__GetReplayConfiguration(struct soap* soap, struct _trp__GetReplayConfiguration *trp__GetReplayConfiguration, struct _trp__GetReplayConfigurationResponse *trp__GetReplayConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trp__SetReplayConfiguration(struct soap* soap, struct _trp__SetReplayConfiguration *trp__SetReplayConfiguration, struct _trp__SetReplayConfigurationResponse *trp__SetReplayConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetServiceCapabilities(struct soap* soap, struct _trt__GetServiceCapabilities *trt__GetServiceCapabilities, struct _trt__GetServiceCapabilitiesResponse *trt__GetServiceCapabilitiesResponse)
{
	printf("start __trt__GetServiceCapabilities");
	trt__GetServiceCapabilitiesResponse->Capabilities = (struct trt__Capabilities *)soap_malloc(soap, sizeof(struct trt__Capabilities));
	soap_default_trt__Capabilities(soap, trt__GetServiceCapabilitiesResponse->Capabilities);
	return SOAP_OK;
	printf("ent __trt__GetServiceCapabilities");
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSources(struct soap* soap, struct _trt__GetVideoSources *trt__GetVideoSources, struct _trt__GetVideoSourcesResponse *trt__GetVideoSourcesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSources(struct soap* soap, struct _trt__GetAudioSources *trt__GetAudioSources, struct _trt__GetAudioSourcesResponse *trt__GetAudioSourcesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputs(struct soap* soap, struct _trt__GetAudioOutputs *trt__GetAudioOutputs, struct _trt__GetAudioOutputsResponse *trt__GetAudioOutputsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateProfile(struct soap* soap, struct _trt__CreateProfile *trt__CreateProfile, struct _trt__CreateProfileResponse *trt__CreateProfileResponse)
{
	int i = 0;
    printf(" start __trt__CreateProfile\n");
    if (NULL == trt__CreateProfile->Name && NULL == trt__CreateProfile->Token)
    {
        goto InvalArgValNull;//ArgVal Err
    }
    printf(" Name:%s, Token:%s\n",trt__CreateProfile->Name, trt__CreateProfile->Token);
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
			if(trt__CreateProfile->Name != NULL){
			    if(strcmp(trt__CreateProfile->Name,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name) == 0){
	        		goto InvalArgValExist;//Profile Exist
			    }
			}
			if(trt__CreateProfile->Token != NULL){
			    if(strcmp(trt__CreateProfile->Token,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
	        		goto InvalArgValExist;//Profile Exist
			    }
			}
	}

    for(i = 0; i < MAX_PROFILE_NUM; i++){
		if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token == NULL && g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name == NULL){

			trt__CreateProfileResponse->Profile = (struct tt__Profile *)soap_malloc(soap, sizeof(struct tt__Profile));
			soap_default_tt__Profile(soap, trt__CreateProfileResponse->Profile);


            /*Name*/
            g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name = (char *)malloc(sizeof(char) * MAX_PROF_TOKEN);
            memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name, 0, MAX_PROF_TOKEN);
			if(trt__CreateProfile->Name == NULL){
            	sprintf(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name, "Profile%d",i);
			}
			else
			{
            	strcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name, trt__CreateProfile->Name);
			}
			trt__CreateProfileResponse->Profile->Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
			strcpy(trt__CreateProfileResponse->Profile->Name , g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name);



            /*Token*/
            g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token= (char *)malloc(sizeof(char) * MAX_PROF_TOKEN);
            memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token, 0, MAX_PROF_TOKEN);
			if(trt__CreateProfile->Token == NULL){
            	sprintf(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token, "ProfileToken%d",i);
			}
			else
			{
            	strcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token, trt__CreateProfile->Token);
			}
			trt__CreateProfileResponse->Profile->token= (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
			strcpy(trt__CreateProfileResponse->Profile->token , g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);



			/*Fixed*/
			g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed = (enum xsd__boolean *)malloc(sizeof(enum xsd__boolean));
            memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed, 0, sizeof(enum xsd__boolean));
			*g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed = xsd__boolean__false_;

			trt__CreateProfileResponse->Profile->fixed  = (enum xsd__boolean *)soap_malloc(soap, sizeof(enum xsd__boolean));
            memset(trt__CreateProfileResponse->Profile->fixed, 0, sizeof(enum xsd__boolean));
            memcpy(trt__CreateProfileResponse->Profile->fixed, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed, sizeof(enum xsd__boolean));

			g_GkIpc_OnvifInf.ProfileNum++;
			break;
		}
	}

	if(i == MAX_PROFILE_NUM){
		goto MaxProfile;//device has max profile
	}
    printf("end __trt__CreateProfile\n");
    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:ProfileExists", "profile exists", NULL);
MaxProfile:
	ONVIF_RECEIVER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:MaxNVTProfiles", "max profile", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfile(struct soap* soap, struct _trt__GetProfile *trt__GetProfile, struct _trt__GetProfileResponse *trt__GetProfileResponse)
{
    printf("start __trt__GetProfile\n");
    int i;
    if(trt__GetProfile){
        printf("trt__GetProfile=%s\n",trt__GetProfile->ProfileToken );
    }
    trt__GetProfileResponse->Profile =(struct tt__Profile *)soap_malloc(soap, sizeof(struct tt__Profile));
    memset(trt__GetProfileResponse->Profile, 0, sizeof(trt__GetProfileResponse->Profile));
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
    {
        if(strcmp(trt__GetProfile->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
            /*Name*/
            trt__GetProfileResponse->Profile->Name = (char *)soap_malloc(soap,sizeof(char) * MAX_PROF_TOKEN);
            memset(trt__GetProfileResponse->Profile->Name, 0, MAX_PROF_TOKEN);
            strcpy(trt__GetProfileResponse->Profile->Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name);
            /*Token*/
            trt__GetProfileResponse->Profile->token= (char *)soap_malloc(soap,sizeof(char) * MAX_PROF_TOKEN);
            memset(trt__GetProfileResponse->Profile->token, 0, MAX_PROF_TOKEN);
            strcpy(trt__GetProfileResponse->Profile->token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
            /*Fixed*/
            trt__GetProfileResponse->Profile->fixed  = (enum xsd__boolean *)soap_malloc(soap, sizeof(enum xsd__boolean));
            memset(trt__GetProfileResponse->Profile->fixed, 0, sizeof(enum xsd__boolean));
            memcpy(trt__GetProfileResponse->Profile->fixed, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed, sizeof(enum xsd__boolean));


            printf("Profile Name:%s,Token:%s,fixed:%d\n",trt__GetProfileResponse->Profile->Name,
                    trt__GetProfileResponse->Profile->token,
                    *trt__GetProfileResponse->Profile->fixed);


            /*VideoSourceConfiguration*/
            trt__GetProfileResponse->Profile->VideoSourceConfiguration = (struct tt__VideoSourceConfiguration *)soap_malloc(soap,sizeof(struct tt__VideoSourceConfiguration));
            memset(trt__GetProfileResponse->Profile->VideoSourceConfiguration, 0, sizeof(struct tt__VideoSourceConfiguration));

            trt__GetProfileResponse->Profile->VideoSourceConfiguration->Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name != NULL){
                strcpy(trt__GetProfileResponse->Profile->VideoSourceConfiguration->Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name);
            }

            trt__GetProfileResponse->Profile->VideoSourceConfiguration->token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token != NULL){
                strcpy(trt__GetProfileResponse->Profile->VideoSourceConfiguration->token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token);
            }

            trt__GetProfileResponse->Profile->VideoSourceConfiguration->SourceToken = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken != NULL){
                strcpy(trt__GetProfileResponse->Profile->VideoSourceConfiguration->SourceToken, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken);
            }

            trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds = (struct tt__IntRectangle *)soap_malloc(soap, sizeof(struct tt__IntRectangle));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds != NULL){
                memcpy(trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds, sizeof(struct tt__IntRectangle));
            }
            trt__GetProfileResponse->Profile->VideoSourceConfiguration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->UseCount;



            printf("VideoSourceConfiguration Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->Name,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->token,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->SourceToken,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds->x,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds->y,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds->width,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->Bounds->height,
                    trt__GetProfileResponse->Profile->VideoSourceConfiguration->UseCount);

            /*VideoEncoderConfiguration*/
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration = (struct tt__VideoEncoderConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration));
            memset(trt__GetProfileResponse->Profile->VideoEncoderConfiguration, 0, sizeof(struct tt__VideoEncoderConfiguration));

            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Name = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name != NULL){
                strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name);
            }
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token != NULL){
                strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token);
            }
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->UseCount;
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Encoding = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Encoding;//2;//JPEG = 0, MPEG4 = 1, H264 = 2;
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution != NULL){
                memcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution, sizeof(struct tt__VideoResolution));
            }
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Quality =  g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Quality;
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl = (struct tt__VideoRateControl *)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl != NULL){
                memcpy((char *)trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl, sizeof(struct tt__VideoRateControl));
            }

            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->MPEG4 = NULL;

            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264 != NULL){
                memcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264, sizeof(struct tt__H264Configuration));
            }
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast = (struct tt__MulticastConfiguration *)soap_malloc(soap, sizeof(struct tt__MulticastConfiguration));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast != NULL){
                if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address!= NULL){
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address = (struct tt__IPAddress *)soap_malloc(soap, sizeof(struct tt__IPAddress));
                    memset(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address, 0, sizeof(struct tt__IPAddress));
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->Type = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->Type;
                    if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address != NULL){
                        trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv4Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv4Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address);

                    }
                    if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address != NULL){
                        trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv6Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Address->IPv6Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address);
                    }
                }
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Port = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Port;
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->TTL = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->TTL;
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->AutoStart= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->AutoStart;
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__size= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->__size;
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__any = NULL;
                trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->__anyAttribute = NULL;
            }
            trt__GetProfileResponse->Profile->VideoEncoderConfiguration->SessionTimeout = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->SessionTimeout;


            printf("VideoEncoderConfiguration Name:%s,Token:%s,UseCount:%d,Encoding:%d,Width:%d,Height:%d,Quality:%f,BitrateLimit:%d,EncodingInterval:%d,FrameRateLimit:%d\n",
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Name,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->token,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->UseCount,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Encoding,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution->Width,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Resolution->Height,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Quality,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->BitrateLimit,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->EncodingInterval,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->RateControl->FrameRateLimit);


            printf("GovLength:%d,H264Profile:%d,Port:%d,TTL:%d,AutoStart:%d,SessionTimeout:%lld\n",
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264->GovLength,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->H264->H264Profile,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->Port,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->TTL,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->Multicast->AutoStart,
                    trt__GetProfileResponse->Profile->VideoEncoderConfiguration->SessionTimeout);

            trt__GetProfileResponse->Profile->AudioSourceConfiguration = NULL;
            trt__GetProfileResponse->Profile->AudioEncoderConfiguration = NULL;
            trt__GetProfileResponse->Profile->VideoAnalyticsConfiguration = NULL;
            trt__GetProfileResponse->Profile->PTZConfiguration = NULL;
            trt__GetProfileResponse->Profile->MetadataConfiguration = NULL;
            trt__GetProfileResponse->Profile->Extension = NULL;
            trt__GetProfileResponse->Profile->__anyAttribute = NULL;
            break;
        }
    }	

	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto NoProfile;
	}
    printf("end __trt__GetProfile\n");
    return SOAP_OK;
NoProfile:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
}

/**
 * @brief 需要和GetVideoSources的token匹配一致
 *         需要填充VideoSourceConfiguration和VideoEncoderConfiguration
 * @param soap
 * @param trt__GetProfiles
 * @param trt__GetProfilesResponse
 *
 * @return 
 */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfiles(struct soap* soap, struct _trt__GetProfiles *trt__GetProfiles, struct _trt__GetProfilesResponse *trt__GetProfilesResponse)
{
    int i=0;
    int size;
    printf("start __trt__GetProfiles\n");
    size = g_GkIpc_OnvifInf.ProfileNum;//profile num
    trt__GetProfilesResponse->Profiles =(struct tt__Profile *)soap_malloc(soap, sizeof(struct tt__Profile) * size);
    memset(trt__GetProfilesResponse->Profiles, 0, sizeof(struct tt__Profile) * size);
    trt__GetProfilesResponse->__sizeProfiles = size;
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
        /*Name*/
        trt__GetProfilesResponse->Profiles[i].Name = (char *)soap_malloc(soap,sizeof(char) * MAX_PROF_TOKEN);
        memset(trt__GetProfilesResponse->Profiles[i].Name, 0, MAX_PROF_TOKEN);
        strcpy(trt__GetProfilesResponse->Profiles[i].Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name);
        /*Token*/
        trt__GetProfilesResponse->Profiles[i].token= (char *)soap_malloc(soap,sizeof(char) * MAX_PROF_TOKEN);
        memset(trt__GetProfilesResponse->Profiles[i].token, 0, MAX_PROF_TOKEN);
        strcpy(trt__GetProfilesResponse->Profiles[i].token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
        /*Fixed*/
        trt__GetProfilesResponse->Profiles[i].fixed  = (enum xsd__boolean  *)soap_malloc(soap, sizeof(enum xsd__boolean));
        memset(trt__GetProfilesResponse->Profiles[i].fixed, 0, sizeof(enum xsd__boolean));
        memcpy(trt__GetProfilesResponse->Profiles[i].fixed, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed, sizeof(enum xsd__boolean));


        printf("Profile Name:%s,Token:%s,fixed:%d\n",trt__GetProfilesResponse->Profiles[i].Name,
                trt__GetProfilesResponse->Profiles[i].token,
                *trt__GetProfilesResponse->Profiles[i].fixed);


        /*VideoSourceConfiguration*/
        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration = (struct tt__VideoSourceConfiguration *)soap_malloc(soap,sizeof(struct tt__VideoSourceConfiguration));
        memset(trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration, 0, sizeof(struct tt__VideoSourceConfiguration));

        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name != NULL){
            strcpy(trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name);
        }

        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token != NULL){
            strcpy(trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token);
        }

        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->SourceToken = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken != NULL){
            strcpy(trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->SourceToken, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken);
        }

        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds = (struct tt__IntRectangle *)soap_malloc(soap, sizeof(struct tt__IntRectangle));
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds != NULL){
            memcpy(trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds, sizeof(struct tt__IntRectangle));
        }
        trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->UseCount;



        printf("VideoSourceConfiguration Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Name,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->token,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->SourceToken,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds->x,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds->y,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds->width,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->Bounds->height,
                trt__GetProfilesResponse->Profiles[i].VideoSourceConfiguration->UseCount);

        /*VideoEncoderConfiguration*/
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration = (struct tt__VideoEncoderConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration));
        memset(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration, 0, sizeof(struct tt__VideoEncoderConfiguration));

        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Name = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name != NULL){
            strcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name);
        }
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token != NULL){
            strcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token);
        }
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->UseCount;
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Encoding = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Encoding;//2;//JPEG = 0, MPEG4 = 1, H264 = 2;
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution != NULL){
            memcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Resolution, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution, sizeof(struct tt__VideoResolution));
        }
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Quality =  g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Quality;
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->RateControl = (struct tt__VideoRateControl *)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl != NULL){
            memcpy((char *)trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->RateControl, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl, sizeof(struct tt__VideoRateControl));
        }

        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->MPEG4 = NULL;


        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264 != NULL){
            memcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->H264, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264, sizeof(struct tt__H264Configuration));
        }
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast = (struct tt__MulticastConfiguration *)soap_malloc(soap, sizeof(struct tt__MulticastConfiguration));
        if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast != NULL){
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address!= NULL){
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address = (struct tt__IPAddress *)soap_malloc(soap, sizeof(struct tt__IPAddress));
                memset(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address, 0, sizeof(struct tt__IPAddress));
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address->Type = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->Type;
                if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address != NULL){
                    trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                    strcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address);

                }
                if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address != NULL){
                    trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                    strcpy(trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address);
                }
            }
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Port = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Port;
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->TTL = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->TTL;
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->AutoStart= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->AutoStart;
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->__size= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->__size;
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->__any = NULL;
            trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->__anyAttribute = NULL;
        }
        trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->SessionTimeout = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->SessionTimeout;


        printf("VideoEncoderConfiguration Name:%s,Token:%s,UseCount:%d,Encoding:%d,Width:%d,Height:%d,Quality:%f,BitrateLimit:%d,EncodingInterval:%d,FrameRateLimit:%d\n",
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Name,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->token,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->UseCount,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Encoding,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Resolution->Width,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Resolution->Height,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Quality,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->RateControl->BitrateLimit,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->RateControl->EncodingInterval,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->RateControl->FrameRateLimit);


        printf("GovLength:%d,H264Profile:%d,Port:%d,TTL:%d,AutoStart:%d,SessionTimeout:%lld\n",
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->H264->GovLength,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->H264->H264Profile,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->Port,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->TTL,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->Multicast->AutoStart,
                trt__GetProfilesResponse->Profiles[i].VideoEncoderConfiguration->SessionTimeout);

        trt__GetProfilesResponse->Profiles[i].AudioSourceConfiguration = NULL;
        trt__GetProfilesResponse->Profiles[i].AudioEncoderConfiguration = NULL;
        trt__GetProfilesResponse->Profiles[i].VideoAnalyticsConfiguration = NULL;
        trt__GetProfilesResponse->Profiles[i].PTZConfiguration = NULL;
        trt__GetProfilesResponse->Profiles[i].MetadataConfiguration = NULL;
        trt__GetProfilesResponse->Profiles[i].Extension = NULL;
        trt__GetProfilesResponse->Profiles[i].__anyAttribute = NULL;
    }
    printf("end __trt__GetProfiles\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoEncoderConfiguration(struct soap* soap, struct _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, struct _trt__AddVideoEncoderConfigurationResponse *trt__AddVideoEncoderConfigurationResponse)
{

	int i = 0;
	int j = 0;
	int k = 0;
	printf(" start __trt__AddVideoEncoderConfiguration\n");

	if(trt__AddVideoEncoderConfiguration->ProfileToken == NULL || trt__AddVideoEncoderConfiguration->ConfigurationToken == NULL)
	{
		goto InvalArgValNull;
	}
    printf(" ProfileToken:%s, ConfigurationToken:%s\n",trt__AddVideoEncoderConfiguration->ProfileToken, trt__AddVideoEncoderConfiguration->ConfigurationToken);

	/*check profile*/
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
		printf(" ProfileToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
	    if(strcmp(trt__AddVideoEncoderConfiguration->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
    		break;
	    }
	}

	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto InvalArgValNoProrileExist;
	}

	/*check videosource configuration*/
    for(j = 0; j < g_GkIpc_OnvifInf.VideoEncodeNum; j++)
	{
		printf(" 111VideoEncodeConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].token);
	    if(strcmp(trt__AddVideoEncoderConfiguration->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].token) == 0){
    		break;
	    }
	}
	if(j == g_GkIpc_OnvifInf.VideoEncodeNum){
		goto InvalArgValNoConfigExist;
	}


	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration != NULL){
	    for(k = 0; k < g_GkIpc_OnvifInf.VideoEncodeNum; k++)
		{
			printf(" 222VideoEncodeConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[k].token);
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token,g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[k].token) == 0){
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[k].UseCount--;
	    		break;
		    }
		}

		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration, 0, sizeof(struct tt__VideoEncoderConfiguration));
		memcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration, &g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j], sizeof(struct tt__VideoEncoderConfiguration));
		g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount++;
	}
	else
	{
		g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration = (struct tt__VideoEncoderConfiguration *)malloc(sizeof(struct tt__VideoEncoderConfiguration));
		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration, 0, sizeof(struct tt__VideoEncoderConfiguration));
		memcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration, &g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j], sizeof(struct tt__VideoEncoderConfiguration));
		g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount++;
		printf(" VideoEncodeUseCount:%d\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount);
	}

    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValNoProrileExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
InvalArgValNoConfigExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoSourceConfiguration(struct soap* soap, struct _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, struct _trt__AddVideoSourceConfigurationResponse *trt__AddVideoSourceConfigurationResponse)
{
	int i = 0;
	int j = 0;
	int k = 0;
    printf(" start __trt__AddVideoSourceConfiguration\n");

	printf(" ProfileToken:%s, ConfigurationToken:%s\n",trt__AddVideoSourceConfiguration->ProfileToken, trt__AddVideoSourceConfiguration->ConfigurationToken);

	if(trt__AddVideoSourceConfiguration->ProfileToken == NULL || trt__AddVideoSourceConfiguration->ConfigurationToken == NULL)
	{
		goto InvalArgValNull;
	}

	/*check profile*/
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
		printf(" ProfileToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
	    if(strcmp(trt__AddVideoSourceConfiguration->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
    		break;
	    }
	}
	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto InvalArgValNoProrileExist;
	}

	/*check videosource configuration*/
    for(j = 0; j < g_GkIpc_OnvifInf.VideoSourceNum; j++)
	{
		printf(" 111VideoSourceConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].token);
	    if(strcmp(trt__AddVideoSourceConfiguration->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].token) == 0){
    		break;
	    }
	}
	if(j == g_GkIpc_OnvifInf.VideoSourceNum){
		goto InvalArgValNoConfigExist;
	}


	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration != NULL){
	    for(k = 0; k < g_GkIpc_OnvifInf.VideoSourceNum; k++)
		{
			printf(" 222VideoSourceConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoSource[k].token);
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[k].token) == 0){
				g_GkIpc_OnvifInf.gokeIPCameraVideoSource[k].UseCount--;
	    		break;
		    }
		}

		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration, 0, sizeof(struct tt__VideoSourceConfiguration));
		memcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration, &g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j], sizeof(struct tt__VideoSourceConfiguration));
		g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount++;
	}
	else
	{
		g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration = (struct tt__VideoSourceConfiguration *)malloc(sizeof(struct tt__VideoSourceConfiguration));
		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration, 0, sizeof(struct tt__VideoSourceConfiguration));
		memcpy(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration, &g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j], sizeof(struct tt__VideoSourceConfiguration));
		g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount++;

	}
    printf(" end __trt__AddVideoSourceConfiguration\n");
    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValNoProrileExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
InvalArgValNoConfigExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioEncoderConfiguration(struct soap* soap, struct _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, struct _trt__AddAudioEncoderConfigurationResponse *trt__AddAudioEncoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioSourceConfiguration(struct soap* soap, struct _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, struct _trt__AddAudioSourceConfigurationResponse *trt__AddAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddPTZConfiguration(struct soap* soap, struct _trt__AddPTZConfiguration *trt__AddPTZConfiguration, struct _trt__AddPTZConfigurationResponse *trt__AddPTZConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoAnalyticsConfiguration(struct soap* soap, struct _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, struct _trt__AddVideoAnalyticsConfigurationResponse *trt__AddVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddMetadataConfiguration(struct soap* soap, struct _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, struct _trt__AddMetadataConfigurationResponse *trt__AddMetadataConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioOutputConfiguration(struct soap* soap, struct _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, struct _trt__AddAudioOutputConfigurationResponse *trt__AddAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioDecoderConfiguration(struct soap* soap, struct _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, struct _trt__AddAudioDecoderConfigurationResponse *trt__AddAudioDecoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoEncoderConfiguration(struct soap* soap, struct _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, struct _trt__RemoveVideoEncoderConfigurationResponse *trt__RemoveVideoEncoderConfigurationResponse)
{
	printf(" start __trt__RemoveVideoEncoderConfiguration\n");

	int i = 0;
	int j = 0;

	printf(" ProfileToken:%s\n",trt__RemoveVideoEncoderConfiguration->ProfileToken);

	if(trt__RemoveVideoEncoderConfiguration->ProfileToken == NULL)
	{
		goto InvalArgValNull;
	}

	/*check profile*/
	printf(" ProfileNum:%d\n",g_GkIpc_OnvifInf.ProfileNum);

    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
		printf(" ProfileToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
	    if(strcmp(trt__RemoveVideoEncoderConfiguration->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
    		break;
	    }
	}
	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto InvalArgValNoProrileExist;
	}



	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration != NULL){
		/*check videoencode configuration*/
		printf(" VideoEncodeNum:%d\n",g_GkIpc_OnvifInf.VideoEncodeNum);
	    for(j = 0; j < g_GkIpc_OnvifInf.VideoEncodeNum; j++)
		{
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].token,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token) == 0){
				printf(" VideoEncodeUseCount:%d\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount);
				free(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration);
				g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration = NULL;
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount--;
				printf(" VideoEncodeUseCount:%d\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount);
	    		break;
		    }
		}
	}
	else
	{
		goto InvalArgValNoConfigExist;

	}
    printf(" end __trt__RemoveVideoEncoderConfiguration\n");
    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValNoProrileExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
InvalArgValNoConfigExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoSourceConfiguration(struct soap* soap, struct _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, struct _trt__RemoveVideoSourceConfigurationResponse *trt__RemoveVideoSourceConfigurationResponse)
{
	printf(" start __trt__RemoveVideoSourceConfiguration\n");

	int i = 0;
	int j = 0;

	printf(" ProfileToken:%s\n",trt__RemoveVideoSourceConfiguration->ProfileToken);

	if(trt__RemoveVideoSourceConfiguration->ProfileToken == NULL)
	{
		goto InvalArgValNull;
	}

	/*check profile*/
	printf(" ProfileNum:%d\n",g_GkIpc_OnvifInf.ProfileNum);

    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
		printf(" ProfileToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token);
	    if(strcmp(trt__RemoveVideoSourceConfiguration->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
    		break;
	    }
	}
	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto InvalArgValNoProrileExist;
	}



	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration != NULL){
		/*check videoencode configuration*/
		printf(" VideoSourceNum:%d\n",g_GkIpc_OnvifInf.VideoSourceNum);
	    for(j = 0; j < g_GkIpc_OnvifInf.VideoSourceNum; j++)
		{
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].token,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token) == 0){
				printf(" VideoSourceUseCount:%d\n",g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount);
				free(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration);
				g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration = NULL;
				g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount--;
				printf(" VideoSourceUseCount:%d\n",g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount);
	    		break;
		    }
		}
	}
	else
	{
		goto InvalArgValNoConfigExist;

	}
    printf(" end __trt__RemoveVideoSourceConfiguration\n");
    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValNoProrileExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
InvalArgValNoConfigExist:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioEncoderConfiguration(struct soap* soap, struct _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, struct _trt__RemoveAudioEncoderConfigurationResponse *trt__RemoveAudioEncoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioSourceConfiguration(struct soap* soap, struct _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, struct _trt__RemoveAudioSourceConfigurationResponse *trt__RemoveAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemovePTZConfiguration(struct soap* soap, struct _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, struct _trt__RemovePTZConfigurationResponse *trt__RemovePTZConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoAnalyticsConfiguration(struct soap* soap, struct _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, struct _trt__RemoveVideoAnalyticsConfigurationResponse *trt__RemoveVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveMetadataConfiguration(struct soap* soap, struct _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, struct _trt__RemoveMetadataConfigurationResponse *trt__RemoveMetadataConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioOutputConfiguration(struct soap* soap, struct _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, struct _trt__RemoveAudioOutputConfigurationResponse *trt__RemoveAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioDecoderConfiguration(struct soap* soap, struct _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, struct _trt__RemoveAudioDecoderConfigurationResponse *trt__RemoveAudioDecoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteProfile(struct soap* soap, struct _trt__DeleteProfile *trt__DeleteProfile, struct _trt__DeleteProfileResponse *trt__DeleteProfileResponse)
{
	int i = 0;
	int j = 0;
    printf(" start __trt__DeleteProfile\n");
    if (NULL == trt__DeleteProfile->ProfileToken)
    {
        goto InvalArgValNull;//ArgVal Err
    }
    printf("Token:%s\n", trt__DeleteProfile->ProfileToken);
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++)
	{
	    if(strcmp(trt__DeleteProfile->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
			break;
	    }
	}

	if(i == g_GkIpc_OnvifInf.ProfileNum){
    	goto InvalArgValNoProfile;//No Profile

	}

    if(*g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed == xsd__boolean__true_){
    	goto DeletionOfFixedProfile;//can not delete the profile
	}

	/*check video source configuration*/
	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration != NULL){
	    for(j = 0; j < g_GkIpc_OnvifInf.VideoSourceNum; j++)
		{
			printf(" VideoSourceConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].token);
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].token) == 0){
				g_GkIpc_OnvifInf.gokeIPCameraVideoSource[j].UseCount--;
	    		break;
		    }
		}
		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration, 0, sizeof(struct tt__VideoSourceConfiguration));
	}

	/*check video source configuration*/
	if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration != NULL){
	    for(j = 0; j < g_GkIpc_OnvifInf.VideoEncodeNum; j++)
		{
			printf(" VideoEncodeConfigurationToken:%s\n",g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].token);
		    if(strcmp(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token,g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].token) == 0){
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[j].UseCount--;
	    		break;
		    }
		}
		memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration, 0, sizeof(struct tt__VideoEncoderConfiguration));
	}

	memset(&g_GkIpc_OnvifInf.gokeIPCameraProfiles[i], 0, sizeof(struct tt__Profile));
	g_GkIpc_OnvifInf.ProfileNum--;
    printf("end __trt__CreateProfile\n");
    return SOAP_OK;
InvalArgValNull:
	ONVIF_SENDER_ERROR(soap, NULL, "ter:InvalidArgVal", "ter:argv NULL", NULL);
InvalArgValNoProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "on compare profile", NULL);
DeletionOfFixedProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:Action", "ter:DeletionOfFixedProfile", "can not delete the profile", NULL);
    return SOAP_OK;
}


SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurations(struct soap* soap, struct _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, struct _trt__GetVideoSourceConfigurationsResponse *trt__GetVideoSourceConfigurationsResponse)
{
    printf("start __trt__GetVideoSourceConfigurations\n");

    int i = 0;
    trt__GetVideoSourceConfigurationsResponse->__sizeConfigurations = g_GkIpc_OnvifInf.VideoSourceNum;
    trt__GetVideoSourceConfigurationsResponse->Configurations = (struct tt__VideoSourceConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoSourceConfiguration) * g_GkIpc_OnvifInf.VideoSourceNum);
    memset(trt__GetVideoSourceConfigurationsResponse->Configurations, 0,  sizeof(struct tt__VideoSourceConfiguration) * g_GkIpc_OnvifInf.VideoSourceNum);
    for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
		soap_default_tt__VideoSourceConfiguration(soap, &trt__GetVideoSourceConfigurationsResponse->Configurations[i]);//set the default value

        /*VideoSourceConfiguration*/
        trt__GetVideoSourceConfigurationsResponse->Configurations[i].Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Name != NULL){
            strcpy(trt__GetVideoSourceConfigurationsResponse->Configurations[i].Name, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Name);
        }

        trt__GetVideoSourceConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token != NULL){
            strcpy(trt__GetVideoSourceConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token);
        }

        trt__GetVideoSourceConfigurationsResponse->Configurations[i].SourceToken = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken != NULL){
            strcpy(trt__GetVideoSourceConfigurationsResponse->Configurations[i].SourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken);
        }

        trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds = (struct tt__IntRectangle *)soap_malloc(soap, sizeof(struct tt__IntRectangle));
		soap_default_tt__IntRectangle(soap, trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds);//set the default value
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds != NULL){
            memcpy(trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds, sizeof(struct tt__IntRectangle));
        }
        trt__GetVideoSourceConfigurationsResponse->Configurations[i].UseCount = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].UseCount;

        trt__GetVideoSourceConfigurationsResponse->Configurations[i].Extension = NULL;
        trt__GetVideoSourceConfigurationsResponse->Configurations[i].__any = NULL;
        trt__GetVideoSourceConfigurationsResponse->Configurations[i].__anyAttribute = NULL;
        trt__GetVideoSourceConfigurationsResponse->Configurations[i].__size = 0;
        printf("GetVideoSourceConfigurations  Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].Name,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].token,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].SourceToken,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds->x,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds->y,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds->width,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].Bounds->height,
                trt__GetVideoSourceConfigurationsResponse->Configurations[i].UseCount);
    }

	printf("end __trt__GetVideoSourceConfigurations\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurations(struct soap* soap, struct _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, struct _trt__GetVideoEncoderConfigurationsResponse *trt__GetVideoEncoderConfigurationsResponse)
{
    printf("start __trt__GetVideoEncoderConfigurations\n");
    int i = 0;

    trt__GetVideoEncoderConfigurationsResponse->__sizeConfigurations = g_GkIpc_OnvifInf.VideoEncodeNum;
    trt__GetVideoEncoderConfigurationsResponse->Configurations = (struct tt__VideoEncoderConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration) * g_GkIpc_OnvifInf.VideoEncodeNum);

    for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
		soap_default_tt__VideoEncoderConfiguration(soap, &trt__GetVideoEncoderConfigurationsResponse->Configurations[i]);//set the default value

        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Name = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Name != NULL){
            strcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Name, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Name);
        }

        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token != NULL){
            strcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token);
        }


        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token != NULL){
            strcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token);
        }

        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].UseCount = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].UseCount;
        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Encoding = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Encoding;
        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
		soap_default_tt__VideoResolution(soap, trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Resolution);// set the default value
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution != NULL){
            memcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Resolution, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution, sizeof(struct tt__VideoResolution));
        }
        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Quality = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Quality;

        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl = (struct tt__VideoRateControl *)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
		soap_default_tt__VideoRateControl(soap,  trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl);// set the default value
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl != NULL){
            memcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl, sizeof(struct tt__VideoRateControl));
        }

        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].MPEG4 = NULL;


        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
		soap_default_tt__H264Configuration(soap, trt__GetVideoEncoderConfigurationsResponse->Configurations[i].H264);//set the default value
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264 != NULL){
            memcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].H264, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264, sizeof(struct tt__H264Configuration));
        }
        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast = (struct tt__MulticastConfiguration *)soap_malloc(soap, sizeof(struct tt__MulticastConfiguration));
		soap_default_tt__MulticastConfiguration(soap, trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast);//set the default value
        if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast != NULL){
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address!= NULL){
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address = (struct tt__IPAddress *)soap_malloc(soap, sizeof(struct tt__IPAddress));
				soap_default_tt__IPAddress(soap, trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address);//set the default value
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->Type = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->Type;
                if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv4Address != NULL){
                    trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv4Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                    strcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv4Address, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv4Address);

                }
                if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv6Address != NULL){
                    trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv6Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                    strcpy(trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv6Address, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv6Address);

                }
            }
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Port = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Port;
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->TTL = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->TTL;
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->AutoStart= g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->AutoStart;
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__size= g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->__size;
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__any = NULL;
            trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__anyAttribute = NULL;
        }
        trt__GetVideoEncoderConfigurationsResponse->Configurations[i].SessionTimeout = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].SessionTimeout;

        printf("GetVideoEncoderConfigurations Name:%s,Token:%s,UseCount:%d,Encoding:%d,Width:%d,Height:%d,Quality:%f,BitrateLimit:%d,EncodingInterval:%d,FrameRateLimit:%d\n",
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Name,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].token,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].UseCount,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Encoding,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Resolution->Width,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Resolution->Height,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Quality,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl->BitrateLimit,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl->EncodingInterval,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].RateControl->FrameRateLimit);


        printf("GovLength:%d,H264Profile:%d,Port:%d,TTL:%d,AutoStart:%d,SessionTimeout:%lld\n",
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].H264->GovLength,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].H264->H264Profile,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Port,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->TTL,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].Multicast->AutoStart,
                trt__GetVideoEncoderConfigurationsResponse->Configurations[i].SessionTimeout);
		}
    printf("end __trt__GetVideoEncoderConfigurations\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurations(struct soap* soap, struct _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, struct _trt__GetAudioSourceConfigurationsResponse *trt__GetAudioSourceConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurations(struct soap* soap, struct _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, struct _trt__GetAudioEncoderConfigurationsResponse *trt__GetAudioEncoderConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, struct _trt__GetVideoAnalyticsConfigurationsResponse *trt__GetVideoAnalyticsConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurations(struct soap* soap, struct _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, struct _trt__GetMetadataConfigurationsResponse *trt__GetMetadataConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurations(struct soap* soap, struct _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, struct _trt__GetAudioOutputConfigurationsResponse *trt__GetAudioOutputConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurations(struct soap* soap, struct _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, struct _trt__GetAudioDecoderConfigurationsResponse *trt__GetAudioDecoderConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfiguration(struct soap* soap, struct _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, struct _trt__GetVideoSourceConfigurationResponse *trt__GetVideoSourceConfigurationResponse)
{
    printf("start __trt__GetVideoSourceConfiguration\n");

    int i = 0;
    trt__GetVideoSourceConfigurationResponse->Configuration = (struct tt__VideoSourceConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoSourceConfiguration));
    memset(trt__GetVideoSourceConfigurationResponse->Configuration, 0,  sizeof(struct tt__VideoSourceConfiguration));
    for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
        if(strcmp(trt__GetVideoSourceConfiguration->ConfigurationToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token) == 0){
            trt__GetVideoSourceConfigurationResponse->Configuration->Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Name != NULL){
                strcpy(trt__GetVideoSourceConfigurationResponse->Configuration->Name, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Name);
            }

            trt__GetVideoSourceConfigurationResponse->Configuration->token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token != NULL){
                strcpy(trt__GetVideoSourceConfigurationResponse->Configuration->token, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token);
            }

            trt__GetVideoSourceConfigurationResponse->Configuration->SourceToken = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken != NULL){
                strcpy(trt__GetVideoSourceConfigurationResponse->Configuration->SourceToken, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken);
            }

            trt__GetVideoSourceConfigurationResponse->Configuration->Bounds = (struct tt__IntRectangle *)soap_malloc(soap, sizeof(struct tt__IntRectangle));
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds != NULL){
                memcpy(trt__GetVideoSourceConfigurationResponse->Configuration->Bounds, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds, sizeof(struct tt__IntRectangle));
            }
            trt__GetVideoSourceConfigurationResponse->Configuration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].UseCount;

            trt__GetVideoSourceConfigurationResponse->Configuration->Extension = NULL;
            trt__GetVideoSourceConfigurationResponse->Configuration->__any = NULL;
            trt__GetVideoSourceConfigurationResponse->Configuration->__anyAttribute = NULL;
            trt__GetVideoSourceConfigurationResponse->Configuration->__size = 0;
            printf("GetVideoSourceConfiguration  Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
                    trt__GetVideoSourceConfigurationResponse->Configuration->Name,
                    trt__GetVideoSourceConfigurationResponse->Configuration->token,
                    trt__GetVideoSourceConfigurationResponse->Configuration->SourceToken,
                    trt__GetVideoSourceConfigurationResponse->Configuration->Bounds->x,
                    trt__GetVideoSourceConfigurationResponse->Configuration->Bounds->y,
                    trt__GetVideoSourceConfigurationResponse->Configuration->Bounds->width,
                    trt__GetVideoSourceConfigurationResponse->Configuration->Bounds->height,
                    trt__GetVideoSourceConfigurationResponse->Configuration->UseCount);
            break;
        }
    }
	if(i == g_GkIpc_OnvifInf.VideoSourceNum){
		goto NoVideoSource;
	}
	printf("end __trt__GetVideoSourceConfiguration\n");
	return SOAP_OK;
NoVideoSource:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoVideoSource", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfiguration(struct soap* soap, struct _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, struct _trt__GetVideoEncoderConfigurationResponse *trt__GetVideoEncoderConfigurationResponse)
{
    printf("start __trt__GetVideoEncoderConfiguration\n");

    int i = 0;
    trt__GetVideoEncoderConfigurationResponse->Configuration = (struct tt__VideoEncoderConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration));
    memset(trt__GetVideoEncoderConfigurationResponse->Configuration, 0,  sizeof(struct tt__VideoEncoderConfiguration));
    for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
        if(strcmp(trt__GetVideoEncoderConfiguration->ConfigurationToken, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token) == 0){
            trt__GetVideoEncoderConfigurationResponse->Configuration->Name = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);

            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Name != NULL){
                strcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->Name, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Name);
            }

            trt__GetVideoEncoderConfigurationResponse->Configuration->token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token != NULL){
                strcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->token, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token);
            }


            trt__GetVideoEncoderConfigurationResponse->Configuration->token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token != NULL){
                strcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->token, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token);
            }

            trt__GetVideoEncoderConfigurationResponse->Configuration->UseCount = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].UseCount;
            trt__GetVideoEncoderConfigurationResponse->Configuration->Encoding = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Encoding;
            trt__GetVideoEncoderConfigurationResponse->Configuration->Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution != NULL){
                memcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->Resolution, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution, sizeof(struct tt__VideoResolution));
            }
            trt__GetVideoEncoderConfigurationResponse->Configuration->Quality = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Quality;

            trt__GetVideoEncoderConfigurationResponse->Configuration->RateControl = (struct tt__VideoRateControl *)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl != NULL){
                memcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->RateControl, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl, sizeof(struct tt__VideoRateControl));
            }

            trt__GetVideoEncoderConfigurationResponse->Configuration->MPEG4 = NULL;


            trt__GetVideoEncoderConfigurationResponse->Configuration->H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264 != NULL){
                memcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->H264, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264, sizeof(struct tt__H264Configuration));
            }
            trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast = (struct tt__MulticastConfiguration *)soap_malloc(soap, sizeof(struct tt__MulticastConfiguration));
            if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast != NULL){
                if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address!= NULL){
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address = (struct tt__IPAddress *)soap_malloc(soap, sizeof(struct tt__IPAddress));
                    memset(trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address, 0, sizeof(struct tt__IPAddress));
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address->Type = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->Type;
                    if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv4Address != NULL){
                        trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address->IPv4Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address->IPv4Address, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv4Address);

                    }
                    if(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv6Address != NULL){
                        trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address->IPv6Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Address->IPv6Address, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Address->IPv6Address);

                    }
                }
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Port = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->Port;
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->TTL = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->TTL;
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->AutoStart= g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->AutoStart;
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->__size= g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Multicast->__size;
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->__any = NULL;
                trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->__anyAttribute = NULL;
            }
            trt__GetVideoEncoderConfigurationResponse->Configuration->SessionTimeout = g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].SessionTimeout;

            printf("GetVideoEncoderConfiguration Name:%s,Token:%s,UseCount:%d,Encoding:%d,Width:%d,Height:%d,Quality:%f,BitrateLimit:%d,EncodingInterval:%d,FrameRateLimit:%d\n",
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Name,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->token,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->UseCount,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Encoding,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Resolution->Width,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Resolution->Height,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Quality,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->RateControl->BitrateLimit,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->RateControl->EncodingInterval,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->RateControl->FrameRateLimit);


            printf("GovLength:%d,H264Profile:%d,Port:%d,TTL:%d,AutoStart:%d,SessionTimeout:%lld\n",
                    trt__GetVideoEncoderConfigurationResponse->Configuration->H264->GovLength,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->H264->H264Profile,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->Port,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->TTL,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->Multicast->AutoStart,
                    trt__GetVideoEncoderConfigurationResponse->Configuration->SessionTimeout);
            break;

        }
    }


	if(i == g_GkIpc_OnvifInf.ProfileNum){
		goto NoConfig;
	}
	printf("end __trt__GetVideoEncoderConfiguration\n");
	return SOAP_OK;
NoConfig:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfiguration(struct soap* soap, struct _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, struct _trt__GetAudioSourceConfigurationResponse *trt__GetAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfiguration(struct soap* soap, struct _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, struct _trt__GetAudioEncoderConfigurationResponse *trt__GetAudioEncoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, struct _trt__GetVideoAnalyticsConfigurationResponse *trt__GetVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfiguration(struct soap* soap, struct _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, struct _trt__GetMetadataConfigurationResponse *trt__GetMetadataConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfiguration(struct soap* soap, struct _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, struct _trt__GetAudioOutputConfigurationResponse *trt__GetAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfiguration(struct soap* soap, struct _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, struct _trt__GetAudioDecoderConfigurationResponse *trt__GetAudioDecoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, struct _trt__GetCompatibleVideoEncoderConfigurationsResponse *trt__GetCompatibleVideoEncoderConfigurationsResponse)
{
    printf("start __trt__GetCompatibleVideoEncoderConfigurations\n");
    int i = 0;
    trt__GetCompatibleVideoEncoderConfigurationsResponse->__sizeConfigurations = 1;//the size should be 1
    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations = (struct tt__VideoEncoderConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfiguration) * 1);
    memset(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations, 0, sizeof(struct tt__VideoEncoderConfiguration) * 1);
    for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
		if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration == NULL){
			continue;
		}
        if(strcmp(trt__GetCompatibleVideoEncoderConfigurations->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Name = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);

            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name != NULL){
                strcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Name);
            }

            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token != NULL){
                strcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token);
            }


            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token != NULL){
                strcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->token);
            }

            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->UseCount;
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Encoding = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Encoding;
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Resolution = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution != NULL){
                memcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Resolution, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Resolution, sizeof(struct tt__VideoResolution));
            }
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Quality = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Quality;

            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].RateControl = (struct tt__VideoRateControl *)soap_malloc(soap, sizeof(struct tt__VideoRateControl));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl != NULL){
                memcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].RateControl, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->RateControl, sizeof(struct tt__VideoRateControl));
            }

            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].MPEG4 = NULL;


            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].H264 = (struct tt__H264Configuration *)soap_malloc(soap, sizeof(struct tt__H264Configuration));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264 != NULL){
                memcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].H264, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->H264, sizeof(struct tt__H264Configuration));
            }
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast = (struct tt__MulticastConfiguration *)soap_malloc(soap, sizeof(struct tt__MulticastConfiguration));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast != NULL){
                if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address!= NULL){
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address = (struct tt__IPAddress *)soap_malloc(soap, sizeof(struct tt__IPAddress));
                    memset(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address, 0, sizeof(struct tt__IPAddress));
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->Type = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->Type;
                    if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address != NULL){
                        trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv4Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv4Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv4Address);

                    }
                    if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address != NULL){
                        trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv6Address = (char *)soap_malloc(soap, sizeof(char)*MAX_PROF_TOKEN);
                        strcpy(trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Address->IPv6Address, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Address->IPv6Address);

                    }
                }
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Port = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->Port;
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->TTL = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->TTL;
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->AutoStart= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->AutoStart;
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__size= g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->Multicast->__size;
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__any = NULL;
                trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->__anyAttribute = NULL;
            }
            trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].SessionTimeout = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoEncoderConfiguration->SessionTimeout;

            printf("GetCompatibleVideoEncoderConfigurations Name:%s,Token:%s,UseCount:%d,Encoding:%d,Width:%d,Height:%d,Quality:%f,BitrateLimit:%d,EncodingInterval:%d,FrameRateLimit:%d\n",
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Name,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].token,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].UseCount,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Encoding,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Resolution->Width,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Resolution->Height,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Quality,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].RateControl->BitrateLimit,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].RateControl->EncodingInterval,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].RateControl->FrameRateLimit);


            printf("GovLength:%d,H264Profile:%d,Port:%d,TTL:%d,AutoStart:%d,SessionTimeout:%lld\n",
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].H264->GovLength,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].H264->H264Profile,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->Port,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->TTL,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].Multicast->AutoStart,
                    trt__GetCompatibleVideoEncoderConfigurationsResponse->Configurations[i].SessionTimeout);
            break;
        }
    }

	if(i == g_GkIpc_OnvifInf.ProfileNum){
	goto NoProfle;
	}
	printf("end __trt__GetCompatibleVideoEncoderConfigurations\n");
	return SOAP_OK;
NoProfle:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, struct _trt__GetCompatibleVideoSourceConfigurationsResponse *trt__GetCompatibleVideoSourceConfigurationsResponse)
{
    printf("start __trt__GetCompatibleVideoSourceConfigurations\n");
    printf("ProfileToken:%s\n",trt__GetCompatibleVideoSourceConfigurations->ProfileToken);
    int i = 0;
    trt__GetCompatibleVideoSourceConfigurationsResponse->__sizeConfigurations = 1;//the size should be 1
    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations = (struct tt__VideoSourceConfiguration *)soap_malloc(soap, sizeof(struct tt__VideoSourceConfiguration) * 1);
    memset(trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations, 0, sizeof(struct tt__VideoSourceConfiguration) * 1);
    for(i = 0; i <g_GkIpc_OnvifInf.ProfileNum; i++){
		if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration == NULL){
			continue;
		}
        if(strcmp(trt__GetCompatibleVideoSourceConfigurations->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Name = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name != NULL){
                strcpy(trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Name, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Name);
            }

            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].token = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token != NULL){
                strcpy(trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].token, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->token);
            }

            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].SourceToken = (char *)soap_malloc(soap, sizeof(char) * MAX_PROF_TOKEN);
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken != NULL){
                strcpy(trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].SourceToken, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->SourceToken);
            }

            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds = (struct tt__IntRectangle *)soap_malloc(soap, sizeof(struct tt__IntRectangle));
            if(g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds != NULL){
                memcpy(trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds, g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->Bounds, sizeof(struct tt__IntRectangle));
            }
            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].UseCount = g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].VideoSourceConfiguration->UseCount;

            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Extension = NULL;
            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].__any = NULL;
            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].__anyAttribute = NULL;
            trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].__size = 0;
            printf("GetCompatibleVideoSourceConfigurations  Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Name,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].token,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].SourceToken,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds->x,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds->y,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds->width,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].Bounds->height,
                    trt__GetCompatibleVideoSourceConfigurationsResponse->Configurations[i].UseCount);

            break;
        }
    }
	if(i == g_GkIpc_OnvifInf.ProfileNum){
	goto NoProfle;
	}
	printf("end __trt__GetCompatibleVideoSourceConfigurations\n");
	return SOAP_OK;
NoProfle:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioEncoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, struct _trt__GetCompatibleAudioEncoderConfigurationsResponse *trt__GetCompatibleAudioEncoderConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioSourceConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, struct _trt__GetCompatibleAudioSourceConfigurationsResponse *trt__GetCompatibleAudioSourceConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap* soap, struct _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, struct _trt__GetCompatibleVideoAnalyticsConfigurationsResponse *trt__GetCompatibleVideoAnalyticsConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleMetadataConfigurations(struct soap* soap, struct _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, struct _trt__GetCompatibleMetadataConfigurationsResponse *trt__GetCompatibleMetadataConfigurationsResponse)
{
    printf("__trt__GetCompatibleMetadataConfigurations\n");
    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioOutputConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, struct _trt__GetCompatibleAudioOutputConfigurationsResponse *trt__GetCompatibleAudioOutputConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioDecoderConfigurations(struct soap* soap, struct _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, struct _trt__GetCompatibleAudioDecoderConfigurationsResponse *trt__GetCompatibleAudioDecoderConfigurationsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceConfiguration(struct soap* soap, struct _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, struct _trt__SetVideoSourceConfigurationResponse *trt__SetVideoSourceConfigurationResponse)
{
    printf("start __trt__SetVideoSourceConfiguration\n");


    printf("SetVideoSourceConfiguration	Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d,Force:%d\n",
            trt__SetVideoSourceConfiguration->Configuration->Name,
            trt__SetVideoSourceConfiguration->Configuration->token,
            trt__SetVideoSourceConfiguration->Configuration->SourceToken,
            trt__SetVideoSourceConfiguration->Configuration->Bounds->x,
            trt__SetVideoSourceConfiguration->Configuration->Bounds->y,
            trt__SetVideoSourceConfiguration->Configuration->Bounds->width,
            trt__SetVideoSourceConfiguration->Configuration->Bounds->height,
            trt__SetVideoSourceConfiguration->Configuration->UseCount,
            trt__SetVideoSourceConfiguration->ForcePersistence);

	int i = 0;
	for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
		if(strcmp(trt__SetVideoSourceConfiguration->Configuration->token, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token) == 0){

			if(trt__SetVideoSourceConfiguration->Configuration->Bounds->height > g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->height ||
			   trt__SetVideoSourceConfiguration->Configuration->Bounds->width > g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->width){
				goto ConfigModify;
			}
			break;
		}
	}

	if(i == g_GkIpc_OnvifInf.VideoSourceNum){
		goto NoVideoSource;
	}
	printf("end __trt__SetVideoSourceConfiguration\n");
	return SOAP_OK;
ConfigModify:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:ConfigModify", "can not modify videosource", NULL);	
NoVideoSource:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoVideoSource", "no videosource exists", NULL);
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoEncoderConfiguration(struct soap* soap, struct _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, struct _trt__SetVideoEncoderConfigurationResponse *trt__SetVideoEncoderConfigurationResponse)
{
	int retVal = 0;
	printf("start __trt__SetVideoEncoderConfiguration\n");
	
	if(trt__SetVideoEncoderConfiguration == NULL){
		return SOAP_ERR;
	}

	printf("Name:%s,Token:%s,UseCount:%d,Quality:%f,size:%d\n",trt__SetVideoEncoderConfiguration->Configuration->Name,
						trt__SetVideoEncoderConfiguration->Configuration->token,
						trt__SetVideoEncoderConfiguration->Configuration->UseCount,
						trt__SetVideoEncoderConfiguration->Configuration->Quality,
						trt__SetVideoEncoderConfiguration->Configuration->__size);


	printf("GovLength:%d,H264Profile:%d,Width:%d,Height:%d,BitrateLimit:%d,FrameRateLimit:%d,EncodingInterval:%d,Encode:%d,Force:%d\n",
								trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength,
								trt__SetVideoEncoderConfiguration->Configuration->H264->H264Profile,
								trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width,
								trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height,
								trt__SetVideoEncoderConfiguration->Configuration->RateControl->BitrateLimit,
								trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit,
								trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval,
								trt__SetVideoEncoderConfiguration->Configuration->Encoding,
								trt__SetVideoEncoderConfiguration->ForcePersistence);

	int i = 0;
	int j = 0;
	for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
		if(strcmp(trt__SetVideoEncoderConfiguration->Configuration->token, g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token) == 0){

			printf("11111111111111\n");
			/*set encoder and resolution*/
			if(trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Width ||
			   trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height!= g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Height)
			{
				/*check value*/
				for(j = 0; j < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeResolutionsAvailable; j++){
					if(trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width == g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->ResolutionsAvailable[j].Width ||
						trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height == g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->ResolutionsAvailable[j].Height)
					{
						break;
					}
				}
				if(j == g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeResolutionsAvailable){
					goto ConfigModify;
				}
				retVal = MediaSetResolution(i,trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width,trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height);
				if(retVal != 0){
					goto ConfigModify;
				}
				printf("222222222222222\n");
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Width = trt__SetVideoEncoderConfiguration->Configuration->Resolution->Width;
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Height = trt__SetVideoEncoderConfiguration->Configuration->Resolution->Height;

			}

			/*set Frame rate*/
			if(trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->FrameRateLimit)
			{
				/*check value*/
				if(trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->FrameRateRange->Min ||
					trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit > g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->FrameRateRange->Max)
				{
					goto ConfigModify;
				}
				retVal = MediaSetFrameRate(i,trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit);
				if(retVal != 0){
					goto ConfigModify;
				}
				printf("333333333333333\n");
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->FrameRateLimit = trt__SetVideoEncoderConfiguration->Configuration->RateControl->FrameRateLimit;

			}

			/*set Bit rate*/
			if(trt__SetVideoEncoderConfiguration->Configuration->RateControl->BitrateLimit != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->BitrateLimit)
			{

				retVal = MediaSetBitRate(i,trt__SetVideoEncoderConfiguration->Configuration->RateControl->BitrateLimit);
				if(retVal != 0){
					goto ConfigModify;
				}
				printf("444444444444444\n");
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->BitrateLimit = trt__SetVideoEncoderConfiguration->Configuration->RateControl->BitrateLimit;

			}


			/*set Encoding Interval*/
			if(trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->EncodingInterval)
			{
				/*check value*/
				if(trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->EncodingIntervalRange->Min ||
					trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval > g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->EncodingIntervalRange->Max)
				{
					goto ConfigModify;
				}

				retVal = MediaSetEncodingInterval(i,trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval);
				if(retVal != 0){
					goto ConfigModify;
				}
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->EncodingInterval = trt__SetVideoEncoderConfiguration->Configuration->RateControl->EncodingInterval;
			}


			/*set Quality*/
			if(trt__SetVideoEncoderConfiguration->Configuration->Quality != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Quality)
			{
				/*check value*/
				if(trt__SetVideoEncoderConfiguration->Configuration->Quality < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].QualityRange->Min ||
					trt__SetVideoEncoderConfiguration->Configuration->Quality > g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].QualityRange->Max)
				{
					goto ConfigModify;
				}
				retVal = MediaSetQuality(i,trt__SetVideoEncoderConfiguration->Configuration->Quality);
				if(retVal != 0){
					goto ConfigModify;
				}
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Quality = trt__SetVideoEncoderConfiguration->Configuration->Quality;
			}

			/*setGovLength*/
			if(trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength != g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264->GovLength)
			{
				/*check value*/
				if(trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->GovLengthRange->Min ||
					trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength > g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->GovLengthRange->Max)
				{
					goto ConfigModify;
				}


				retVal = MediaSetGovLength(i,trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength);
				if(retVal != 0){
					goto ConfigModify;
				}
				g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264->GovLength = trt__SetVideoEncoderConfiguration->Configuration->H264->GovLength;
			}
			break;
		}

	}
	if(i == g_GkIpc_OnvifInf.VideoEncodeNum){
		goto NoConfig;
	}
	printf("end __trt__SetVideoEncoderConfiguration\n");
	return SOAP_OK;
ConfigModify:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:ConfigModify", " can not modify videoencoder", NULL);	
NoConfig:
		ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioSourceConfiguration(struct soap* soap, struct _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, struct _trt__SetAudioSourceConfigurationResponse *trt__SetAudioSourceConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioEncoderConfiguration(struct soap* soap, struct _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, struct _trt__SetAudioEncoderConfigurationResponse *trt__SetAudioEncoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoAnalyticsConfiguration(struct soap* soap, struct _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, struct _trt__SetVideoAnalyticsConfigurationResponse *trt__SetVideoAnalyticsConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetMetadataConfiguration(struct soap* soap, struct _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, struct _trt__SetMetadataConfigurationResponse *trt__SetMetadataConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioOutputConfiguration(struct soap* soap, struct _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, struct _trt__SetAudioOutputConfigurationResponse *trt__SetAudioOutputConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioDecoderConfiguration(struct soap* soap, struct _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, struct _trt__SetAudioDecoderConfigurationResponse *trt__SetAudioDecoderConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurationOptions(struct soap* soap, struct _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, struct _trt__GetVideoSourceConfigurationOptionsResponse *trt__GetVideoSourceConfigurationOptionsResponse)
{
    printf("start __trt__GetVideoSourceConfigurationOptions\n");

    int i = 0;

    trt__GetVideoSourceConfigurationOptionsResponse->Options = (struct tt__VideoSourceConfigurationOptions *)soap_malloc(soap, sizeof(struct tt__VideoSourceConfigurationOptions));
	soap_default_tt__VideoSourceConfigurationOptions(soap, trt__GetVideoSourceConfigurationOptionsResponse->Options);// set default value

    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange = (struct tt__IntRectangleRange *)soap_malloc(soap, sizeof(struct tt__IntRectangleRange));
	soap_default_tt__IntRectangleRange(soap, trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange);// set default value

	/*bound range information*/
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->XRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->XRange->Min = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->XRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->XRange->Max = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->XRange->Max;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->YRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->YRange->Min = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->YRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->YRange->Max = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->YRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->WidthRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->WidthRange->Min = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->WidthRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->WidthRange->Max = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->WidthRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->HeightRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->HeightRange->Min = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->HeightRange->Min;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->BoundsRange->HeightRange->Max = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].BoundsRange->HeightRange->Min;

	/*video source token information*/
    trt__GetVideoSourceConfigurationOptionsResponse->Options->__sizeVideoSourceTokensAvailable = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].__sizeVideoSourceTokensAvailable;//the size should be 1
    trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable = (char **)soap_malloc(soap, sizeof(char *));
    *trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable = (char *)soap_malloc(soap,  sizeof(char) * MAX_PROF_TOKEN);
    memset(*trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable, 0, sizeof(char) * MAX_PROF_TOKEN);
	strcpy(*trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable,*g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].VideoSourceTokensAvailable);

	/*Extension __anyAttribute information*/
	trt__GetVideoSourceConfigurationOptionsResponse->Options->Extension = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].Extension;
	trt__GetVideoSourceConfigurationOptionsResponse->Options->__anyAttribute = g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[0].__anyAttribute;

    printf("ProfileToken:%s,ConfigurationToken:%s\n",trt__GetVideoSourceConfigurationOptions->ProfileToken,trt__GetVideoSourceConfigurationOptions->ConfigurationToken);

    if(trt__GetVideoSourceConfigurationOptions->ProfileToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
            if(strcmp(trt__GetVideoSourceConfigurationOptions->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
				break;
            }
        }
		if(i == g_GkIpc_OnvifInf.ProfileNum){
			goto NoProfile;
		}

		if(trt__GetVideoSourceConfigurationOptions->ConfigurationToken != NULL){
			for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
				if(strcmp(trt__GetVideoSourceConfigurationOptions->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token) == 0){
					strcpy(*trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken);
					break;
				}
			}
		}
		if(i == g_GkIpc_OnvifInf.VideoSourceNum){
			goto NoConfig;
		}
	}

    if(trt__GetVideoSourceConfigurationOptions->ProfileToken == NULL && trt__GetVideoSourceConfigurationOptions->ConfigurationToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
            if(strcmp(trt__GetVideoSourceConfigurationOptions->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token) == 0){
                strcpy(*trt__GetVideoSourceConfigurationOptionsResponse->Options->VideoSourceTokensAvailable, g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken);
				break;
            }
        }
    }
	if(i == g_GkIpc_OnvifInf.VideoSourceNum){
		goto NoConfig;
	}

    trt__GetVideoSourceConfigurationOptionsResponse->Options->Extension = NULL;
    trt__GetVideoSourceConfigurationOptionsResponse->Options->__anyAttribute = NULL;

    printf("end __trt__GetVideoSourceConfigurationOptions\n");
    return SOAP_OK;
NoProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
NoConfig:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurationOptions(struct soap* soap, struct _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, struct _trt__GetVideoEncoderConfigurationOptionsResponse *trt__GetVideoEncoderConfigurationOptionsResponse)
{

	int i = 0;
    printf("start __trt__GetVideoEncoderConfigurationOptions\n");

    if(trt__GetVideoEncoderConfigurationOptions != NULL){
        printf("ConfigurationToken:%s,ProfileToken:%s\n",trt__GetVideoEncoderConfigurationOptions->ConfigurationToken,trt__GetVideoEncoderConfigurationOptions->ProfileToken);
    }

    if(trt__GetVideoEncoderConfigurationOptions->ProfileToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
            if(strcmp(trt__GetVideoEncoderConfigurationOptions->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
				break;
            }
        }
		if(i == g_GkIpc_OnvifInf.ProfileNum){
			goto NoProfile;
		}

		if(trt__GetVideoEncoderConfigurationOptions->ConfigurationToken != NULL){
			for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
				if(strcmp(trt__GetVideoEncoderConfigurationOptions->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token) == 0){
					break;
				}
			}
		}
		if(i == g_GkIpc_OnvifInf.VideoEncodeNum){
			goto NoConfig;
		}
	}

    if(trt__GetVideoEncoderConfigurationOptions->ProfileToken == NULL && trt__GetVideoEncoderConfigurationOptions->ConfigurationToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
            if(strcmp(trt__GetVideoEncoderConfigurationOptions->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].token) == 0){
				break;
            }
        }
    }
	if(i == g_GkIpc_OnvifInf.VideoEncodeNum){
		goto NoConfig;
	}


    trt__GetVideoEncoderConfigurationOptionsResponse->Options = (struct tt__VideoEncoderConfigurationOptions *)soap_malloc(soap, sizeof(struct tt__VideoEncoderConfigurationOptions));
	soap_default_tt__VideoEncoderConfigurationOptions(soap, trt__GetVideoEncoderConfigurationOptionsResponse->Options);// set default value

    /*video quality range*/
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->QualityRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->QualityRange->Min = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].QualityRange->Min;
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->QualityRange->Max = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].QualityRange->Max;

	/*h264 information*/
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264 =  (struct tt__H264Options *)soap_malloc(soap, sizeof(struct tt__H264Options));
	soap_default_tt__H264Options(soap, trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264);// set default value

	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->__sizeResolutionsAvailable = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeResolutionsAvailable;
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->ResolutionsAvailable = (struct tt__VideoResolution *)soap_malloc(soap, sizeof(struct tt__VideoResolution)*g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeResolutionsAvailable);
	for(i = 0; i < g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeResolutionsAvailable; i++){
		trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->ResolutionsAvailable[i].Width  = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->ResolutionsAvailable[i].Width;
		trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->ResolutionsAvailable[i].Height = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->ResolutionsAvailable[i].Height;
	}


	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->GovLengthRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->GovLengthRange->Min = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->GovLengthRange->Min;
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->GovLengthRange->Max = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->GovLengthRange->Max;

	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->FrameRateRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->FrameRateRange->Min = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->FrameRateRange->Min;
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->FrameRateRange->Max = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->FrameRateRange->Max;

	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->EncodingIntervalRange = (struct tt__IntRange *)soap_malloc(soap, sizeof(struct tt__IntRange));
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->EncodingIntervalRange->Min = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->EncodingIntervalRange->Min;
	trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->EncodingIntervalRange->Max = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->EncodingIntervalRange->Max;

    trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->__sizeH264ProfilesSupported = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->__sizeH264ProfilesSupported;

    trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->H264ProfilesSupported = (enum tt__H264Profile *)soap_malloc(soap, sizeof(enum tt__H264Profile));
    *trt__GetVideoEncoderConfigurationOptionsResponse->Options->H264->H264ProfilesSupported = *g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].H264->H264ProfilesSupported;

	/*MPEG4 JPEG Extension __anyAttribute information*/
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->MPEG4 = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].MPEG4;//not support MPEG4 Encoder
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->JPEG = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].JPEG;//not support JPEG Encoder
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->Extension = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].Extension;
    trt__GetVideoEncoderConfigurationOptionsResponse->Options->__anyAttribute = g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[0].__anyAttribute;

    printf("end __trt__GetVideoEncoderConfigurationOptions\n");
    return SOAP_OK;
NoProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL);
NoConfig:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurationOptions(struct soap* soap, struct _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, struct _trt__GetAudioSourceConfigurationOptionsResponse *trt__GetAudioSourceConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, struct _trt__GetAudioEncoderConfigurationOptionsResponse *trt__GetAudioEncoderConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurationOptions(struct soap* soap, struct _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, struct _trt__GetMetadataConfigurationOptionsResponse *trt__GetMetadataConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurationOptions(struct soap* soap, struct _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, struct _trt__GetAudioOutputConfigurationOptionsResponse *trt__GetAudioOutputConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurationOptions(struct soap* soap, struct _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, struct _trt__GetAudioDecoderConfigurationOptionsResponse *trt__GetAudioDecoderConfigurationOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap* soap, struct _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, struct _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse *trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse)
{
	printf("start __trt__GetGuaranteedNumberOfVideoEncoderInstances");
	int i = 0;
	if(trt__GetGuaranteedNumberOfVideoEncoderInstances->ConfigurationToken != NULL){
		for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
			if(strcmp(trt__GetGuaranteedNumberOfVideoEncoderInstances->ConfigurationToken,g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token) == 0){
				break;
			}
		}
	}
	if(i == g_GkIpc_OnvifInf.VideoSourceNum){
		goto NoConfig;
	}
	trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->TotalNumber = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].UseCount;
	trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->JPEG = soap_malloc(soap, sizeof(int));
	*trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->JPEG = 0;
	trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->MPEG4 = soap_malloc(soap, sizeof(int));
	*trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->MPEG4 = 0;
	trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->H264 = soap_malloc(soap, sizeof(int));
	*trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse->H264 = g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].UseCount;
	printf("end __trt__GetGuaranteedNumberOfVideoEncoderInstances");
	return SOAP_OK;
NoConfig:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoConfig", "no config exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetStreamUri(struct soap* soap, struct _trt__GetStreamUri *trt__GetStreamUri, struct _trt__GetStreamUriResponse *trt__GetStreamUriResponse)
{
	int i;
	char _IPAddr[INFO_LENGTH];
    unsigned int localIp = 0;

    printf("Sean: ===> %s():\n", __func__);


    if(trt__GetStreamUri->ProfileToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
            if(strcmp(trt__GetStreamUri->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
				break;
            }
        }
		if(i == g_GkIpc_OnvifInf.ProfileNum){
			goto NoProfile;
		}
    }

	if(trt__GetStreamUri->StreamSetup->Transport->Protocol != tt__TransportProtocol__RTSP){
		goto InvalidStreamSetup;
	}
	
    netGetIp(ETHERNET_ADAPT, &localIp);

    memset(_IPAddr, 0, sizeof(_IPAddr));
    if(strcmp(trt__GetStreamUri->ProfileToken,"MainStreamProfileToken") == 0){
        sprintf(_IPAddr, "rtsp://%s/stream1", inet_ntoa(*((struct in_addr *)&localIp)));//mainstream channel1 url
    }

    if(strcmp(trt__GetStreamUri->ProfileToken,"SecondStreamProfileToken") == 0){
        sprintf(_IPAddr, "rtsp://%s/stream2", inet_ntoa(*((struct in_addr *)&localIp)));//secondstream channel2 url
    }

    printf("[%d] _IPAddr ==== %s\n", __LINE__, _IPAddr);
    /* Response */
    trt__GetStreamUriResponse->MediaUri = (struct tt__MediaUri *)soap_malloc(soap, sizeof(struct tt__MediaUri));
    trt__GetStreamUriResponse->MediaUri->Uri = (char *)soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
    strcpy(trt__GetStreamUriResponse->MediaUri->Uri,_IPAddr);
    trt__GetStreamUriResponse->MediaUri->InvalidAfterConnect = xsd__boolean__false_;
    trt__GetStreamUriResponse->MediaUri->InvalidAfterReboot = xsd__boolean__false_;
    trt__GetStreamUriResponse->MediaUri->Timeout = 5;
    trt__GetStreamUriResponse->MediaUri->__size = 0;
    trt__GetStreamUriResponse->MediaUri->__any = NULL;
    trt__GetStreamUriResponse->MediaUri->__anyAttribute = NULL;

    printf("Sean: <=== %s():\n", __func__);

    return SOAP_OK; 
NoProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL); 
InvalidStreamSetup:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidStreamSetup", "Invalid Stream Setup", NULL); 
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StartMulticastStreaming(struct soap* soap, struct _trt__StartMulticastStreaming *trt__StartMulticastStreaming, struct _trt__StartMulticastStreamingResponse *trt__StartMulticastStreamingResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__StopMulticastStreaming(struct soap* soap, struct _trt__StopMulticastStreaming *trt__StopMulticastStreaming, struct _trt__StopMulticastStreamingResponse *trt__StopMulticastStreamingResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetSynchronizationPoint(struct soap* soap, struct _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, struct _trt__SetSynchronizationPointResponse *trt__SetSynchronizationPointResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetSnapshotUri(struct soap* soap, struct _trt__GetSnapshotUri *trt__GetSnapshotUri, struct _trt__GetSnapshotUriResponse *trt__GetSnapshotUriResponse)
{

    /*this interface request WebServer support*/
    /*client will get the jpg image from the ImageIPAddr WebServer*/
    printf("start __trt__GetSnapshotUri\n");
	int i;
    char ImageIPAddr[INFO_LENGTH];
    unsigned int localIp = 0;

    if(trt__GetSnapshotUri->ProfileToken != NULL){
        for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
            if(strcmp(trt__GetSnapshotUri->ProfileToken,g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token) == 0){
				break;
            }
        }
		if(i == g_GkIpc_OnvifInf.ProfileNum){
			goto NoProfile;
		}
    }

    trt__GetSnapshotUriResponse->MediaUri = NULL;
    trt__GetSnapshotUriResponse->MediaUri = (struct tt__MediaUri *)soap_malloc(soap, sizeof(struct tt__MediaUri));
    memset(trt__GetSnapshotUriResponse->MediaUri, 0, sizeof(struct tt__MediaUri));


    netGetIp(ETHERNET_ADAPT, &localIp);
    memset(ImageIPAddr, 0, INFO_LENGTH);
    sprintf(ImageIPAddr, "http://192.168.100.40/images/test.jpg");//this contain the webserver address
    printf("ImageIPAddr:%s\n",ImageIPAddr);
    trt__GetSnapshotUriResponse->MediaUri->Uri = (char *)soap_malloc(soap, LARGE_INFO_LENGTH);
    memset(trt__GetSnapshotUriResponse->MediaUri->Uri, 0, LARGE_INFO_LENGTH);
    strcpy(trt__GetSnapshotUriResponse->MediaUri->Uri,ImageIPAddr);

    trt__GetSnapshotUriResponse->MediaUri->InvalidAfterConnect = xsd__boolean__false_;
    trt__GetSnapshotUriResponse->MediaUri->InvalidAfterReboot = xsd__boolean__false_;
    trt__GetSnapshotUriResponse->MediaUri->Timeout = 5;
    trt__GetSnapshotUriResponse->MediaUri->__size = 0;
    trt__GetSnapshotUriResponse->MediaUri->__any = NULL;
    trt__GetSnapshotUriResponse->MediaUri->__anyAttribute = NULL;

    return SOAP_OK; 

NoProfile:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:NoProfile", "no profile exists", NULL); 
}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceModes(struct soap* soap, struct _trt__GetVideoSourceModes *trt__GetVideoSourceModes, struct _trt__GetVideoSourceModesResponse *trt__GetVideoSourceModesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceMode(struct soap* soap, struct _trt__SetVideoSourceMode *trt__SetVideoSourceMode, struct _trt__SetVideoSourceModeResponse *trt__SetVideoSourceModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDs(struct soap* soap, struct _trt__GetOSDs *trt__GetOSDs, struct _trt__GetOSDsResponse *trt__GetOSDsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSD(struct soap* soap, struct _trt__GetOSD *trt__GetOSD, struct _trt__GetOSDResponse *trt__GetOSDResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDOptions(struct soap* soap, struct _trt__GetOSDOptions *trt__GetOSDOptions, struct _trt__GetOSDOptionsResponse *trt__GetOSDOptionsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__SetOSD(struct soap* soap, struct _trt__SetOSD *trt__SetOSD, struct _trt__SetOSDResponse *trt__SetOSDResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateOSD(struct soap* soap, struct _trt__CreateOSD *trt__CreateOSD, struct _trt__CreateOSDResponse *trt__CreateOSDResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteOSD(struct soap* soap, struct _trt__DeleteOSD *trt__DeleteOSD, struct _trt__DeleteOSDResponse *trt__DeleteOSDResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetServiceCapabilities(struct soap* soap, struct _trv__GetServiceCapabilities *trv__GetServiceCapabilities, struct _trv__GetServiceCapabilitiesResponse *trv__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceivers(struct soap* soap, struct _trv__GetReceivers *trv__GetReceivers, struct _trv__GetReceiversResponse *trv__GetReceiversResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceiver(struct soap* soap, struct _trv__GetReceiver *trv__GetReceiver, struct _trv__GetReceiverResponse *trv__GetReceiverResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__CreateReceiver(struct soap* soap, struct _trv__CreateReceiver *trv__CreateReceiver, struct _trv__CreateReceiverResponse *trv__CreateReceiverResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__DeleteReceiver(struct soap* soap, struct _trv__DeleteReceiver *trv__DeleteReceiver, struct _trv__DeleteReceiverResponse *trv__DeleteReceiverResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__ConfigureReceiver(struct soap* soap, struct _trv__ConfigureReceiver *trv__ConfigureReceiver, struct _trv__ConfigureReceiverResponse *trv__ConfigureReceiverResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__SetReceiverMode(struct soap* soap, struct _trv__SetReceiverMode *trv__SetReceiverMode, struct _trv__SetReceiverModeResponse *trv__SetReceiverModeResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __trv__GetReceiverState(struct soap* soap, struct _trv__GetReceiverState *trv__GetReceiverState, struct _trv__GetReceiverStateResponse *trv__GetReceiverStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetServiceCapabilities(struct soap* soap, struct _tse__GetServiceCapabilities *tse__GetServiceCapabilities, struct _tse__GetServiceCapabilitiesResponse *tse__GetServiceCapabilitiesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingSummary(struct soap* soap, struct _tse__GetRecordingSummary *tse__GetRecordingSummary, struct _tse__GetRecordingSummaryResponse *tse__GetRecordingSummaryResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingInformation(struct soap* soap, struct _tse__GetRecordingInformation *tse__GetRecordingInformation, struct _tse__GetRecordingInformationResponse *tse__GetRecordingInformationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetMediaAttributes(struct soap* soap, struct _tse__GetMediaAttributes *tse__GetMediaAttributes, struct _tse__GetMediaAttributesResponse *tse__GetMediaAttributesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindRecordings(struct soap* soap, struct _tse__FindRecordings *tse__FindRecordings, struct _tse__FindRecordingsResponse *tse__FindRecordingsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetRecordingSearchResults(struct soap* soap, struct _tse__GetRecordingSearchResults *tse__GetRecordingSearchResults, struct _tse__GetRecordingSearchResultsResponse *tse__GetRecordingSearchResultsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindEvents(struct soap* soap, struct _tse__FindEvents *tse__FindEvents, struct _tse__FindEventsResponse *tse__FindEventsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetEventSearchResults(struct soap* soap, struct _tse__GetEventSearchResults *tse__GetEventSearchResults, struct _tse__GetEventSearchResultsResponse *tse__GetEventSearchResultsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindPTZPosition(struct soap* soap, struct _tse__FindPTZPosition *tse__FindPTZPosition, struct _tse__FindPTZPositionResponse *tse__FindPTZPositionResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetPTZPositionSearchResults(struct soap* soap, struct _tse__GetPTZPositionSearchResults *tse__GetPTZPositionSearchResults, struct _tse__GetPTZPositionSearchResultsResponse *tse__GetPTZPositionSearchResultsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetSearchState(struct soap* soap, struct _tse__GetSearchState *tse__GetSearchState, struct _tse__GetSearchStateResponse *tse__GetSearchStateResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__EndSearch(struct soap* soap, struct _tse__EndSearch *tse__EndSearch, struct _tse__EndSearchResponse *tse__EndSearchResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__FindMetadata(struct soap* soap, struct _tse__FindMetadata *tse__FindMetadata, struct _tse__FindMetadataResponse *tse__FindMetadataResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tse__GetMetadataSearchResults(struct soap* soap, struct _tse__GetMetadataSearchResults *tse__GetMetadataSearchResults, struct _tse__GetMetadataSearchResultsResponse *tse__GetMetadataSearchResultsResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}





