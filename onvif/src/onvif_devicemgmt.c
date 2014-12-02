/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke.
 *       Filename:  onvif_devicemgmt.c
 *
 *    Description:
 *         Others:
 *
 *        Version:  1.0
 *        Date:  2014/7/24 14:42:55
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:   Created by housir
 *
 * =====================================================================================
 */

#include "onvif_devicemgmt.h"
//#include "onvif_common.h"

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */

#define COUNT_DEL            10/*  */
#define COUNT_MODFY         10 /*  */
#define START_TIME_YEAR     1900            /*  */


/* #####   EXPORTED FUNCTION DECLARATIONS   ######################################### */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServices(struct soap* soap, struct _tds__GetServices *tds__GetServices, struct _tds__GetServicesResponse *tds__GetServicesResponse)
{
    FUN_IN();

    char _IPAddr[INFO_LENGTH];
    int i = 0;
    struct sockaddr addr;

    /*-----------------------------------------------------------------------------
     *  NVT需要实�?device,events,media,PTZ,Imaging,Video Analytics, Device IO
     *-----------------------------------------------------------------------------*/
    const char *  tds	= "http://www.onvif.org/ver10/device/wsdl";
    const char *  tev	= "http://www.onvif.org/ver10/events/wsdl";
    //    const char *  tls	= "http://www.onvif.org/ver10/display/wsdl";
    const char *  tmd	= "http://www.onvif.org/ver10/deviceIO/wsdl";
    const char *  timg	= "http://www.onvif.org/ver20/imaging/wsdl";
    const char *  trt	= "http://www.onvif.org/ver10/media/wsdl";
    const char *  tptz	= "http://www.onvif.org/ver20/ptz/wsdl";
    //    const char *  trv	= "http://www.onvif.org/ver10/receiver/wsdl";
    //    const char *  trc	= "http://www.onvif.org/ver10/recording/wsdl";
    //    const char *  tse	= "http://www.onvif.org/ver10/search/wsdl";
    //    const char *  trp	= "http://www.onvif.org/ver10/replay/wsdl";
    //    const char *  tan	= "http://www.onvif.org/ver20/analytics/wsdl";
    //    const char *  tad	= "http://www.onvif.org/ver10/analyticsdevice/wsdl";
    const char *  tdn	= "http://www.onvif.org/ver10/network/wsdl";
    const char *  tt	= "http://www.onvif.org/ver10/schema";
    const char *  ter   = "http://www.onvif.org/ver10/error";
    const char *services[]={tds, tev, tmd, timg, trt, tptz, tdn, tt, ter, NULL};

    /*-----------------------------------------------------------------------------
     *  if include Capabilities must be
     *-----------------------------------------------------------------------------*/

    const char *  device = "<tds:Capabilities> <tds:Network IPFilter=\"false\" etwork=\"true\" /> <tds:Security TLS1.0=\"false\" etwork=\"true\" /> <tds:System DiscoveryResolve=\"false\" etwork=\"true\" /> </tds:Capabilities>";
    const char *  event = "<tev:Capabilities> <tev:Network IPFilter=\"false\" etwork=\"true\" /> <tev:Security TLS1.0=\"false\" etwork=\"true\" /> <tev:System DiscoveryResolve=\"false\" etwork=\"true\" /> </tev:Capabilities>";
    const char *  image = "<timg:Capabilities> <timg:Network IPFilter=\"false\" etwork=\"true\" /> <timg:Security TLS1.0=\"false\" etwork=\"true\" /> <timg:System DiscoveryResolve=\"false\" etwork=\"true\" /> </timg:Capabilities>";
    const char *  media = "<trt:Capabilities> <trt:Network IPFilter=\"false\" etwork=\"true\" /> <trt:Security TLS1.0=\"false\" etwork=\"true\" /> <trt:System DiscoveryResolve=\"false\" etwork=\"true\" /> </trt:Capabilities>";
    const char *  ptz = "<tptz:Capabilities> <tptz:Network IPFilter=\"false\" etwork=\"true\" /> <tptz:Security TLS1.0=\"false\" etwork=\"true\" /> <tptz:System DiscoveryResolve=\"false\" etwork=\"true\" /> </tptz:Capabilities>";
    const char * service_caplties[]={device, event, NULL, image, media, ptz, NULL, NULL, NULL, NULL};
//    const char * service_caplties[]={device, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

    gNetworkAdapterConfiguration.get_ip(ETHERNET_ADAPT, &addr);
    sprintf(_IPAddr, "http://%s:%d/onvif/services", inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr), ONVIF_REQ_LISTEN_PORT);

    tds__GetServicesResponse->__sizeService = sizeof(services)/sizeof(char *) - 1;

    //    if(xsd__boolean__false_  == tds__GetServices->IncludeCapability)

    tds__GetServicesResponse->Service = (struct tds__Service *)soap_malloc(soap, tds__GetServicesResponse->__sizeService * sizeof(struct tds__Service));
    /*-----------------------------------------------------------------------------
     *  若为"http://www.onvif.org/ver10/media/wsdl" 则对�?测试工具接收media service
     *  信息，若为event/wsdl则只能接收event信息,除非在客户端include 性能=true的情�?
     *  下可以接�?和测试项目的矛盾怎么�?会在传入参数中有所体现�?
     *-----------------------------------------------------------------------------*/


    for(i=0;NULL!=services[i];i++)
    {
        soap_default_tds__Service(soap, &(tds__GetServicesResponse->Service[i]));
        tds__GetServicesResponse->Service[i].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
        tds__GetServicesResponse->Service[i].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
        strcpy(tds__GetServicesResponse->Service[i].Namespace, services[i]);

        strcpy(tds__GetServicesResponse->Service[i].XAddr, _IPAddr);

        if(xsd__boolean__false_  == tds__GetServices->IncludeCapability)
        {
            tds__GetServicesResponse->Service[i].Capabilities = NULL;
        }
        else
        {
            tds__GetServicesResponse->Service[i].Capabilities = (struct _tds__Service_Capabilities *)soap_malloc(soap, sizeof(struct _tds__Service_Capabilities));

            /*-----------------------------------------------------------------------------
             *  需要对其域�?提供功能的true或者false XML格式返回,如下
             *-----------------------------------------------------------------------------*/
            if (service_caplties[i])
            {
                tds__GetServicesResponse->Service[i].Capabilities->__any = (char *)soap_malloc(soap, INFO_LENGTH * sizeof(char));
                sprintf(tds__GetServicesResponse->Service[i].Capabilities->__any, "%s", service_caplties[i]);
                PRINT_ERR("ANY[%s]\n", tds__GetServicesResponse->Service[i].Capabilities->__any);
            }
            else
            {
                tds__GetServicesResponse->Service[i].Capabilities->__any = NULL;
                PRINT_ERR("service_caplties[%d] is NULL\n", i);
            }
        }
        tds__GetServicesResponse->Service[i].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
        tds__GetServicesResponse->Service[i].Version->Major = 0;
        tds__GetServicesResponse->Service[i].Version->Minor = 3;

        tds__GetServicesResponse->Service[i].__any = NULL;
        tds__GetServicesResponse->Service[i].__size = 0;
        tds__GetServicesResponse->Service[i].__anyAttribute = NULL;
    }
 /* :TODO:Saturday, July 19, 2014 12:07:12 HKT:SeanHou:  */
#if 0
    /*-----------------------------------------------------------------------------
     *  device service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[0].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[0].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[0].Namespace, "http://www.onvif.org/ver10/device/wsdl");

    strcpy(tds__GetServicesResponse->Service[0].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[0].Capabilities = NULL;
    tds__GetServicesResponse->Service[0].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[0].Version->Major = 0;
    tds__GetServicesResponse->Service[0].Version->Minor = 3;

    tds__GetServicesResponse->Service[0].__any = NULL;
    tds__GetServicesResponse->Service[0].__size = NULL;
    tds__GetServicesResponse->Service[0].__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  media service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/media/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  event service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/event/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    /*-----------------------------------------------------------------------------
     *  display service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/display/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    /*-----------------------------------------------------------------------------
     *  deviceIO service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/deviceIO/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  imaging service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver20/imaging/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;


    /*-----------------------------------------------------------------------------
     *  receiver service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/receiver/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    /*-----------------------------------------------------------------------------
     *  ptz service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver20/ptz/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    /*-----------------------------------------------------------------------------
     *  recording service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/recording/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    tds__GetServicesResponse->Service[1].__any = NULL;
    /*-----------------------------------------------------------------------------
     *  search service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/search/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    /*-----------------------------------------------------------------------------
     *  replay service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/replay/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
    /*-----------------------------------------------------------------------------
     *  analytics service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver20/analytics/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  analyticsdevice service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/analyticsdevice/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  network service
     *-----------------------------------------------------------------------------*/
    tds__GetServicesResponse->Service[1].XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    tds__GetServicesResponse->Service[1].Namespace = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetServicesResponse->Service[1].Namespace, "http://www.onvif.org/ver10/network/wsdl");

    strcpy(tds__GetServicesResponse->Service[1].XAddr, _IPAddr);
    tds__GetServicesResponse->Service[1].Capabilities = NULL;
    tds__GetServicesResponse->Service[1].Version = (struct tt__OnvifVersion *)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
    tds__GetServicesResponse->Service[1].Version->Major = 0;
    tds__GetServicesResponse->Service[1].Version->Minor = 4;

    tds__GetServicesResponse->Service[1].__any = NULL;
    tds__GetServicesResponse->Service[1].__size = NULL;
    tds__GetServicesResponse->Service[1].__anyAttribute = NULL;
