/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke.
 *       Filename:  onvif_common.c
 *
 *    Description:  
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  2014/7/24 15:06:56
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:   Created by housir
 *
 * =====================================================================================
 */

#include "onvif_common.h"

static inline int onvif_receiver_fault_subcode_oom(struct soap *soap)
{
    return soap_receiver_fault_subcode(soap, "ter:OutofMemory", "Out of Memory", "The device does not have sufficient memory to complete the action.");
}

int soap_sender_2fault_subcode(struct soap *soap, const char *faultsubcodeQName,
        const char *faultsubcodeQName1, const char *faultstring, const char *faultdetailXML)
{
    int ret = soap_sender_fault_subcode(soap, 
            faultsubcodeQName, faultstring, faultdetailXML);
    soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode =
        (struct SOAP_ENV__Code *)soap_malloc(soap, sizeof(struct SOAP_ENV__Code));
    soap_default_SOAP_ENV__Code(soap, soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode);
    soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value =
        soap_strdup(soap, faultsubcodeQName1);
    return ret;
}

int soap_receiver_2fault_subcode(struct soap *soap, const char *faultsubcodeQName,
        const char *faultsubcodeQName1, const char *faultstring, const char *faultdetailXML)
{
    int ret = soap_receiver_fault_subcode(soap, 
            faultsubcodeQName, faultstring, faultdetailXML);
    soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode =
        (struct SOAP_ENV__Code *)soap_malloc(soap, sizeof(struct SOAP_ENV__Code));
    soap_default_SOAP_ENV__Code(soap, soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode);
    soap->fault->SOAP_ENV__Code->SOAP_ENV__Subcode->SOAP_ENV__Subcode->SOAP_ENV__Value =
        soap_strdup(soap, faultsubcodeQName1);
    return ret;
}

