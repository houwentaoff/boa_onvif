/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke.
 *       Filename:  onvif_discovery.c
 *
 *    Description:
 *         Others:
 *
 *        Version:  1.0
 *        Date:  2014/7/24 14:46:45
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:   Created by housir
 *
 * =====================================================================================
 */

#include "onvif_discovery.h"


/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Hello(struct soap* soap, struct wsdd__HelloType *wsdd__Hello)
{
//    char _IPAddr[INFO_LENGTH];
    char mulcast[MAX_PROF_TOKEN] = {0};
//    unsigned int localIp = 0;
    unsigned char macaddr[6] = {0};
    char _HwId[1024] = {0};
    int i=0;

//    printf("Sean:===>%s():\n", __func__);
    FUN_IN();


    netGetMac(ETHERNET_ADAPT, macaddr);
    sprintf(_HwId,"urn:uuid:2419d68a-2dd2-21b2-a205-%02X%02X%02X%02X%02X%02X",macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);

    struct wsdd__HelloType *Hello;

    Hello = (struct wsdd__HelloType *)soap_malloc(soap, sizeof(struct wsdd__HelloType));
    memset(Hello, 0, sizeof(struct wsdd__HelloType));
    soap_default_wsdd__HelloType(soap, Hello);
    soap_default_wsa__EndpointReferenceType(soap, &(Hello->wsa__EndpointReference));

#if 0/*{{{*/
    Hello->wsa__EndpointReference.ReferenceProperties = (struct wsa__ReferencePropertiesType*)soap_malloc(soap,sizeof(struct wsa__ReferencePropertiesType));
    Hello->wsa__EndpointReference.ReferenceParameters = (struct wsa__ReferenceParametersType*)soap_malloc(soap,sizeof(struct wsa__ReferenceParametersType));
    Hello->wsa__EndpointReference.ServiceName = (struct wsa__ServiceNameType*)soap_malloc(soap,sizeof(struct wsa__ServiceNameType));
    Hello->wsa__EndpointReference.PortType = (char **)soap_malloc(soap, sizeof(char *) * SMALL_INFO_LENGTH);
    Hello->wsa__EndpointReference.__any = (char **)soap_malloc(soap, sizeof(char*) * SMALL_INFO_LENGTH);
    Hello->wsa__EndpointReference.__anyAttribute = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
#endif/*}}}*/
    Hello->wsa__EndpointReference.Address = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(Hello->wsa__EndpointReference.Address, _HwId);

#if 0/*{{{*/
    //ws-discovery规定 为可选项
    Hello->wsa__EndpointReference.ReferenceProperties->__size = 0;
    Hello->wsa__EndpointReference.ReferenceProperties->__any = NULL;
    Hello->wsa__EndpointReference.ReferenceParameters->__size = 0;
    Hello->wsa__EndpointReference.ReferenceParameters->__any = NULL;

    Hello->wsa__EndpointReference.PortType[0] = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
    //ws-discovery规定 为可选项
    strcpy(Hello->wsa__EndpointReference.PortType[0], "ttl");
    Hello->wsa__EndpointReference.ServiceName->__item = NULL;
    Hello->wsa__EndpointReference.ServiceName->PortName = NULL;
    Hello->wsa__EndpointReference.ServiceName->__anyAttribute = NULL;
    Hello->wsa__EndpointReference.__any[0] = (char *)soap_malloc(soap, sizeof(char) * SMALL_INFO_LENGTH);
    strcpy(Hello->wsa__EndpointReference.__any[0], "Any");
    strcpy(Hello->wsa__EndpointReference.__anyAttribute, "Attribute");
    Hello->wsa__EndpointReference.__size = 0;
#endif/*}}}*/

    Hello->Types = (char *)soap_malloc(soap, INFO_LENGTH * sizeof(char));//Qname
    strcpy(Hello->Types, "tdn:NetworkVideoTransmitter");
    Hello->Scopes = (struct wsdd__ScopesType *)soap_malloc(soap, sizeof(struct wsdd__ScopesType));
    soap_default_wsdd__ScopesType(soap, Hello->Scopes);
    Hello->Scopes->__item =(char *)soap_malloc(soap, 1024);
    memset(Hello->Scopes->__item, 0, sizeof(Hello->Scopes->__item));
    //Scopes MUST BE
    strcpy(Hello->Scopes->__item, g_GkIpc_OnvifInf.Scopes[0]->ScopeItem);

    for(i=1;NULL != g_GkIpc_OnvifInf.Scopes[i];i++)
    {
        strcat(Hello->Scopes->__item," ");
        strcat(Hello->Scopes->__item, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
    }

    Hello->Scopes->MatchBy = NULL;//???


    Hello->XAddrs = (char *)soap_malloc(soap, INFO_LENGTH * sizeof(char));
    if (NULL != wsdd__Hello)
    {
        if (NULL != wsdd__Hello->Types)
        {
            printf("wsdd__Hello->Types[%s]\n", wsdd__Hello->Types);
        }
        if (NULL != wsdd__Hello->XAddrs)
        {
            printf("wsdd__Hello->XAddrs[%s]\n", wsdd__Hello->XAddrs);
        }
        if (NULL != wsdd__Hello->Scopes && (NULL != wsdd__Hello->Scopes->__item))
        {
            printf("wsdd__Hello->Scopes[NOT NULL]Scopes[%s]\n",wsdd__Hello->Scopes->__item);
        }
    }


    strcpy(Hello->XAddrs, g_GkIpc_OnvifInf.XAddrs);
    Hello->MetadataVersion = 4;//wsdd__Hello->MetadataVersion;


    if (NULL == soap->header)
    {
        soap->header = (struct SOAP_ENV__Header *)soap_malloc(soap, sizeof(struct SOAP_ENV__Header ) );
        soap_default_SOAP_ENV__Header(soap, soap->header);
    }
    soap->header->wsa__To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Hello";

    soap->header->wsa__MessageID =(char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(soap->header->wsa__MessageID, _HwId+4);


    sprintf(mulcast,"soap.udp://%s:%d/", MULTICAST_ADDRESS, MUL_ONVIFMUL_PORT);
    if (SOAP_OK == soap_send___wsdd__Hello(soap, mulcast, NULL, Hello))
    {
        printf("send wsdd__Hello success !\n");
        FUN_OUT();
        return SOAP_OK;
    }
    printf("[%d] soap error: %d, %s, %s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));

    FUN_OUT();
    return soap->error;;
}

SOAP_FMAC5 int SOAP_FMAC6 __wsdd__Bye(struct soap* soap, struct wsdd__ByeType *_wsdd__Bye)
{
    unsigned char macaddr[6] = {0};
    char _HwId[1024] = {0};
    struct wsdd__ByeType *wsdd__Bye = NULL;
    char mulcast[MAX_PROF_TOKEN] = {0};
    int i=0;

 //   FUN_IN();
    fprintf(stderr, "[onvif]===probe===\n");

    netGetMac(ETHERNET_ADAPT, macaddr);
    sprintf(_HwId,"urn:uuid:2419d68a-2dd2-21b2-a205-%02X%02X%02X%02X%02X%02X",macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);

    wsdd__Bye = (struct wsdd__ByeType *)soap_malloc(soap, sizeof(struct wsdd__ByeType));
    soap_default_wsdd__ByeType(soap, wsdd__Bye);
    wsdd__Bye->wsa__EndpointReference.Address = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(wsdd__Bye->wsa__EndpointReference.Address, _HwId);

    wsdd__Bye->Types = (char *)soap_malloc(soap, 100 * sizeof(char));
    strcpy(wsdd__Bye->Types, "tdn:NetworkVideoTransmitter");
    wsdd__Bye->Scopes = (struct wsdd__ScopesType *)soap_malloc(soap, sizeof(struct wsdd__ScopesType));
    wsdd__Bye->Scopes->__item =(char *)soap_malloc(soap, 1024);
    memset(wsdd__Bye->Scopes->__item, 0, 1024);

    //Scopes MUST BE
    strcpy(wsdd__Bye->Scopes->__item, g_GkIpc_OnvifInf.Scopes[0]->ScopeItem);

    for(i=1;NULL != g_GkIpc_OnvifInf.Scopes[i];i++)
    {
        strcat(wsdd__Bye->Scopes->__item," ");
        strcat(wsdd__Bye->Scopes->__item, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
    }
    wsdd__Bye->Scopes->MatchBy = NULL;
    wsdd__Bye->XAddrs = (char *)soap_malloc(soap, INFO_LENGTH * sizeof(char));
    strcpy(wsdd__Bye->XAddrs, g_GkIpc_OnvifInf.XAddrs);
    wsdd__Bye->MetadataVersion = (unsigned int *)soap_malloc(soap, sizeof(unsigned int));
    *wsdd__Bye->MetadataVersion = 4;
    //    printf("XAddrs[%s]MetadataVersion[%d]\n", wsdd__Bye->XAddrs, *(wsdd__Bye->MetadataVersion));
    /*-----------------------------------------------------------------------------
     *  head设置
     *-----------------------------------------------------------------------------*/
    if (NULL == soap->header)
    {
        soap->header = (struct SOAP_ENV__Header *)soap_malloc(soap, sizeof(struct SOAP_ENV__Header) );
        soap_default_SOAP_ENV__Header(soap, soap->header);
    }

    soap->header->wsa__To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Bye";

    soap->header->wsa__MessageID =(char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(soap->header->wsa__MessageID, _HwId+4);
    sprintf(mulcast,"soap.udp://%s:%d/", MULTICAST_ADDRESS, MUL_ONVIFMUL_PORT);
    if (SOAP_OK != soap_send___wsdd__Bye(soap, mulcast, NULL, wsdd__Bye))
    {
        printf("send soap_send___wsdd__Bye success !\n");
        printf("[%d] soap error: %d, %s, %s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
        FUN_OUT();
        return soap->error;;
    }

    FUN_OUT();

    return soap->error;;
}

SOAP_FMAC5 int SOAP_FMAC6  __wsdd__Probe(struct soap* soap, struct wsdd__ProbeType *wsdd__Probe)
{
    unsigned char macaddr[16] = {0};
    char _HwId[500] = {0};
    struct sockaddr addr;
    int i=0;

    FUN_IN();

    if (tt__DiscoveryMode__Discoverable != g_GkIpc_OnvifInf.discoverymode)
    {
        return SOAP_OK;
    }
    if(soap->header == NULL)
    {
        PRINT_DBG("header NULL\n");
    }
    else
    {
//        PRINT_DBG("wsa__To[%s]wsa__Action[%s]\n", soap->header->wsa__To, soap->header->wsa__Action);
    }
    /* :TODO:Saturday, July 05, 2014 05:30:13 HKT:SeanHou: 客户端发来Device 和 NetworkVideoTransmitter 是什么意思，我们只是取一个匹配么，加上probe不到 */
#if 0
    if (0 != strcmp(wsdd__Probe->Types, "tdn:NetworkVideoTransmitter" ))
    {
        printf("!!!ERROR!!!get from client:wsdd__Probe->Types=%s\n",wsdd__Probe->Types);
        return SOAP_OK;
        //        ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
    }
#endif
    /* :TODO:End---  */
    gNetworkAdapterConfiguration.get_ip(ETHERNET_ADAPT, &addr);

    gNetworkAdapterConfiguration.get_hwaddr(ETHERNET_ADAPT, macaddr);
    sprintf(_HwId,"urn:uuid:2419d68a-2dd2-21b2-a205-%02X%02X%02X%02X%02X%02X",macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);
//    PRINT_DBG("hwid[%s]\n", _HwId);

#if 1
    wsdd__ProbeMatchesType ProbeMatches;
    soap_default_wsdd__ProbeMatchesType(soap, &ProbeMatches);
    ProbeMatches.__sizeProbeMatch = 1;
    gNetworkAdapterConfiguration.get_netmask(ETHERNET_ADAPT, &addr);
    ProbeMatches.ProbeMatch = (struct wsdd__ProbeMatchType *)soap_malloc(soap, sizeof(struct wsdd__ProbeMatchType));
    soap_default_wsdd__ProbeMatchType(soap, ProbeMatches.ProbeMatch);
    ProbeMatches.ProbeMatch->XAddrs = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);/* must be XAddrs is a space separated list of URLs to the Device service:*/
    ProbeMatches.ProbeMatch->Types = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);/*must be*/

    /*-----------------------------------------------------------------------------
     *  EndpointReference
     *-----------------------------------------------------------------------------*/
    soap_default_wsa__EndpointReferenceType(soap, &(ProbeMatches.ProbeMatch->wsa__EndpointReference));
    ProbeMatches.ProbeMatch->wsa__EndpointReference.Address = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);/*must be*/
    strcpy(ProbeMatches.ProbeMatch->wsa__EndpointReference.Address, _HwId);

    /*-----------------------------------------------------------------------------
     *  others  Types scope Xaddr metadataVersion must be
     *-----------------------------------------------------------------------------*/
    strcpy(ProbeMatches.ProbeMatch->XAddrs, g_GkIpc_OnvifInf.XAddrs);
//    printf("xaddr[%s]\n", g_GkIpc_OnvifInf.XAddrs);
    ProbeMatches.ProbeMatch->Scopes = (struct wsdd__ScopesType *)soap_malloc(soap,sizeof(struct wsdd__ScopesType));/*must be*/
    soap_default_wsdd__ScopesType(soap,  ProbeMatches.ProbeMatch->Scopes);
    ProbeMatches.ProbeMatch->Scopes->__item =(char *)soap_malloc(soap, 1024);


    strcpy(ProbeMatches.ProbeMatch->Scopes->__item, g_GkIpc_OnvifInf.Scopes[0]->ScopeItem);

    for(i=1;NULL != g_GkIpc_OnvifInf.Scopes[i];i++)
    {
        strcat(ProbeMatches.ProbeMatch->Scopes->__item," ");
        strcat(ProbeMatches.ProbeMatch->Scopes->__item, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
    }

    strcpy(ProbeMatches.ProbeMatch->Types, "tdn:NetworkVideoTransmitter");
    ProbeMatches.ProbeMatch->MetadataVersion = 4;/*must be*/


//    printf("Sean ===> %s()line[%d]:\n", __func__, __LINE__);
    //    soap_default_SOAP_ENV__Header(soap, soap->header);//加了这句，会使发送中的wsa__RelatesTo丢失,导致客户端匹配不到
    soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
//    soap->header->wsa__To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";
    soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
//    printf("Sean ===> %s()line[%d]:\n", __func__, __LINE__);
    soap->header->wsa__RelatesTo = (struct wsa__Relationship*)soap_malloc(soap, sizeof(struct wsa__Relationship));
    soap_default_wsa__Relationship(soap, soap->header->wsa__RelatesTo);
    soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;
    soap->header->wsa__MessageID =(char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
//    printf("Sean ===> %s()line[%d]Scopes[0x%x]\n", __func__, __LINE__, wsdd__Probe->Scopes);
    strcpy(soap->header->wsa__MessageID,_HwId+4);

    if ((NULL != wsdd__Probe->Scopes) && (NULL != wsdd__Probe->Scopes->__item) && *(wsdd__Probe->Scopes->__item))//scope不匹配
    {

        PRINT_DBG("Sean ===> %s():line[%d]item[%s]\n", __func__, __LINE__, wsdd__Probe->Scopes->__item);
        bool match=false;
        char *delimPos = NULL;
        char *p = wsdd__Probe->Scopes->__item;
        delimPos = strtok(p, " ");
        for(i =0;NULL != g_GkIpc_OnvifInf.Scopes[i];i++)
        {
            if (true == compare_match(delimPos, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem))
            {
               match = true;
               break;
            }
        }
        while((delimPos = strtok(NULL, " ")))
        {
            for(i =0;NULL != g_GkIpc_OnvifInf.Scopes[i];i++)
            {
                if (true == compare_match(delimPos, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem))
                {
                   match = true;
                   break;
                }
            }
            if (NULL == g_GkIpc_OnvifInf.Scopes[i])
            {
                match = false;
                break;
            }
        }
        if (false == match)
        {
            PRINT_DBG("Sean ===> %s():line[%d]path[%s]\n", __func__, __LINE__, soap->path);
            soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/fault";
            ONVIF_SENDER_ERROR(soap, NULL, "ter:MatchingRuleNotSuported", "the matching rule spec is not supported", NULL);
        }
  }
    if (SOAP_OK == soap_send___wsdd__ProbeMatches(soap, NULL, NULL, &ProbeMatches))
    {
        if(soap->header == NULL)
        {
            PRINT_DBG("header NULL\n");
        }
        else
        {
            ;
//            PRINT_DBG("wsa__To[%s]wsa__Action[%s]\n", soap->header->wsa__To, soap->header->wsa__Action);
        }
        PRINT_DBG("send ProbeMatches success !\n");
        PRINT_DBG("Sean <=== %s():line[%d]\n", __func__, __LINE__);
        return SOAP_OK;
    }
    PRINT_DBG("[%d] soap error: %d, %s, %s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
#endif
    FUN_OUT();
        return SOAP_OK;

    return soap->error;;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetScopes(struct soap* soap, struct _tds__GetScopes *tds__GetScopes, struct _tds__GetScopesResponse *tds__GetScopesResponse)
{
    int num_scope = 0;
    char *temp = NULL;
    int i=0;

    FUN_IN();

    soap_default__tds__GetScopesResponse(soap, tds__GetScopesResponse);

    /*-----------------------------------------------------------------------------
     *  计算scope的个数
     *-----------------------------------------------------------------------------*/

    while (NULL != g_GkIpc_OnvifInf.Scopes[num_scope++]){};
    num_scope = num_scope-1;
    tds__GetScopesResponse->__sizeScopes = num_scope;

    tds__GetScopesResponse->Scopes = (struct tt__Scope*)soap_malloc(soap, num_scope * sizeof(struct tt__Scope));

    for(i=0;i<num_scope;i++)
    {
        temp= (char *)soap_malloc(soap, LEN_URL * sizeof(char));
        strcpy(temp, g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
        tds__GetScopesResponse->Scopes[i].ScopeItem = temp;
        tds__GetScopesResponse->Scopes[i].ScopeDef = g_GkIpc_OnvifInf.Scopes[i]->ScopeDef;
    }

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetScopes(struct soap* soap, struct _tds__SetScopes *tds__SetScopes, struct _tds__SetScopesResponse *tds__SetScopesResponse)
{
    int i=0;
    char *temp;
    int size = tds__SetScopes->__sizeScopes;

    FUN_IN("size[%d]\n", size);
    if (tds__SetScopes->Scopes[size] != NULL)
    {
        goto overwrite;
    }

    /*-----------------------------------------------------------------------------
     *  free ScopeItem
     *-----------------------------------------------------------------------------*/
    while(NULL != g_GkIpc_OnvifInf.Scopes[i])
    {
        free(g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
        free(g_GkIpc_OnvifInf.Scopes[i]);
        i++;
    }
    free(g_GkIpc_OnvifInf.Scopes);
    g_GkIpc_OnvifInf.Scopes = NULL;


    /*-----------------------------------------------------------------------------
     *  copy
     *-----------------------------------------------------------------------------*/
    g_GkIpc_OnvifInf.Scopes = (struct tt__Scope **)malloc((size+1) * sizeof(struct tt__Scope *));

    if (g_GkIpc_OnvifInf.Scopes == NULL)
    {
        return -1;
    }
    FUN_IN("line[%d]\n", __LINE__);

    for(i=0;i<size;i++)
    {
        FUN_IN("line[%d]\n", __LINE__);
        g_GkIpc_OnvifInf.Scopes[i] = (struct tt__Scope *)malloc(sizeof(struct tt__Scope ));
        temp = (char *)malloc((strlen(tds__SetScopes->Scopes[i]) + 1)* sizeof(char));
        if (NULL == temp)
        {
            return -1;
        }
        strcpy(temp, tds__SetScopes->Scopes[i]);
        FUN_IN("line[%d]\n", __LINE__);
        g_GkIpc_OnvifInf.Scopes[i]->ScopeItem = temp;
        g_GkIpc_OnvifInf.Scopes[i]->ScopeDef = tt__ScopeDefinition__Fixed;
    }
    g_GkIpc_OnvifInf.Scopes[i] = NULL;

    FUN_OUT();

    return SOAP_OK;
overwrite:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:OperationProhibited", "ter:ScopeOverwrite", "Scope parameter overwrites fixed device scope setting,command rejected", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddScopes(struct soap* soap, struct _tds__AddScopes *tds__AddScopes, struct _tds__AddScopesResponse *tds__AddScopesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveScopes(struct soap* soap, struct _tds__RemoveScopes *tds__RemoveScopes, struct _tds__RemoveScopesResponse *tds__RemoveScopesResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDiscoveryMode(struct soap* soap, struct _tds__GetDiscoveryMode *tds__GetDiscoveryMode, struct _tds__GetDiscoveryModeResponse *tds__GetDiscoveryModeResponse)
{
    FUN_IN();

    /*Sean Hou: required element of type tt:DiscoveryMode */
    tds__GetDiscoveryModeResponse->DiscoveryMode = g_GkIpc_OnvifInf.discoverymode;
#if 0
    if (NULL == soap->header)
    {
        soap->header = (struct SOAP_ENV__Header *)soap_malloc(soap, sizeof(struct SOAP_ENV__Header) );
        soap_default_SOAP_ENV__Header(soap, soap->header);
    }
    soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing";
    soap->header->wsa__Action = "http://www.onvif.org/ver10/device/wsdl/GetDiscoveryModeRespons";
#endif
    FUN_OUT();

    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDiscoveryMode(struct soap* soap, struct _tds__SetDiscoveryMode *tds__SetDiscoveryMode, struct _tds__SetDiscoveryModeResponse *tds__SetDiscoveryModeResponse)
{
    FUN_IN();

    g_GkIpc_OnvifInf.discoverymode = tds__SetDiscoveryMode->DiscoveryMode;
#if 0
    if (NULL == soap->header)
    {
        soap->header = (struct SOAP_ENV__Header *)soap_malloc(soap, sizeof(struct SOAP_ENV__Header) );
        soap_default_SOAP_ENV__Header(soap, soap->header);
    }
    soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
    soap->header->wsa__Action = "http://www.onvif.org/ver10/device/wsdl/SetDiscoveryModeResponse";
#endif
    FUN_OUT();

    return SOAP_OK;

}