#endif
 /* :TODO:End---  */

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServiceCapabilities(struct soap* soap, struct _tds__GetServiceCapabilities *tds__GetServiceCapabilities, struct _tds__GetServiceCapabilitiesResponse *tds__GetServiceCapabilitiesResponse)
{
    FUN_IN();


    FUN_OUT();

    return SOAP_OK;
    //    ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDeviceInformation(struct soap* soap, struct _tds__GetDeviceInformation *tds__GetDeviceInformation, struct _tds__GetDeviceInformationResponse *tds__GetDeviceInformationResponse)
{
    FUN_IN();

    /*-----------------------------------------------------------------------------
     *  should read from conf
     *-----------------------------------------------------------------------------*/
    tds__GetDeviceInformationResponse->Manufacturer =  "22222222222";
    tds__GetDeviceInformationResponse->Model =  "11111111111";
    tds__GetDeviceInformationResponse->SerialNumber =  "33333333333";
    tds__GetDeviceInformationResponse->HardwareId =  "444444444444";

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemDateAndTime(struct soap* soap, struct _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, struct _tds__SetSystemDateAndTimeResponse *tds__SetSystemDateAndTimeResponse)
{
    char cmd[LEN_CMD];
    int time_zone=0;
    char sign;
    char TZ[MAX_PROF_TOKEN];
    FILE *fp = NULL;

    FUN_IN();

    if (tds__SetSystemDateAndTime->UTCDateTime)
    {

        if ((tds__SetSystemDateAndTime->UTCDateTime->Date->Year < 0) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Date->Month > 12) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Date->Month < 1) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Date->Day > 31) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Date->Day < 1) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Hour > 59) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Hour < 0) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Minute > 59) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Minute < 0) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Second > 59) ||
                (tds__SetSystemDateAndTime->UTCDateTime->Time->Second < 0)
                )
        {
            goto invaliddatatime;
        }
        if (0 == sprintf(cmd, "date -s \"%04d-%02d-%02d %02d:%02d:%02d\"",
                    tds__SetSystemDateAndTime->UTCDateTime->Date->Year,
                    tds__SetSystemDateAndTime->UTCDateTime->Date->Month,
                    tds__SetSystemDateAndTime->UTCDateTime->Date->Day,
                    tds__SetSystemDateAndTime->UTCDateTime->Time->Hour,
                    tds__SetSystemDateAndTime->UTCDateTime->Time->Minute,
                    tds__SetSystemDateAndTime->UTCDateTime->Time->Second))
        {
            PRINT_ERR();
            goto err;
        }
        printf("cmd[%s]\n", cmd);
        if (NULL == (fp = popen(cmd, "r")))
        {
            PRINT_ERR();
            goto err;
        }

        if (-1 == pclose(fp))
        {
            goto err;
        }
    }

   g_GkIpc_OnvifInf.DateTimeType    = tds__SetSystemDateAndTime->DateTimeType;
   g_GkIpc_OnvifInf.DaylightSavings = tds__SetSystemDateAndTime->DaylightSavings;
   g_GkIpc_OnvifInf.time_zone = 8;

   /*get time from server by using NTP*/
   if (tt__SetDateTimeType__NTP == g_GkIpc_OnvifInf.DateTimeType)
   {
        return SOAP_OK;
   }

   if (tds__SetSystemDateAndTime->TimeZone  && tds__SetSystemDateAndTime->TimeZone->TZ)
   {

       sscanf(tds__SetSystemDateAndTime->TimeZone->TZ, "%3s%c%d", TZ, &sign, &time_zone);
       if (0 != strncmp(TZ, "GMT", sizeof("GMT")))
       {
            PRINT_ERR("%s\n", tds__SetSystemDateAndTime->TimeZone->TZ);
            goto invalidtimezone;
       }
       g_GkIpc_OnvifInf.time_zone = sign == '+' ? time_zone:0-time_zone;
   }

    FUN_OUT();

    return SOAP_OK;

err:
    ONVIF_PROCESS_ERROR(soap, NULL);
invalidtimezone:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidTimeZone", "an invalid time zone was specified", NULL);
invaliddatatime:
	ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidDateTime", "an invalid date or time was specified", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemDateAndTime(struct soap* soap, struct _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, struct _tds__GetSystemDateAndTimeResponse *tds__GetSystemDateAndTimeResponse)
{

    time_t   now;
    struct   tm     *timenow;

    FUN_IN();

    time(&now);
    timenow   =   localtime(&now);

    if (NULL == tds__GetSystemDateAndTimeResponse)
    {
        PRINT_ERR();
        goto err;
    }
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime = (struct tt__SystemDateTime *)soap_malloc(soap, sizeof(struct tt__SystemDateTime));
    soap_default_tt__SystemDateTime(soap, tds__GetSystemDateAndTimeResponse->SystemDateAndTime);

    /*-----------------------------------------------------------------------------
     *  SystemDateTime
     *-----------------------------------------------------------------------------*/
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->DateTimeType = g_GkIpc_OnvifInf.DateTimeType;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->DaylightSavings = g_GkIpc_OnvifInf.DaylightSavings;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->TimeZone = (struct tt__TimeZone *)soap_malloc(soap, sizeof(struct tt__TimeZone));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->TimeZone->TZ = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));

    sprintf(tds__GetSystemDateAndTimeResponse->SystemDateAndTime->TimeZone->TZ, "GMT+%d", g_GkIpc_OnvifInf.time_zone);
 /* :TODO:2014/7/21 14:17:59:Sean:  */
//    strcpy(tds__GetSystemDateAndTimeResponse->SystemDateAndTime->TimeZone->TZ, TIME_ZONE);
 /* :TODO:End---  */

    /*-----------------------------------------------------------------------------
     *  LocalDateTime
     *-----------------------------------------------------------------------------*/
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime = (struct tt__DateTime *)soap_malloc(soap, sizeof(struct tt__DateTime));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Time = (struct tt__Time *)soap_malloc(soap, sizeof(struct tt__Time));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Time->Hour = timenow->tm_hour;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Time->Minute = timenow->tm_min;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Time->Second = timenow->tm_sec;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Date = (struct tt__Date *)soap_malloc(soap, sizeof(struct tt__Date));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Date->Year = timenow->tm_year + START_TIME_YEAR;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Date->Month = timenow->tm_mon + 1;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->LocalDateTime->Date->Day = timenow->tm_mday;

    timenow = gmtime(&now);

    /*-----------------------------------------------------------------------------
     *  UTCDateTime
     *-----------------------------------------------------------------------------*/
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime = (struct tt__DateTime *)soap_malloc(soap, sizeof(struct tt__DateTime));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time = (struct tt__Time *)soap_malloc(soap, sizeof(struct tt__Time));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Hour = timenow->tm_hour;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Minute = timenow->tm_min;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Time->Second = timenow->tm_sec;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date = (struct tt__Date *)soap_malloc(soap, sizeof(struct tt__Date));
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Year = timenow->tm_year + START_TIME_YEAR;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Month = timenow->tm_mon + 1;
    tds__GetSystemDateAndTimeResponse->SystemDateAndTime->UTCDateTime->Date->Day = timenow->tm_mday;

    FUN_OUT();

    return SOAP_OK;
err:
    ONVIF_PROCESS_ERROR(soap, NULL);
}


SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemFactoryDefault(struct soap* soap, struct _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, struct _tds__SetSystemFactoryDefaultResponse *tds__SetSystemFactoryDefaultResponse)
{
    int i=0;

    FUN_IN();
    if (tds__SetSystemFactoryDefault->FactoryDefault == tt__FactoryDefaultType__Soft)
    {
        /*-----------------------------------------------------------------------------
         *  free g_GkIpc_OnvifInf & reinit_env
         *-----------------------------------------------------------------------------*/
        while(NULL != g_GkIpc_OnvifInf.Scopes[i])
        {
            free(g_GkIpc_OnvifInf.Scopes[i]->ScopeItem);
            free(g_GkIpc_OnvifInf.Scopes[i]);
            g_GkIpc_OnvifInf.Scopes[i] = NULL;
            i++;
        }
        free(g_GkIpc_OnvifInf.Scopes);
        g_GkIpc_OnvifInf.Scopes = NULL;

        i = 0;

        while(NULL != g_GkIpc_OnvifInf.User[i])
        {
            free(g_GkIpc_OnvifInf.User[i]->Username);
            if (g_GkIpc_OnvifInf.User[i]->Password)
            {
                free(g_GkIpc_OnvifInf.User[i]->Password);
            }
            if (g_GkIpc_OnvifInf.User[i]->Extension)
            {
                free(g_GkIpc_OnvifInf.User[i]->Extension);
            }
            if (g_GkIpc_OnvifInf.User[i]->__anyAttribute)
            {
                free(g_GkIpc_OnvifInf.User[i]->__anyAttribute);
            }
            free(g_GkIpc_OnvifInf.User[i]);
            g_GkIpc_OnvifInf.User[i] = NULL;
            i++;
        }
        free(g_GkIpc_OnvifInf.User);
        g_GkIpc_OnvifInf.User = NULL;

        init_env();
    }
    else
    {
         raise(SOAP_HELLO);
    }

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SystemReboot(struct soap* soap, struct _tds__SystemReboot *tds__SystemReboot, struct _tds__SystemRebootResponse *tds__SystemRebootResponse)
{

    FUN_IN();

    tds__SystemRebootResponse->Message = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
    strcpy(tds__SystemRebootResponse->Message, "Rebooting in 5 seconds.");
    g_GkIpc_OnvifInf.is_reboot = true;
    raise(SOAP_BYE);

    FUN_OUT();

    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetUsers(struct soap* soap, struct _tds__GetUsers *tds__GetUsers, struct _tds__GetUsersResponse *tds__GetUsersResponse)
{
    int i=0;

    FUN_IN();

    tds__GetUsersResponse->__sizeUser = g_GkIpc_OnvifInf.Usercount;
    tds__GetUsersResponse->User = (struct tt__User *)soap_malloc(soap, tds__GetUsersResponse->__sizeUser * sizeof(struct tt__User));
    while (i<tds__GetUsersResponse->__sizeUser)
    {
        soap_default_tt__User(soap, &(tds__GetUsersResponse->User[i]));
        i++;
    }

    i=0;
    while(i<tds__GetUsersResponse->__sizeUser)
    {
        tds__GetUsersResponse->User[i].Username = (char *)soap_malloc(soap, LEN_USRNAME * sizeof(char));
        strcpy(tds__GetUsersResponse->User[i].Username, g_GkIpc_OnvifInf.User[i]->Username);
        tds__GetUsersResponse->User[i].UserLevel = g_GkIpc_OnvifInf.User[i]->UserLevel;
        i++;
    }

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateUsers(struct soap* soap, struct _tds__CreateUsers *tds__CreateUsers, struct _tds__CreateUsersResponse *tds__CreateUsersResponse)
{
    int i=0;
    int index=0;
    int count = tds__CreateUsers->__sizeUser;
    char *username = NULL;

    FUN_IN();

    /*-----------------------------------------------------------------------------
     *  is exist?
     *-----------------------------------------------------------------------------*/
    if (NULL == tds__CreateUsers->User || (NULL == tds__CreateUsers->User->Username))
    {
        PRINT_ERR();
        goto err;
    }

    for(i=0;i<count;i++)
    {
        username = tds__CreateUsers->User[i].Username;

        if ((index=find_user(username, g_GkIpc_OnvifInf.User)) >= 0)
        {
            goto usernameclash;
        }

        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount] = (struct tt__User *)malloc(sizeof(struct tt__User));
        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->Username    =  (char *)malloc(LEN_USRNAME * sizeof(char));
        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->Password    = (char *)malloc(LEN_PASSWD * sizeof(char));
        strcpy(g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->Username, tds__CreateUsers->User[i].Username);
        strcpy(g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->Password, tds__CreateUsers->User[i].Password);
        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->UserLevel = tds__CreateUsers->User[i].UserLevel;
        /*-----------------------------------------------------------------------------
         *  not copy
         *-----------------------------------------------------------------------------*/
        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->Extension = NULL;
        g_GkIpc_OnvifInf.User[g_GkIpc_OnvifInf.Usercount]->__anyAttribute = NULL;

        g_GkIpc_OnvifInf.Usercount++;
    }
    FUN_OUT();

    return SOAP_OK;

err:
    ONVIF_SENDER_ERROR(soap, NULL, "ter:OperationProhibited", "argv NULL", NULL);
usernameclash:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:OperationProhibited", "ter:UsernameClash", "uname already exists", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteUsers(struct soap* soap, struct _tds__DeleteUsers *tds__DeleteUsers, struct _tds__DeleteUsersResponse *tds__DeleteUsersResponse)
{
    int count = tds__DeleteUsers->__sizeUsername;
    int i=0,j=0;
    int index[COUNT_DEL]={0};
    int del =0;
    char *name=NULL;

    FUN_IN();

    for(i=0;i<count;i++)
    {
        name = tds__DeleteUsers->Username[i];
        if ((index[i] = find_user(name, g_GkIpc_OnvifInf.User)) < 0)
        {
            goto username_missing;
        }
    }

    for(i=0;i<count;i++)
    {
        del = index[i] - i;

        free(g_GkIpc_OnvifInf.User[del]->Username);
        free(g_GkIpc_OnvifInf.User[del]->Password);
        free(g_GkIpc_OnvifInf.User[del]);
        g_GkIpc_OnvifInf.User[del] = NULL;
        for (j=del;j<g_GkIpc_OnvifInf.Usercount;j++)
        {
            g_GkIpc_OnvifInf.User[j] = g_GkIpc_OnvifInf.User[j+1];
        }
        g_GkIpc_OnvifInf.Usercount--;
    }

    FUN_OUT();

    return SOAP_OK;
username_missing:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:UsernameMissing", "uname not recognized", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetUser(struct soap* soap, struct _tds__SetUser *tds__SetUser, struct _tds__SetUserResponse *tds__SetUserResponse)
{
    const int count = tds__SetUser->__sizeUser;
    char *name=NULL;
    int index[COUNT_MODFY]={0};
    int i=0;
    int mdfy_pos=0;

    FUN_IN();
    for(i=0;i<count;i++)
    {
        name = tds__SetUser->User[i].Username;
        if ((index[i] = find_user(name, g_GkIpc_OnvifInf.User)) < 0)
        {
            goto username_missing;
        }
    }

    for(i=0;i<count;i++)
    {
       mdfy_pos = index[i];
       strcpy(g_GkIpc_OnvifInf.User[mdfy_pos]->Password, tds__SetUser->User[i].Password);
       g_GkIpc_OnvifInf.User[mdfy_pos]->UserLevel = tds__SetUser->User[i].UserLevel;

       /*-----------------------------------------------------------------------------
        *  Extension __anyAttribute not set
        *-----------------------------------------------------------------------------*/
    }

    FUN_OUT();

    return SOAP_OK;

username_missing:
    return soap_sender_2fault_subcode(soap, "ter:InvalidArgVal", "ter:UsernameMissing", "uname not recognized", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetWsdlUrl(struct soap* soap, struct _tds__GetWsdlUrl *tds__GetWsdlUrl, struct _tds__GetWsdlUrlResponse *tds__GetWsdlUrlResponse)
{
    FUN_IN();

    if (NULL == tds__GetWsdlUrlResponse)
    {
        PRINT_ERR();
        goto err;
    }

    /*-----------------------------------------------------------------------------
     *  请求端口�?<GetWsdlUrl xmlns="http://www.onvif.org/ver10/device/wsdl" />
     *  赋值http://www.onvif.org/ver10/media/wsdl 可以�?http://www.baidu.com不能�?
     *  查明是以wsdl为关键字进行判别
     *-----------------------------------------------------------------------------*/
    tds__GetWsdlUrlResponse->WsdlUrl = (char *)soap_malloc(soap, LARGE_INFO_LENGTH * sizeof(char));
    strcpy(tds__GetWsdlUrlResponse->WsdlUrl, URL_WSDL);

    FUN_OUT();

    return SOAP_OK;

err:
    ONVIF_PROCESS_ERROR(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCapabilities(struct soap* soap, struct _tds__GetCapabilities *tds__GetCapabilities, struct _tds__GetCapabilitiesResponse *tds__GetCapabilitiesResponse)
{
    int _Category;
    char _IPv4Address[LARGE_INFO_LENGTH];
    int isAll=false;
    struct sockaddr addr;

    FUN_IN();

    if(tds__GetCapabilities->Category == NULL)
    {
        printf("Sean ===> %s(): NULL\n", __func__);
        tds__GetCapabilities->Category=(enum tt__CapabilityCategory *)soap_malloc(soap, sizeof(enum tt__CapabilityCategory));
        /* :BUG:Wednesday, June 18, 2014 06:31:45 HKT:SeanHou:  */
#if 1
        *tds__GetCapabilities->Category = tt__CapabilityCategory__All;
        _Category = tt__CapabilityCategory__All;
#endif
        /* :TODO:End---  */
    }
    else
    {
        _Category = *tds__GetCapabilities->Category;
        printf("Sean: _Category [%d]__sizeCategory[%d]\n", _Category, tds__GetCapabilities->__sizeCategory);
    }

    gNetworkAdapterConfiguration.get_ip(ETHERNET_ADAPT, &addr);
    sprintf(_IPv4Address, "http://%s:%d/onvif/services",inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr),ONVIF_REQ_LISTEN_PORT);

    /*-----------------------------------------------------------------------------
     *  Capabilities
     *-----------------------------------------------------------------------------*/
    tds__GetCapabilitiesResponse->Capabilities = (struct tt__Capabilities*)soap_malloc(soap, sizeof(struct tt__Capabilities));
    soap_default_tt__Capabilities(soap, tds__GetCapabilitiesResponse->Capabilities);



    switch(*tds__GetCapabilities->Category)
    {
        case tt__CapabilityCategory__All:
            /*-----------------------------------------------------------------------------
             *  All
             *-----------------------------------------------------------------------------*/
            isAll = true;
        case tt__CapabilityCategory__Analytics:

            if(!isAll)break;
        case tt__CapabilityCategory__Device:
            /*-----------------------------------------------------------------------------
             *  Device
             *-----------------------------------------------------------------------------*/
            /*基础设置，很必须*/
            tds__GetCapabilitiesResponse->Capabilities->Device = (struct tt__DeviceCapabilities*)soap_malloc(soap, sizeof(struct tt__DeviceCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Device->XAddr = (char *) soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
            strcpy(tds__GetCapabilitiesResponse->Capabilities->Device->XAddr, _IPv4Address);
            tds__GetCapabilitiesResponse->Capabilities->Device->Extension = NULL;

            /*必要部分*/
            tds__GetCapabilitiesResponse->Capabilities->Device->Network = (struct tt__NetworkCapabilities*)soap_malloc(soap, sizeof(struct tt__NetworkCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6 = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));

            *tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPFilter = xsd__boolean__false_;
            *tds__GetCapabilitiesResponse->Capabilities->Device->Network->ZeroConfiguration = xsd__boolean__false_;
            *tds__GetCapabilitiesResponse->Capabilities->Device->Network->IPVersion6 = xsd__boolean__false_;
            *tds__GetCapabilitiesResponse->Capabilities->Device->Network->DynDNS = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension = (struct tt__NetworkCapabilitiesExtension*)soap_malloc(soap, sizeof(struct tt__NetworkCapabilitiesExtension));
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Dot11Configuration = (enum xsd__boolean *)soap_malloc(soap, sizeof(enum xsd__boolean));
            *tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Dot11Configuration = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->Extension = NULL;
            /*goke  MUST BE*/
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->__size= 0;
            tds__GetCapabilitiesResponse->Capabilities->Device->Network->Extension->__any = NULL;

            tds__GetCapabilitiesResponse->Capabilities->Device->System = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security = NULL;

#if 1
            tds__GetCapabilitiesResponse->Capabilities->Device->System = (struct tt__SystemCapabilities*)soap_malloc(soap, sizeof(struct tt__SystemCapabilities));
            soap_default_tt__SystemCapabilities(soap, tds__GetCapabilitiesResponse->Capabilities->Device->System);

            tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryResolve = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->DiscoveryBye = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->RemoteDiscovery = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemBackup = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->SystemLogging = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->FirmwareUpgrade = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->__sizeSupportedVersions = 1;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions = (struct tt__OnvifVersion*)soap_malloc(soap, sizeof(struct tt__OnvifVersion));
            tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Major = 0;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->SupportedVersions->Minor = 3;

            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension = (struct tt__SystemCapabilitiesExtension*)soap_malloc(soap, sizeof(struct tt__SystemCapabilitiesExtension));
            /* :TODO:2014/6/23 16:55:43:Sean:  ploto:没有用但是没有设置为NULL会导�?挂掉*/
#if 1
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemBackup = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemBackup = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpFirmwareUpgrade = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpFirmwareUpgrade = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemLogging = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSystemLogging = xsd__boolean__true_;
#endif
            /* :TODO:End---  */
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSupportInformation = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->HttpSupportInformation = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->Extension = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->__size = 0;
            tds__GetCapabilitiesResponse->Capabilities->Device->System->Extension->__any = NULL;
            /* :TODO:2014/6/23 16:58:06:Sean:  */
#if 1
            tds__GetCapabilitiesResponse->Capabilities->Device->IO = (struct tt__IOCapabilities*)soap_malloc(soap, sizeof(struct tt__IOCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors = (int *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->IO->InputConnectors = 0;
			tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs = (int *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Device->IO->RelayOutputs = 0;
#endif
            /* :TODO:End---  */
            /* :TODO:2014/6/23 16:58:59:Sean:  */
#if 1
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension = (struct tt__IOCapabilitiesExtension *)soap_malloc(soap, sizeof(struct tt__IOCapabilitiesExtension));
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__size =0;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__any = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Auxiliary = (enum xsd__boolean *)soap_malloc(soap, sizeof(enum xsd__boolean));
            *tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Auxiliary = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__anyAttribute = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->__sizeAuxiliaryCommands = 0;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->AuxiliaryCommands= NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->IO->Extension->Extension = NULL;
#endif
            /* :TODO:End---  */
#endif
#if 1
            tds__GetCapabilitiesResponse->Capabilities->Device->Security = (struct tt__SecurityCapabilities*)soap_malloc(soap, sizeof(struct tt__SecurityCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e1 = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->TLS1_x002e2 = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->OnboardKeyGeneration = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->AccessPolicyConfig = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->X_x002e509Token = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->SAMLToken = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->KerberosToken = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->RELToken = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->Extension = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->__size = 0;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->__any = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->Security->__anyAttribute = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Device->Extension = NULL;
#endif

            if(!isAll)break;

        case tt__CapabilityCategory__Events:

            /*-----------------------------------------------------------------------------
             *  Events
             *-----------------------------------------------------------------------------*/
            tds__GetCapabilitiesResponse->Capabilities->Events = (struct tt__EventCapabilities *)soap_malloc(soap, sizeof(struct tt__EventCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Events->XAddr = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
            char _IPAddr[INFO_LENGTH] = {0};
            unsigned int localIp = 0;
            netGetIp(ETHERNET_ADAPT, &localIp); //eth0 根据实际情况填充
            sprintf(_IPAddr, "http://%s:%d/onvif/device_service", inet_ntoa(*((struct in_addr *)&localIp)),ONVIF_REQ_LISTEN_PORT);
            strcpy(tds__GetCapabilitiesResponse->Capabilities->Events->XAddr, _IPAddr);
            tds__GetCapabilitiesResponse->Capabilities->Events->WSSubscriptionPolicySupport = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Events->WSPullPointSupport = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Events->WSPausableSubscriptionManagerInterfaceSupport = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Events->__size = 0;
            tds__GetCapabilitiesResponse->Capabilities->Events->__any = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Events->__anyAttribute = NULL;

            if(!isAll)break;

        case tt__CapabilityCategory__Imaging:
            /*-----------------------------------------------------------------------------
             *  Imaging
             *-----------------------------------------------------------------------------*/
            tds__GetCapabilitiesResponse->Capabilities->Imaging = (struct tt__ImagingCapabilities *)soap_malloc(soap, sizeof(struct tt__ImagingCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
            //char _IPAddr[INFO_LENGTH] = {0};
            //unsigned int localIp = 0;
            netGetIp(ETHERNET_ADAPT, &localIp); //eth0 根据实际情况填充
            sprintf(_IPAddr, "http://%s:%d/onvif/device_service", inet_ntoa(*((struct in_addr *)&localIp)),ONVIF_REQ_LISTEN_PORT);
            strcpy(tds__GetCapabilitiesResponse->Capabilities->Imaging->XAddr, _IPAddr);
            tds__GetCapabilitiesResponse->Capabilities->Imaging->__anyAttribute = NULL;

            if(!isAll)break;

        case tt__CapabilityCategory__Media:
            /*-----------------------------------------------------------------------------
             *  Media 	//想要对接RTSP视频，必须设置Media
             *-----------------------------------------------------------------------------*/
            tds__GetCapabilitiesResponse->Capabilities->Media = (struct tt__MediaCapabilities*)soap_malloc(soap, sizeof(struct tt__MediaCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Media->XAddr = (char *) soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
            strcpy(tds__GetCapabilitiesResponse->Capabilities->Media->XAddr, _IPv4Address);
            tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities = (struct tt__RealTimeStreamingCapabilities*)soap_malloc(soap, sizeof(struct tt__RealTimeStreamingCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTPMulticast = xsd__boolean__false_;
            tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORETCP = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = (enum xsd__boolean *)soap_malloc(soap, sizeof(int));
            *tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->RTP_USCORERTSP_USCORETCP = xsd__boolean__true_;
            tds__GetCapabilitiesResponse->Capabilities->Media->StreamingCapabilities->Extension = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Media->Extension = NULL;
            tds__GetCapabilitiesResponse->Capabilities->Media->__size = 0;
            tds__GetCapabilitiesResponse->Capabilities->Media->__any = 0;

            if(!isAll)break;

        case tt__CapabilityCategory__PTZ:
            /*-----------------------------------------------------------------------------
             * PTZ
             *-----------------------------------------------------------------------------*/
            tds__GetCapabilitiesResponse->Capabilities->PTZ= (struct tt__PTZCapabilities*)soap_malloc(soap, sizeof(struct tt__PTZCapabilities));
            tds__GetCapabilitiesResponse->Capabilities->PTZ->XAddr = (char *) soap_malloc(soap, sizeof(char) * LARGE_INFO_LENGTH);
            strcpy(tds__GetCapabilitiesResponse->Capabilities->PTZ->XAddr, _IPv4Address);
            tds__GetCapabilitiesResponse->Capabilities->PTZ->__size = 0;
            tds__GetCapabilitiesResponse->Capabilities->PTZ->__any = NULL;
            tds__GetCapabilitiesResponse->Capabilities->PTZ->__anyAttribute = NULL;
            if(!isAll)break;
    }
 /* :TODO:2014/7/25 17:14:20:Sean: 不清楚其功能暂时屏蔽 */
#if 0
    /*-----------------------------------------------------------------------------
     *  Extension
     *-----------------------------------------------------------------------------*/
    tds__GetCapabilitiesResponse->Capabilities->Extension = (struct tt__CapabilitiesExtension*)soap_malloc(soap, sizeof(struct tt__CapabilitiesExtension));
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO = (struct tt__DeviceIOCapabilities*)soap_malloc(soap, sizeof(struct tt__DeviceIOCapabilities));
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->XAddr = (char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
    strcpy(tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->XAddr,_IPv4Address);

    //下面的重要，这里只实现视频流，需要设置VideoSources
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->VideoSources = xsd__boolean__true_;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->VideoOutputs = xsd__boolean__false_;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->AudioSources = xsd__boolean__false_;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->AudioOutputs = xsd__boolean__false_;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->RelayOutputs = xsd__boolean__false_;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->__size = 0;
    tds__GetCapabilitiesResponse->Capabilities->Extension->DeviceIO->__any = NULL;

    tds__GetCapabilitiesResponse->Capabilities->Extension->Display = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->Recording = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->Search = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->Replay = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->Receiver = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->AnalyticsDevice = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->Extensions = NULL;
    tds__GetCapabilitiesResponse->Capabilities->Extension->__size = 0;
    tds__GetCapabilitiesResponse->Capabilities->Extension->__any = NULL;
#endif
 /* :TODO:End---  */

    FUN_OUT();

    return SOAP_OK;

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetHostname(struct soap* soap, struct _tds__GetHostname *tds__GetHostname, struct _tds__GetHostnameResponse *tds__GetHostnameResponse)
{
    FILE *fp = NULL;
    char buffer[LEN_HOSTNAME];

    FUN_IN();
#if 0
    if (tds__GetHostname != NULL)
    {
        printf("Sean: tds__GetHostname == 0x%xover\n", tds__GetHostname);
        //        puts((char *)tds__GetHostname);
    }
    if (NULL == tds__GetHostnameResponse->HostnameInformation)
    {
        printf("Sean : HostnameInformation NULL\n");
    }
#endif
    tds__GetHostnameResponse->HostnameInformation = (struct tt__HostnameInformation *)soap_malloc(soap, sizeof(struct tt__HostnameInformation));
    tds__GetHostnameResponse->HostnameInformation->FromDHCP =  xsd__boolean__false_;

    /*-----------------------------------------------------------------------------
     *  GetHostname OK,Ambarella is core,其他的则是错误�?客户端是用的什么协议去验证
     *  ping hostname??? 只检查字符的有效性�?
     *-----------------------------------------------------------------------------*/
    //    char str[30];
    //    char *p = str;
    //    strcpy(str, "Ambarella");
    //    tds__GetHostnameResponse->HostnameInformation->Name = "Ambarella";//NULL;
    tds__GetHostnameResponse->HostnameInformation->Name = soap_malloc(soap, LEN_HOSTNAME *sizeof(char));
    if (NULL == (fp = popen("cat /etc/hostname", "r")))
    {
        PRINT_ERR();
        goto err;
    }

    if (NULL == fgets(buffer, LEN_HOSTNAME, fp))
    {
        PRINT_ERR();
        goto err;
    }
    else
    {
        buffer[strlen(buffer) - 1 ] = '\0';

        /*-----------------------------------------------------------------------------
         *  检�?buffer是否含有 '_' ' ' [0-9]非法hostname字符
         *-----------------------------------------------------------------------------*/
        strcpy(tds__GetHostnameResponse->HostnameInformation->Name, buffer);
    }
    if (-1 == pclose(fp))
    {
        goto err;
    }
    tds__GetHostnameResponse->HostnameInformation->Extension =  NULL;
    tds__GetHostnameResponse->HostnameInformation->__anyAttribute =  NULL;


    FUN_OUT();
    return SOAP_OK;
err:
    ONVIF_PROCESS_ERROR(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostname(struct soap* soap, struct _tds__SetHostname *tds__SetHostname, struct _tds__SetHostnameResponse *tds__SetHostnameResponse)
{

    FILE *fp = NULL;
    char cmd[LEN_HOSTNAME];
    char result[LEN_ERR_INFO];

    FUN_IN();

    if (NULL == tds__SetHostname)
    {
        PRINT_ERR();
        goto err;
    }
    /*-----------------------------------------------------------------------------
     *  检�?buffer是否含有 '_' ' ' [0-9]等非法onvif hostname字符
     *-----------------------------------------------------------------------------*/
    char *p = tds__SetHostname->Name;

    while(*p)
    {
        if ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z'))
        {
            p++;
            continue;
        }
        else
        {
            goto invalid_arg;
        }
    }

    if (0 == sprintf(cmd, "echo \"%s\" > /etc/hostname && hostname \"%s\"", tds__SetHostname->Name, tds__SetHostname->Name))
    {
        PRINT_ERR();
        goto err;
    }

    printf("cmd [%s]\n", cmd);

    if (NULL == (fp = popen(cmd, "r")))
    {
        PRINT_ERR();
        goto err;
    }

    if (NULL != fgets(result, LEN_HOSTNAME, fp))
    {
        PRINT_ERR("%s\n", result);
        goto err;
    }

    if (-1 == pclose(fp))
    {
        goto err;
    }
    FUN_OUT();
    return SOAP_OK;

err:
    ONVIF_PROCESS_ERROR(soap, NULL);
invalid_arg:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidHostname", "The requested hostname cannot be accepted by the device", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostnameFromDHCP(struct soap* soap, struct _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, struct _tds__SetHostnameFromDHCPResponse *tds__SetHostnameFromDHCPResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDNS(struct soap* soap, struct _tds__GetDNS *tds__GetDNS, struct _tds__GetDNSResponse *tds__GetDNSResponse)
{
#if 0
    FILE *fp = NULL;
    char buffer[LEN_DNS];
    /*-----------------------------------------------------------------------------
     *  nameserver �?search  可能会有多个
     *-----------------------------------------------------------------------------*/
    char cmd[LEN_CMD];
    const char *dns_key[]={"nameserver", "search", NULL};
#endif
    int i=0;

    char **search=NULL;
    char **nameserver=NULL;
    char *domain=NULL;
    int __sizeSearchDomain=0;
    int __sizeDNSManual=0;

    FUN_IN();

    gNetworkAdapterConfiguration.get_dns(&search, &nameserver, &domain, &__sizeSearchDomain, &__sizeDNSManual);
    tds__GetDNSResponse->DNSInformation = (struct tt__DNSInformation* )soap_malloc(soap, sizeof(struct tt__DNSInformation));

    soap_default_tt__DNSInformation(soap, tds__GetDNSResponse->DNSInformation);
    tds__GetDNSResponse->DNSInformation->FromDHCP = g_GkIpc_OnvifInf.DHCP;

    /*-----------------------------------------------------------------------------
     *  search
     *-----------------------------------------------------------------------------*/
    tds__GetDNSResponse->DNSInformation->__sizeSearchDomain = __sizeSearchDomain;
    tds__GetDNSResponse->DNSInformation->SearchDomain = (char **)soap_malloc(soap, (__sizeSearchDomain+1) * sizeof(char *));
    while (i<__sizeSearchDomain)
    {
       tds__GetDNSResponse->DNSInformation->SearchDomain[i] = (char *)soap_malloc(soap, MIN_PROF_TOKEN * sizeof(char));
       strcpy(tds__GetDNSResponse->DNSInformation->SearchDomain[i], search[i]);
       free(search[i]);
       i++;
    }
    tds__GetDNSResponse->DNSInformation->SearchDomain[i] = NULL;
    if (__sizeSearchDomain)
    {
        free(search);
    }
    /*-----------------------------------------------------------------------------
     *  nameserve
     *-----------------------------------------------------------------------------*/
    i = 0;
    tds__GetDNSResponse->DNSInformation->__sizeDNSManual = __sizeDNSManual;
    tds__GetDNSResponse->DNSInformation->DNSManual = (struct tt__IPAddress *)soap_malloc(soap, (__sizeDNSManual) * sizeof(struct tt__IPAddress));
    while (i<__sizeDNSManual)
    {
       soap_default_tt__IPAddress(soap, &tds__GetDNSResponse->DNSInformation->DNSManual[i]);
       tds__GetDNSResponse->DNSInformation->DNSManual[i].IPv4Address = (char *)soap_malloc(soap, MIN_PROF_TOKEN * sizeof(char));
       strcpy(tds__GetDNSResponse->DNSInformation->DNSManual[i].IPv4Address, nameserver[i]);
       free(nameserver[i]);
       i++;
    }
    if (__sizeDNSManual)
        free(nameserver);
    if (domain)
        free(domain);

    FUN_OUT();

    return SOAP_OK;
#if 0
err:
    ONVIF_PROCESS_ERROR(soap, NULL);
#endif
}


SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDNS(struct soap* soap, struct _tds__SetDNS *tds__SetDNS, struct _tds__SetDNSResponse *tds__SetDNSResponse)
{
    int size_ns=0;
    int size_sch=0;
    int i=0;
    char *nameserver[10];

    FUN_IN("dhcp[%d],size_ns[%d],size_sch[%d]\n", tds__SetDNS->FromDHCP, tds__SetDNS->__sizeDNSManual, tds__SetDNS->__sizeSearchDomain);

    /*-----------------------------------------------------------------------------
     *  check ip format
     *-----------------------------------------------------------------------------*/
    if (tds__SetDNS->__sizeDNSManual)
    {
        while (i<tds__SetDNS->__sizeDNSManual)
        {
            if (tds__SetDNS->DNSManual[i].Type == tt__IPType__IPv4)
            {
                if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetDNS->DNSManual[i].IPv4Address, IPV4))
                {
                    goto inval_ipv4;
                }
            }
            else
            {
                if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetDNS->DNSManual[i].IPv4Address, IPV6))
                {
                    goto inval_ipv6;
                }
            }
            i++;
        }
    }
    g_GkIpc_OnvifInf.DHCP = tds__SetDNS->FromDHCP;/*mark Sean Hou */

    /*-----------------------------------------------------------------------------
     *  Set DNS  nameserver SearchDomain
     *-----------------------------------------------------------------------------*/
    if (xsd__boolean__false_ == tds__SetDNS->FromDHCP)
    {
        /*-----------------------------------------------------------------------------
         *  DNS Manual
         *-----------------------------------------------------------------------------*/
        size_ns = tds__SetDNS->__sizeDNSManual;
        size_sch = tds__SetDNS->__sizeSearchDomain;

        i=0;
        while(i<size_ns)
        {
           if (tds__SetDNS->DNSManual[i].Type != tt__IPType__IPv4)
           {
               nameserver[i] = tds__SetDNS->DNSManual[i].IPv6Address;
           }
           else
           {
               nameserver[i] = tds__SetDNS->DNSManual[i].IPv4Address;
           }
               i++;
        }
        gNetworkAdapterConfiguration.set_dns(tds__SetDNS->SearchDomain, nameserver, NULL, size_sch, size_ns);
    }

    FUN_OUT();

    return SOAP_OK;
inval_ipv4:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv4Address", "The suggested IPV4 address is invalid", NULL);
inval_ipv6:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv6Address", "The suggested IPV6 address is invalid", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNTP(struct soap* soap, struct _tds__GetNTP *tds__GetNTP, struct _tds__GetNTPResponse *tds__GetNTPResponse)
{
    int size=0;
    int i=0;

    FUN_IN();

    tds__GetNTPResponse->NTPInformation = (struct tt__NTPInformation *)soap_malloc(soap, sizeof(struct tt__NTPInformation));
    soap_default_tt__NTPInformation(soap, tds__GetNTPResponse->NTPInformation);
    tds__GetNTPResponse->NTPInformation->__sizeNTPManual = 1;
    size = tds__GetNTPResponse->NTPInformation->__sizeNTPManual;
    tds__GetNTPResponse->NTPInformation->NTPManual = (struct tt__NetworkHost *)soap_malloc(soap, size * sizeof(struct tt__NetworkHost));
    while (i<size)
    {
        soap_default_tt__NetworkHost(soap, &tds__GetNTPResponse->NTPInformation->NTPManual[i]);
        tds__GetNTPResponse->NTPInformation->NTPManual[i].Type = tt__NetworkHostType__IPv4;
        tds__GetNTPResponse->NTPInformation->NTPManual[i].IPv4Address = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        strcpy(tds__GetNTPResponse->NTPInformation->NTPManual[i].IPv4Address, NTP_SERVER);
        i++;
    }

    FUN_OUT();

    return SOAP_OK;
//    ONVIF_NOTSUPPORTED_FUNC(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNTP(struct soap* soap, struct _tds__SetNTP *tds__SetNTP, struct _tds__SetNTPResponse *tds__SetNTPResponse)
{
    int size = 0;
    int i=0;

    FUN_IN();

    /*-----------------------------------------------------------------------------
     *  check ip format.
     *-----------------------------------------------------------------------------*/
    size = tds__SetNTP->__sizeNTPManual;
    while (i<size)
    {
        if (tt__NetworkHostType__IPv4 == tds__SetNTP->NTPManual[i].Type)
        {
            if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNTP->NTPManual[i].IPv4Address, IPV4))
            {
                goto inval_ipv4;
            } 
        }
        else if (tt__NetworkHostType__IPv6 == tds__SetNTP->NTPManual[i].Type)
        {
            if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNTP->NTPManual[i].IPv6Address, IPV6))
            {
                goto inval_ipv6;
            } 
        }
        else
        {
           PRINT_DBG("dont know how to process NTP DNS!\n"); 
        }
            i++;
    }


    FUN_OUT();

    return SOAP_OK;    

inval_ipv4:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv4Address", "The suggested IPV4 address is invalid", NULL);
inval_ipv6:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv6Address", "The suggested IPV6 address is invalid", NULL);    
}
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkInterfaces(struct soap* soap, struct _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, struct _tds__GetNetworkInterfacesResponse *tds__GetNetworkInterfacesResponse)
{
    unsigned char macaddr[6] = {0};
    char *name[ADAPTERNUM_MAX+1]={0};
    int i=0;
    int count_adapter=0;
    struct sockaddr addr;

    FUN_IN();

    /* :TODO:2014/7/23 14:15:03:Sean:  segment error*/
#if 0
    printf("===>line[%d]:\n", __LINE__);
    soap->header->wsa__To = "http://schemas.xmlsoap.org/ws/2004/08/addressing/role/anonymous";
    printf("===>line[%d]:\n", __LINE__);
    soap->header->wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/ProbeMatches";
    soap->header->wsa__RelatesTo = (struct wsa__Relationship*)soap_malloc(soap, sizeof(struct wsa__Relationship));
    soap_default_wsa__Relationship(soap, soap->header->wsa__RelatesTo);
    soap->header->wsa__RelatesTo->__item = soap->header->wsa__MessageID;
    soap->header->wsa__MessageID =(char *)soap_malloc(soap, sizeof(char) * INFO_LENGTH);
#endif
//    strcpy(soap->header->wsa__MessageID,_HwId+4);
 /* :TODO:End---  */
    soap_default__tds__GetNetworkInterfacesResponse(soap, tds__GetNetworkInterfacesResponse);
    /*-----------------------------------------------------------------------------
     *  GetNetworkInterfacesResponse
     *-----------------------------------------------------------------------------*/
    gNetworkAdapterConfiguration.get_name(name, &count_adapter);
    tds__GetNetworkInterfacesResponse->__sizeNetworkInterfaces = count_adapter-1;

    tds__GetNetworkInterfacesResponse->NetworkInterfaces = (struct tt__NetworkInterface *)soap_malloc(soap, tds__GetNetworkInterfacesResponse->__sizeNetworkInterfaces * sizeof(struct tt__NetworkInterface));
    soap_default_tt__NetworkInterface(soap, tds__GetNetworkInterfacesResponse->NetworkInterfaces);

    /*-----------------------------------------------------------------------------
     *  remove "lo"
     *-----------------------------------------------------------------------------*/
    i = 0;
    do{
        if(0 == strcmp(name[i], "lo"))
        {
            free(name[i]);
            name[i] = NULL;
            i++;
            while(name[i]!=NULL)
            {
                name[i-1] = name[i];
                i++;
            }
            name[i-1] = NULL;
            break;
        }
    }while(name[i]!=NULL);
    i=0;

    while(name[i]!=NULL)
    {
        PRINT_DBG("%s\n", name[i]);
        i++;
    }

    i=0;
    while(name[i]!=NULL)
    {
        PRINT_DBG("adapter name[%s]\n", name[i]);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].token = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        strcpy(tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].token, name[i]);

        /*-----------------------------------------------------------------------------
         *  NetworkInterfaceInfo
         *-----------------------------------------------------------------------------*/

        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info = (struct tt__NetworkInterfaceInfo *)soap_malloc(soap, sizeof(struct tt__NetworkInterfaceInfo));
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->Name = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        strcpy(tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->Name, name[i]);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->HwAddress = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        gNetworkAdapterConfiguration.get_hwaddr(name[i], macaddr);
        sprintf(tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->HwAddress, "%02X%02X%02X%02X%02X%02X", macaddr[0], macaddr[1], macaddr[2], macaddr[3], macaddr[4], macaddr[5]);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->MTU = (int *)soap_malloc(soap, sizeof(int));
        gNetworkAdapterConfiguration.get_mtu(name[i], tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Info->MTU);

        /*-----------------------------------------------------------------------------
         *  NetworkInterfaceLink
         *-----------------------------------------------------------------------------*/
#if 1
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link = (struct tt__NetworkInterfaceLink *)soap_malloc(soap, sizeof(struct tt__NetworkInterfaceLink));
        soap_default_tt__NetworkInterfaceLink(soap, tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->AdminSettings = (struct tt__NetworkInterfaceConnectionSetting *)soap_malloc(soap, sizeof(struct tt__NetworkInterfaceConnectionSetting));
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->AdminSettings->AutoNegotiation = xsd__boolean__true_;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->AdminSettings->Speed = SPEED_ETH;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->AdminSettings->Duplex = tt__Duplex__Full;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->OperSettings = (struct tt__NetworkInterfaceConnectionSetting *)soap_malloc(soap, sizeof(struct tt__NetworkInterfaceConnectionSetting));
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->OperSettings->AutoNegotiation = xsd__boolean__true_;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->OperSettings->Speed = SPEED_ETH;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->OperSettings->Duplex = tt__Duplex__Full;

        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Link->InterfaceType = ETHERNET;
#endif
        /*-----------------------------------------------------------------------------
         *  IPv4NetworkInterface
         *-----------------------------------------------------------------------------*/
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4 = (struct tt__IPv4NetworkInterface *)soap_malloc(soap, sizeof(struct tt__IPv4NetworkInterface));
        soap_default_tt__IPv4NetworkInterface(soap, tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Enabled = xsd__boolean__true_;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config = (struct tt__IPv4Configuration *)soap_malloc(soap, sizeof(struct tt__IPv4Configuration));
        soap_default_tt__IPv4Configuration(soap, tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config);
#if 1
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->__sizeManual = 1;
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->Manual = (struct tt__PrefixedIPv4Address *)soap_malloc(soap, sizeof(struct tt__PrefixedIPv4Address));
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->Manual->Address = (char *)soap_malloc(soap, MAX_PROF_TOKEN);


        gNetworkAdapterConfiguration.get_ip(name[i], &addr);
        strcpy(tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->Manual->Address, inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr));
        gNetworkAdapterConfiguration.get_netmask(name[i], &addr);
        
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->Manual->PrefixLength = gNetworkAdapterConfiguration.covprefixlen(&addr);
#endif
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->LinkLocal = (struct tt__PrefixedIPv4Address *)soap_malloc(soap, sizeof(struct tt__PrefixedIPv4Address));
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->LinkLocal->Address = (char *)soap_malloc(soap, MAX_PROF_TOKEN);
        gNetworkAdapterConfiguration.get_ip(name[i], &addr);
        strcpy(tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->LinkLocal->Address, inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr));
        gNetworkAdapterConfiguration.get_netmask(name[i], &addr);
        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].IPv4->Config->LinkLocal->PrefixLength = gNetworkAdapterConfiguration.covprefixlen(&addr);/*netmask */

        tds__GetNetworkInterfacesResponse->NetworkInterfaces[i].Enabled = xsd__boolean__true_;/*Sean Hou: 实时检查网卡然后赋�?*/

        /*-----------------------------------------------------------------------------
         *  IPv6NetworkInterface
         *-----------------------------------------------------------------------------*/

        /*-----------------------------------------------------------------------------
         * NetworkInterfaceExtension
         *-----------------------------------------------------------------------------*/

        /*-----------------------------------------------------------------------------
         *  __anyAttribute
         *-----------------------------------------------------------------------------*/

        PRINT_DBG("--->line[%d]:\n", __LINE__);
        free(name[i]);

        i++;
    }

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkInterfaces(struct soap* soap, struct _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, struct _tds__SetNetworkInterfacesResponse *tds__SetNetworkInterfacesResponse)
{
    struct sockaddr_in addr;
    int i=0;

    FUN_IN();

    if (0 != strcmp(ETHERNET_ADAPT, tds__SetNetworkInterfaces->InterfaceToken))
    {
        goto inval_interface;
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->Enabled)
    {
        if (xsd__boolean__false_ == *tds__SetNetworkInterfaces->NetworkInterface->Enabled)
        {
           g_GkIpc_OnvifInf.NIC_alive = false;
        }
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->MTU)
    {
        gNetworkAdapterConfiguration.set_mtu(ETHERNET_ADAPT, *(tds__SetNetworkInterfaces->NetworkInterface->MTU));
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->Link)
    {
        ;
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->IPv4)
    {
        if ((!tds__SetNetworkInterfaces->NetworkInterface->IPv4->DHCP) || (xsd__boolean__false_ == *tds__SetNetworkInterfaces->NetworkInterface->IPv4->DHCP))
        {
            if (tds__SetNetworkInterfaces->NetworkInterface->IPv4->Manual)
            {
                /*-----------------------------------------------------------------------------
                 *  检查是否符合格�
                 *-----------------------------------------------------------------------------*/
                if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNetworkInterfaces->NetworkInterface->IPv4->Manual->Address, IPV4))
                {
                    goto inval_ipv4;
                }

                memset(&addr, 0, sizeof(addr));
                addr.sin_family = AF_INET;
                addr.sin_addr.s_addr = inet_addr(tds__SetNetworkInterfaces->NetworkInterface->IPv4->Manual->Address);

                /*-----------------------------------------------------------------------------
                 *  set_ip will down ETHERNET_ADAPT. so you must set all the net config.
                 *-----------------------------------------------------------------------------*/
                struct sockaddr *addr_matrix[MAX_GATE_COUNT]={0};
                int count_gateway=0;
                if (0 != gNetworkAdapterConfiguration.get_gateway(ETHERNET_ADAPT, addr_matrix, &count_gateway))
                {
                    goto err;
                }
                if (0 != gNetworkAdapterConfiguration.get_netmask(ETHERNET_ADAPT, (struct sockaddr *)&addr))
                {
                    goto err;
                }                
//                if (0 != gNetworkAdapterConfiguration.get_broadaddr(ETHERNET_ADAPT, (struct sockaddr *)&addr))
//                {
//                    goto err;
//                }                
                if (0 != gNetworkAdapterConfiguration.set_ip(ETHERNET_ADAPT, (struct sockaddr *)&addr))
                {
                    goto err;
                }

                if (0 != gNetworkAdapterConfiguration.set_netmask(ETHERNET_ADAPT, (struct sockaddr *)&addr))
                {
                    goto err;
                }

//                 if (0 != gNetworkAdapterConfiguration.set_broadaddr(ETHERNET_ADAPT, (struct sockaddr *)&addr))
//                {
//                    goto err;
//                }               

                if (0 != gNetworkAdapterConfiguration.set_gateway(ETHERNET_ADAPT, addr_matrix, count_gateway))
                {
                    goto err;
                }
                /*free gateway temp  array*/
                for (i=0;i<count_gateway;i++)
                {
                    free(addr_matrix[i]);
                }
            }
        }
        else
        {
           g_GkIpc_OnvifInf.DHCP = *tds__SetNetworkInterfaces->NetworkInterface->IPv4->DHCP;
           gNetworkAdapterConfiguration.set_dhcp(ETHERNET_ADAPT);
        }
    }

    /*-----------------------------------------------------------------------------
     *  NOT SUPPORTED
     *-----------------------------------------------------------------------------*/
    if (tds__SetNetworkInterfaces->NetworkInterface->IPv6)
    {
        if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNetworkInterfaces->NetworkInterface->IPv4->Manual->Address, IPV6))
        {
            goto inval_ipv6;
        }
        
        ;
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->Extension)
    {
        ;
    }
    if (tds__SetNetworkInterfaces->NetworkInterface->__anyAttribute)
    {
        ;
    }

    raise(SOAP_HELLO);

    FUN_OUT();

    return SOAP_OK;
inval_interface:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidNetworkInterface", "The NetworkInterface  token does not exist", NULL);
inval_ipv4:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv4Address", "The suggested IPV4 address is invalid", NULL);
inval_ipv6:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidIPv6Address", "The suggested IPV6 address is invalid", NULL);
    
err:
    ONVIF_PROCESS_ERROR(soap, NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkProtocols(struct soap* soap, struct _tds__GetNetworkProtocols *tds__GetNetworkProtocols, struct _tds__GetNetworkProtocolsResponse *tds__GetNetworkProtocolsResponse)
{
    int i=0;
    int size =0;

    FUN_IN("size[%d]\n", g_GkIpc_OnvifInf.NetworkProtocolsInf.__sizeNetworkProtocols);

    size = g_GkIpc_OnvifInf.NetworkProtocolsInf.__sizeNetworkProtocols;
    tds__GetNetworkProtocolsResponse->__sizeNetworkProtocols = size;
    tds__GetNetworkProtocolsResponse->NetworkProtocols = (struct tt__NetworkProtocol *)soap_malloc(soap, tds__GetNetworkProtocolsResponse->__sizeNetworkProtocols * sizeof(struct tt__NetworkProtocol));
    for (i=0;i<size;i++)
    {
        tds__GetNetworkProtocolsResponse->NetworkProtocols[i].Name = g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[i].Name;
        tds__GetNetworkProtocolsResponse->NetworkProtocols[i].Enabled = g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[i].Enabled;
        tds__GetNetworkProtocolsResponse->NetworkProtocols[i].__sizePort = g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[i].__sizePort;
        tds__GetNetworkProtocolsResponse->NetworkProtocols[i].Port = (int *)soap_malloc(soap, tds__GetNetworkProtocolsResponse->NetworkProtocols[i].__sizePort * sizeof(int));
        *tds__GetNetworkProtocolsResponse->NetworkProtocols[i].Port = *g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[i].Port;
    }

    FUN_OUT();

    return SOAP_OK;
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkProtocols(struct soap* soap, struct _tds__SetNetworkProtocols *tds__SetNetworkProtocols, struct _tds__SetNetworkProtocolsResponse *tds__SetNetworkProtocolsResponse)
{
    int i=0;
    int index=0;

    FUN_IN("size[%d]\n", tds__SetNetworkProtocols->__sizeNetworkProtocols);

    while (i<tds__SetNetworkProtocols->__sizeNetworkProtocols)
    {
        index = tds__SetNetworkProtocols->NetworkProtocols[i].Name;
//        if (tt__NetworkProtocolType__HTTPS == index && (!g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].Enabled))
        if (0)
        {
            goto inval_arg;
        }
        g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].Name = tds__SetNetworkProtocols->NetworkProtocols[i].Name;
        g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].Enabled = tds__SetNetworkProtocols->NetworkProtocols[i].Enabled;
        g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].__sizePort = 1;/*dont copy from client*/
        if (tds__SetNetworkProtocols->NetworkProtocols[i].Port)
        {
            *g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].Port = *tds__SetNetworkProtocols->NetworkProtocols[i].Port;
        }
        /*-----------------------------------------------------------------------------
         *  dont copy from client
         *-----------------------------------------------------------------------------*/
        g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].Extension = NULL;
        g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[index].__anyAttribute = NULL;
        i++;
    }

    FUN_OUT();

    return SOAP_OK;

inval_arg:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:ServiceNotSupported", "The supplied network serve is not supported", NULL);

}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkDefaultGateway(struct soap* soap, struct _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, struct _tds__GetNetworkDefaultGatewayResponse *tds__GetNetworkDefaultGatewayResponse)
{
#if 0
    FILE *fp = NULL;
    char buffer[LEN_DNS];
    char cmd[LEN_CMD]={"route |grep default | awk \'{print $2}\'"};
#endif
    struct sockaddr *addr_matrix[MAX_GATE_COUNT]={0};
    int count_gateway=0;
    int i=0;

    FUN_IN();

    tds__GetNetworkDefaultGatewayResponse->NetworkGateway = (struct tt__NetworkGateway *)soap_malloc(soap, sizeof(struct tt__NetworkGateway));
    soap_default_tt__NetworkGateway(soap, tds__GetNetworkDefaultGatewayResponse->NetworkGateway);
   
    if (0 != gNetworkAdapterConfiguration.get_gateway(ETHERNET_ADAPT, addr_matrix, &count_gateway))
    {
        goto err;
    }

    tds__GetNetworkDefaultGatewayResponse->NetworkGateway->__sizeIPv4Address = count_gateway;
    tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address = (char **)soap_malloc(soap, count_gateway * sizeof(char *));
    while(i<count_gateway)
    {
        tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[i] = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        strcpy(tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[i], inet_ntoa((*((struct sockaddr_in*)addr_matrix[i])).sin_addr));
        i++;
    }
#if 0
    if (NULL == (fp = popen(cmd, "r")))
    {
        PRINT_ERR();
        goto err;
    }
    if (NULL == fgets(buffer, LEN_DNS, fp))
    {
        PRINT_ERR("gw NULL\n");
        goto err;
    }

    puts(buffer);

    char *p = buffer;
    int size = 0;
    /*Sean Hou: computer count */
    while(*p)
    {
        if ('\n' == *(p++))
        {
            size++;
        }
    }

    tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address = (char **)soap_malloc(soap, size * sizeof(char *));

    p = buffer;
    char *delimPos = NULL;
    int num=0;

    delimPos = strtok(p, " \n");
    tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[0] = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
    strcpy(tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[0], delimPos);
    while((delimPos = strtok(NULL, " \n")))
    {
        p = delimPos;
        num++;
        tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[num] = (char *)soap_malloc(soap, MAX_PROF_TOKEN * sizeof(char));
        strcpy(tds__GetNetworkDefaultGatewayResponse->NetworkGateway->IPv4Address[num], delimPos);
    }
    if (-1 == pclose(fp))
    {
        goto err;
    }
#endif
    FUN_OUT();

    return SOAP_OK;

err:
    ONVIF_PROCESS_ERROR(soap, NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkDefaultGateway(struct soap* soap, struct _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, struct _tds__SetNetworkDefaultGatewayResponse *tds__SetNetworkDefaultGatewayResponse)
{
    FILE *fp = NULL;
    char cmd[LEN_CMD];
    char buffer[INFO_LENGTH];
    int i=0;
//    int rc=0;

    FUN_IN();

    while (i<tds__SetNetworkDefaultGateway->__sizeIPv4Address)
    {
        if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNetworkDefaultGateway->IPv4Address[i], IPV4))
        {
            goto inval_ip;
        }
        i++;
    }
    i=0;
    while (i<tds__SetNetworkDefaultGateway->__sizeIPv6Address)
    {
        if (!gNetworkAdapterConfiguration.is_ipaddr(tds__SetNetworkDefaultGateway->IPv6Address[i], IPV6))
        {
            goto inval_ip;
        }
        i++;
    }

    if (0 == sprintf(cmd, "route add default gw %s %s 2>&1", tds__SetNetworkDefaultGateway->IPv4Address[0], ETHERNET_ADAPT))
    {
        PRINT_ERR();
        goto err;
    }

    if (NULL == (fp = popen(cmd, "r")))
    {
        PRINT_ERR();
        goto err;
    }
    if (NULL != fgets(buffer, sizeof(buffer), fp))
    {
        PRINT_ERR("%s\n", buffer);
        goto err;
    }
    if (-1 == pclose(fp))
    {
        goto err;
    }

    FUN_OUT();

    return SOAP_OK;

err:
    ONVIF_PROCESS_ERROR(soap, NULL);
inval_ip:
    ONVIF_SENDER_2ERROR(soap, NULL, "ter:InvalidArgVal", "ter:InvalidGatewayAddress", "The GatewayAddress  address was invalid", NULL);
}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDynamicDNS(struct soap* soap, struct _tds__GetDynamicDNS *tds__GetDynamicDNS, struct _tds__GetDynamicDNSResponse *tds__GetDynamicDNSResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDynamicDNS(struct soap* soap, struct _tds__SetDynamicDNS *tds__SetDynamicDNS, struct _tds__SetDynamicDNSResponse *tds__SetDynamicDNSResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetZeroConfiguration(struct soap* soap, struct _tds__GetZeroConfiguration *tds__GetZeroConfiguration, struct _tds__GetZeroConfigurationResponse *tds__GetZeroConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetZeroConfiguration(struct soap* soap, struct _tds__SetZeroConfiguration *tds__SetZeroConfiguration, struct _tds__SetZeroConfigurationResponse *tds__SetZeroConfigurationResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetIPAddressFilter(struct soap* soap, struct _tds__GetIPAddressFilter *tds__GetIPAddressFilter, struct _tds__GetIPAddressFilterResponse *tds__GetIPAddressFilterResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__SetIPAddressFilter(struct soap* soap, struct _tds__SetIPAddressFilter *tds__SetIPAddressFilter, struct _tds__SetIPAddressFilterResponse *tds__SetIPAddressFilterResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__AddIPAddressFilter(struct soap* soap, struct _tds__AddIPAddressFilter *tds__AddIPAddressFilter, struct _tds__AddIPAddressFilterResponse *tds__AddIPAddressFilterResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveIPAddressFilter(struct soap* soap, struct _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, struct _tds__RemoveIPAddressFilterResponse *tds__RemoveIPAddressFilterResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemLog(struct soap* soap, struct _tds__GetSystemLog *tds__GetSystemLog, struct _tds__GetSystemLogResponse *tds__GetSystemLogResponse){ONVIF_NOTSUPPORTED_FUNC(soap, NULL);}

