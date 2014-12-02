/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke.
 *       Filename:  onvif_common.h
 *
 *    Description:  
 *         Others:  Need to include this file,if you want to compile the whole project.
 *   
 *        Version:  1.0
 *        Date:  2014/7/24 14:38:36
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:   Created by housir
 *
 * =====================================================================================
 */


#ifndef  __ONVIF_COMMON_H__
#define  __ONVIF_COMMON_H__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <time.h>
#include <string.h>

#include "soapH.h"
#include "soapStub.h"
#include "onvif_function.h"
#include "onvif_imaging.h"
#include "onvif_media.h"
#include "include.h"

#include "onvif_net.h"

/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
extern int init_env();

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


int soap_sender_2fault_subcode(struct soap *soap, const char *faultsubcodeQName,
        const char *faultsubcodeQName1, const char *faultstring, const char *faultdetailXML);

int soap_receiver_2fault_subcode(struct soap *soap, const char *faultsubcodeQName,
        const char *faultsubcodeQName1, const char *faultstring, const char *faultdetailXML);

#endif   /* ----- #ifndef __ONVIF_COMMON_H__  ----- */
