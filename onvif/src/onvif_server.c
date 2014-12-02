/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_server.c
**
** \version     $Id$
**
** \brief       onvif test main file
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2014 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/



//#define __ONVIF_SERVER_C__
#include "onvif_common.h"
//#undef  __ONVIF_SERVER_C__

#include "nsmap.h"/*dont modify*/

/* #####   EXPORTED VARIABLES   ##################################################### */
int preset_size;
node *head;

/* #####   EXPORTED VARIABLES   ##################################################### */
struct tt__VideoResolution Resolution[DEFAULT_VIDEOENCODE_NUM] = {
	{1280,720},
	{1280,720}
};
struct tt__VideoRateControl RateControl[DEFAULT_VIDEOENCODE_NUM] = {
	{200, 1, 4096},
	{200, 1, 2048}
};
struct tt__H264Configuration H264[DEFAULT_VIDEOENCODE_NUM] = {
    {25, tt__H264Profile__Main},
    {25, tt__H264Profile__Main}
};

struct tt__IPAddress Address[DEFAULT_VIDEOENCODE_NUM] = {
    {tt__IPType__IPv4,NULL,NULL},
    {tt__IPType__IPv4,NULL,NULL}
};

struct tt__MulticastConfiguration Multicast[DEFAULT_VIDEOENCODE_NUM] = {
    {&Address[0], 554, 1, xsd__boolean__true_, 0, NULL, NULL},
    {&Address[1], 554, 1, xsd__boolean__true_, 0, NULL, NULL}
};

struct tt__IntRectangle Bounds = {
    0,0,1920,1080
};

enum xsd__boolean fixed = xsd__boolean__true_;

/*device have  one video source input*/
struct tt__VideoSourceConfiguration gokeDefVideoSourceConfiguration[DEFAULT_VIDEOSOURCE_NUM] = {
    {"IPCamera", 2, "IPCameraToken", "IPCameraSourceToken", &Bounds,0,NULL,NULL,NULL}
};

/*device have  two video encode*/
struct tt__VideoEncoderConfiguration gokeDefVideoEncoderConfiguration[DEFAULT_VIDEOENCODE_NUM] = {
    {"Stream0",1, "Stream0Token", tt__VideoEncoding__H264,&Resolution[0], 30.0, &RateControl[0],NULL,&H264[0],&Multicast[0],720000,0,NULL,NULL},
    {"Stream1",1, "Stream1Token", tt__VideoEncoding__H264,&Resolution[1], 30.0, &RateControl[1],NULL,&H264[1],&Multicast[1],720000,0,NULL,NULL}
};


static char *VideoSourceTokens = "IPCameraToken";


struct tt__IntRange IntRange[4] = {
	{0, 0},// x range
	{0, 0},// y range
	{1920, 1920},//width range
	{1080, 1080} // height range
};

struct tt__IntRectangleRange BoundsRange = {

	&IntRange[0],&IntRange[1],&IntRange[2],&IntRange[3]

};

struct tt__VideoSourceConfigurationOptions gokeDefVideoSourceConfigurationOption[DEFAULT_VIDEOSOURCEOPTION_NUM] = {
	{ &BoundsRange, 1, &VideoSourceTokens, NULL , NULL }
};


enum tt__H264Profile H264ProfilesSupported  = tt__H264Profile__Main;
struct tt__IntRange QualityRange = {0,100};
struct tt__IntRange GovLengthRange = {1, 400};
struct tt__IntRange FrameRateRange = {100 , 500};
struct tt__IntRange EncodingIntervalRange = {1, 400};

struct tt__VideoResolution ResolutionsAvailable[1] = {
	{1280, 720},
};
struct tt__H264Options H264Options = {
	1,									//ResolutionsAvailable size
	ResolutionsAvailable,				//Resolutions
	&GovLengthRange,					//GovLength
	&FrameRateRange,					//FrameRate
	&EncodingIntervalRange,				//Encode Interval
	1,									//H264ProfilesSupported size
	&H264ProfilesSupported
};
struct tt__VideoEncoderConfigurationOptions gokeDefVideoEncodeConfigurationOption[DEFAULT_VIDEOENCODEOPTION_NUM] = {
	{ &QualityRange, NULL , NULL, &H264Options, NULL, NULL},
	{ &QualityRange, NULL , NULL, &H264Options, NULL, NULL}
};



/*device have two profile*/
static struct tt__Profile gokeDefIPCameraProfiles[DEFAULT_PROFILE_NUM] = {
    /*MainStreamProfile*/
    {
        /*name*/
        "MainStreamProfile",
        /*VideoSourceConfiguration*/
        &gokeDefVideoSourceConfiguration[0],
        /*AudioSourceConfiguration*/
        NULL,
        /*VideoEncoderConfiguration*/
        &gokeDefVideoEncoderConfiguration[0],
        /*AudioEncoderConfiguration*/
        NULL,
        /*VideoAnalyticsConfiguration*/
        NULL,
        /*PTZConfiguration*/
        NULL,
        /*MetadataConfiguration*/
        NULL,
        /*Extension*/
        NULL,
        /*token*/
        "MainStreamProfileToken",
        /*fixed*/
        &fixed,
        /*__anyAttribute*/
        NULL
    },

    /*SecondStreamProfile*/
    {
        /*name*/
        "SecondStreamProfile",
        /*VideoSourceConfiguration*/
        &gokeDefVideoSourceConfiguration[0],
        /*AudioSourceConfiguration*/
        NULL,
        /*VideoEncoderConfiguration*/
        &gokeDefVideoEncoderConfiguration[1],
        /*AudioEncoderConfiguration*/
        NULL,
        /*VideoAnalyticsConfiguration*/
        NULL,
        /*PTZConfiguration*/
        NULL,
        /*MetadataConfiguration*/
        NULL,
        /*Extension*/
        NULL,
        /*token*/
        "SecondStreamProfileToken",
        /*fixed*/
        &fixed,
        /*__anyAttribute*/
        NULL
    }
};
/*add the default profiles end*/


GkIpc_OnvifInf g_GkIpc_OnvifInf;

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */

static void* soap_request_handler(void *argPtr)
{
    struct soap ServerSoap;
    int ret;

    soap_init(&ServerSoap);
    soap_set_namespaces(&ServerSoap,  namespaces);

    if(!soap_valid_socket(soap_bind(&ServerSoap, NULL, ONVIF_REQ_LISTEN_PORT, 10)))
	{
        soap_print_fault(&ServerSoap, stderr);
        exit(1);
    }

    while (1) {

        ret = soap_accept(&ServerSoap);
        if (ret < 0) {
            soap_print_fault(&ServerSoap, stderr);
            exit(-1);
        }
        fprintf(stderr, "Socket connection successful: slave socket = %d\n", ret);
        soap_serve(&ServerSoap);
        soap_end(&ServerSoap);

        if (true == g_GkIpc_OnvifInf.is_reboot)
        {
            goto rebooot;
        }
    }

    /*-----------------------------------------------------------------------------
     *  send Bye
     *-----------------------------------------------------------------------------*/
rebooot:
    ;
#if 0
    sleep(2);
    soap_init1(&ServerSoap, SOAP_IO_UDP | SOAP_XML_IGNORENS);
    if (SOAP_OK != __wsdd__Bye(&ServerSoap, NULL))
    {
        printf("ERROR!Say Bye\n");
    }
    soap_destroy(&ServerSoap);
    soap_end(&ServerSoap);
    system("reboot");
#endif
    return NULL;
}

static void hellobye_handle(int signo)
{
    struct soap send_soap;

    soap_init1(&send_soap, SOAP_IO_UDP|SOAP_XML_IGNORENS);
    soap_set_namespaces(&send_soap,  namespaces);



    if (SOAP_HELLO == signo)
    {
        sleep(1);
        if (SOAP_OK != __wsdd__Hello(&send_soap, NULL))
        {
            printf("ERROR!Say Hello\n");
        }

    }
    else if (SOAP_BYE == signo)
    {
        sleep(1);
        if (SOAP_OK != __wsdd__Bye(&send_soap, NULL))
        {
            printf("ERROR!Say Bye\n");
        }
        if (true == g_GkIpc_OnvifInf.is_reboot)
        {
            printf("is reboot!\n");
            system("reboot");
        }


    }

    return;
}

int init_env()
{
    int i=0;
	U8 ucCnt = 0;
    const char *scope1 = "onvif://www.onvif.org/type/NetworkVideoTransmitter";
    const char *scope2 = "onvif://www.onvif.org/type/video_encoder";
    const char *scope3 = "onvif://www.onvif.org/type/ptz";
    const char *scope4 = "onvif://www.onvif.org/hardware/HD-53NV1080HSD";
    const char *scope5 = "onvif://www.onvif.org/name/HD-53NV1080HSD";
    const char *scope6 = "onvif://www.onvif.org/location/Chendu";
    const char *scope[]={scope1, scope2, scope3, scope4, scope5, scope6, NULL};
    char *temp = NULL;
    struct sockaddr addr;


    FUN_IN();
	head = Peset_List_Init();
 /* :TODO:2014/7/18 9:17:36:Sean:  便于调试暂时关闭*/
#if 0
	/*Init HAL*/
	if(MediaInitHAL() < 0){
        PRINT_DBG("Init HAL Failed!\n");
        return -1;
	}
#endif
 /* :TODO:End---  */
	memset(&g_GkIpc_OnvifInf, 0, sizeof(g_GkIpc_OnvifInf));
    g_GkIpc_OnvifInf.is_reboot = false;
    g_GkIpc_OnvifInf.discoverymode = tt__DiscoveryMode__Discoverable;
    g_GkIpc_OnvifInf.Scopes = (struct tt__Scope **)malloc((MAX_SCOPE+1) * sizeof(struct tt__Scope *));

    if (g_GkIpc_OnvifInf.Scopes == NULL)
    {
        return -1;
    }
    memset(g_GkIpc_OnvifInf.Scopes, 0, sizeof((MAX_SCOPE+1) * sizeof(struct tt__Scope *)));
    for(i=0;NULL != scope[i];i++)
    {
        g_GkIpc_OnvifInf.Scopes[i] = (struct tt__Scope *)malloc(sizeof(struct tt__Scope ));
        temp = (char *)malloc((strlen(scope[i]) + 1)* sizeof(char));
        if (NULL == temp)
        {
            return -1;
        }
        strcpy(temp, scope[i]);
        g_GkIpc_OnvifInf.Scopes[i]->ScopeItem = temp;
        g_GkIpc_OnvifInf.Scopes[i]->ScopeDef = tt__ScopeDefinition__Fixed;
    }
    g_GkIpc_OnvifInf.Scopes[i] = NULL;

    g_GkIpc_OnvifInf.XAddrs = (char *)malloc(LEN_URL * sizeof(char));
    gNetworkAdapterConfiguration.get_ip(ETHERNET_ADAPT, &addr);
//    sprintf(g_GkIpc_OnvifInf.XAddrs, "http://%s/onvif/device_service http://%s/onvif/device_serviceSean", inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr), inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr));
    sprintf(g_GkIpc_OnvifInf.XAddrs, "http://%s:%d/onvif/device_service", inet_ntoa((*(struct sockaddr_in *)&addr).sin_addr),ONVIF_REQ_LISTEN_PORT);

    /*-----------------------------------------------------------------------------
     *  Security
     *-----------------------------------------------------------------------------*/
    g_GkIpc_OnvifInf.Usercount = 1;
    g_GkIpc_OnvifInf.User = (struct tt__User **)malloc(MAX_USER * sizeof(struct tt__User *));
    memset(g_GkIpc_OnvifInf.User, 0, MAX_USER);
    g_GkIpc_OnvifInf.User[0] = (struct tt__User *)malloc(sizeof(struct tt__User));
    g_GkIpc_OnvifInf.User[0]->Username = (char *)malloc(LEN_USRNAME * sizeof(char));
    strcpy(g_GkIpc_OnvifInf.User[0]->Username, "admin");
    g_GkIpc_OnvifInf.User[0]->Password = (char *)malloc(LEN_PASSWD * sizeof(char));
    strcpy(g_GkIpc_OnvifInf.User[0]->Password, "admin");
    g_GkIpc_OnvifInf.User[0]->UserLevel = tt__UserLevel__Administrator;
    g_GkIpc_OnvifInf.User[0]->Extension = NULL;
    g_GkIpc_OnvifInf.User[0]->__anyAttribute = NULL;

    /*-----------------------------------------------------------------------------
     *  DateTime
     *-----------------------------------------------------------------------------*/
    g_GkIpc_OnvifInf.DateTimeType = tt__SetDateTimeType__Manual;
    g_GkIpc_OnvifInf.DaylightSavings = xsd__boolean__false_;
    g_GkIpc_OnvifInf.time_zone = TIME_ZONE_NUM;

    /*-----------------------------------------------------------------------------
     *  network
     *-----------------------------------------------------------------------------*/
    g_GkIpc_OnvifInf.DHCP = xsd__boolean__false_;
    g_GkIpc_OnvifInf.NIC_alive = true;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.__sizeNetworkProtocols = 3;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols = (struct tt__NetworkProtocol *)malloc(g_GkIpc_OnvifInf.NetworkProtocolsInf.__sizeNetworkProtocols * sizeof(struct tt__NetworkProtocol));
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].Name = tt__NetworkProtocolType__HTTP;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].Enabled = xsd__boolean__true_;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].__sizePort = 1;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].Port = (int *)malloc(g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].__sizePort * sizeof(int));
    *g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].Port = ONVIF_HTTP_PORT;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].Extension = NULL;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTP].__anyAttribute = NULL;

    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].Name = tt__NetworkProtocolType__HTTPS;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].Enabled = xsd__boolean__false_;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].__sizePort = 1;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].Port = (int *)malloc(g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].__sizePort * sizeof(int));
    *g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].Port = ONVIF_HTTPS_PORT;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].Extension = NULL;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__HTTPS].__anyAttribute = NULL;

   g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].Name = tt__NetworkProtocolType__RTSP;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].Enabled = xsd__boolean__true_;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].__sizePort = 1;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].Port = (int *)malloc(g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].__sizePort * sizeof(int));
    *g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].Port = ONVIF_RTSP_PORT;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].Extension = NULL;
    g_GkIpc_OnvifInf.NetworkProtocolsInf.NetworkProtocols[tt__NetworkProtocolType__RTSP].__anyAttribute = NULL;


	/*Init Media Profile*/
	g_GkIpc_OnvifInf.gokeIPCameraProfiles = malloc(MAX_PROFILE_NUM * sizeof(struct tt__Profile));
	memset(g_GkIpc_OnvifInf.gokeIPCameraProfiles, 0, MAX_PROFILE_NUM * sizeof(struct tt__Profile));
	for(i = 0; i < DEFAULT_PROFILE_NUM; i++){
		if(&gokeDefIPCameraProfiles[i] != NULL){
			memcpy(&g_GkIpc_OnvifInf.gokeIPCameraProfiles[i], &gokeDefIPCameraProfiles[i], sizeof(struct tt__Profile));
			ucCnt++;
		}
	}
	g_GkIpc_OnvifInf.ProfileNum = ucCnt;

	/*Init Media Source*/
	g_GkIpc_OnvifInf.gokeIPCameraVideoSource = malloc(MAX_VIDEOSOURCE_NUM * sizeof(struct tt__VideoSourceConfiguration));
	memset(g_GkIpc_OnvifInf.gokeIPCameraVideoSource, 0, MAX_VIDEOSOURCE_NUM * sizeof(struct tt__VideoSourceConfiguration));
	ucCnt = 0;
	for(i = 0; i < DEFAULT_VIDEOSOURCE_NUM; i++){
		if(&gokeDefVideoSourceConfiguration[i] != NULL){
			memcpy(&g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i], &gokeDefVideoSourceConfiguration[i], sizeof(struct tt__VideoSourceConfiguration));
			ucCnt++;
		}
	}
	g_GkIpc_OnvifInf.VideoSourceNum= ucCnt;

	/*Init Media Encode*/
	g_GkIpc_OnvifInf.gokeIPCameraVideoEncode = malloc(MAX_VIDEOENCODE_NUM * sizeof(struct tt__VideoEncoderConfiguration));
	memset(g_GkIpc_OnvifInf.gokeIPCameraVideoEncode, 0, MAX_VIDEOENCODE_NUM * sizeof(struct tt__VideoEncoderConfiguration));
	ucCnt = 0;
	for(i = 0; i < DEFAULT_VIDEOENCODE_NUM; i++){
		if(&gokeDefVideoEncoderConfiguration[i] != NULL){
			memcpy(&g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i], &gokeDefVideoEncoderConfiguration[i], sizeof(struct tt__VideoEncoderConfiguration));
			ucCnt++;
		}
	}
	g_GkIpc_OnvifInf.VideoEncodeNum= ucCnt;

	/*Init Media Source Option*/
	g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption = malloc(MAX_VIDEOSOURCEOPTION_NUM * sizeof(struct tt__VideoSourceConfigurationOptions));
	memset(g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption, 0, MAX_VIDEOSOURCEOPTION_NUM * sizeof(struct tt__VideoSourceConfigurationOptions));
	ucCnt = 0;
	for(i = 0; i < DEFAULT_VIDEOSOURCEOPTION_NUM; i++){
		if(&gokeDefVideoSourceConfigurationOption[i] != NULL){
			memcpy(&g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i], &gokeDefVideoSourceConfigurationOption[i], sizeof(struct tt__VideoSourceConfigurationOptions));
			ucCnt++;
		}
	}
	g_GkIpc_OnvifInf.VideoSourceOptionNum= ucCnt;

	/*Init Media Encode Option*/
	g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption = malloc(MAX_VIDEOENCODEOPTION_NUM * sizeof(struct tt__VideoEncoderConfigurationOptions));
	memset(g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption, 0, MAX_VIDEOENCODEOPTION_NUM * sizeof(struct tt__VideoEncoderConfigurationOptions));
	ucCnt = 0;
	for(i = 0; i < DEFAULT_VIDEOENCODEOPTION_NUM; i++){
		if(&gokeDefVideoEncodeConfigurationOption[i] != NULL){
			memcpy(&g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i], &gokeDefVideoEncodeConfigurationOption[i], sizeof(struct tt__VideoEncoderConfigurationOptions));
			ucCnt++;
		}
	}
	g_GkIpc_OnvifInf.VideoEncodeOptionNum= ucCnt;


	for(i = 0; i < g_GkIpc_OnvifInf.ProfileNum; i++){
	    printf("[Profile]Name:%s,Token:%s,Fix:%d\n",
	            g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].Name,
	            g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].token,
	            *g_GkIpc_OnvifInf.gokeIPCameraProfiles[i].fixed);
	}

	for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceNum; i++){
	    printf("[VideoSource]Name:%s,Token:%s,SourceToken:%s,bound-x:%d,bound-y:%d,bound-width:%d,bound-height:%d,UseCount:%d\n",
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Name,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].token,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].SourceToken,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->x,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->y,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->width,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].Bounds->height,
	            g_GkIpc_OnvifInf.gokeIPCameraVideoSource[i].UseCount);
	}

	for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeNum; i++){
		printf("[VideoEncode]GovLength:%d,H264Profile:%d,Width:%d,Height:%d,BitrateLimit:%d,FrameRateLimit:%d,EncodingInterval:%d,Encode:%d\n",
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264->GovLength,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].H264->H264Profile,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Width,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Resolution->Height,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->BitrateLimit,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->FrameRateLimit,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].RateControl->EncodingInterval,
									g_GkIpc_OnvifInf.gokeIPCameraVideoEncode[i].Encoding);
	}

	for(i = 0; i < g_GkIpc_OnvifInf.VideoSourceOptionNum; i++){
	    printf("[VideoSourceOption]XRangeMin:%d,XRangeMax:%d,YRangeMin:%d,YRangeMax:%d,WidthRangeMin:%d,WidthRangeMax:%d,HeightRangeMin:%d,HeightRangeMax:%d,sizeVideoSourceTokens:%d,VideoSourceTokens:%s\n",
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->XRange->Min,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->XRange->Max,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->YRange->Min,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->YRange->Max,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->WidthRange->Min,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->WidthRange->Max,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->HeightRange->Min,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].BoundsRange->HeightRange->Max,
	            g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].__sizeVideoSourceTokensAvailable,
	            *g_GkIpc_OnvifInf.gokeVideoSourceConfigurationOption[i].VideoSourceTokensAvailable);
	}


	for(i = 0; i < g_GkIpc_OnvifInf.VideoEncodeOptionNum; i++){
		printf("[VideoEncodeOption]QualityMin:%d,QualityMax:%d,sizeResolutions:%d,Resolutions0Width:%d,Resolutions0Height:%d,Resolutions1Width:%d,Resolutions1Height:%d,Resolutions2Width:%d,Resolutions2Height:%d\n",
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].QualityRange->Min,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].QualityRange->Max,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->__sizeResolutionsAvailable,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[0].Width,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[0].Height,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[1].Width,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[1].Height,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[2].Width,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->ResolutionsAvailable[2].Height);
		printf("[VideoEncodeOption]GovLengthMin:%d,GovLengthMax:%d,FrameRateMin:%d,FrameRateMax:%d,EncodingIntervalMin:%d,EncodingIntervalMax:%d,sizeH264ProfilesSupported:%d,H264ProfilesSupported:%d\n",
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->GovLengthRange->Min,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->GovLengthRange->Max,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->FrameRateRange->Min,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->FrameRateRange->Max,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->EncodingIntervalRange->Min,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->EncodingIntervalRange->Max,
									g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->__sizeH264ProfilesSupported,
									*g_GkIpc_OnvifInf.gokeVideoEncoderConfigurationOption[i].H264->H264ProfilesSupported);
	}
    FUN_OUT();
    return 0;

}

int _main(int argc,char ** argv)
{
    PRINT_DBG("[%s][%d][%s][%s] start \n", __FILE__, __LINE__, __TIME__, __func__);

	int count = 0;
    struct soap     ServerSoap;
    struct ip_mreq  mcast;
    pthread_t       thread_request;
    int             sock_opt = 1;
    unsigned char   one      = 0;
    pthread_attr_t attr;
    struct sockaddr addr;

    if (0 != init_env())
    {
        PRINT_ERR("ERROR!init_env\n");
        return -1;
    }

    signal(SIGUSR1, hellobye_handle);
    signal(SIGUSR2, hellobye_handle);

    if (pthread_attr_init(&attr) < 0)
    {
        PRINT_ERR("ERROR!attr_init\n");
    }
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_create(&thread_request, &attr, soap_request_handler, 0);


    soap_init1(&ServerSoap, SOAP_IO_UDP | SOAP_XML_IGNORENS);
    soap_set_namespaces(&ServerSoap,  namespaces);

    PRINT_DBG("[%s][%d][%s][%s] ServerSoap.version = %d \n", __FILE__, __LINE__, __TIME__, __func__, ServerSoap.version);

    /*-----------------------------------------------------------------------------
     *  Say Hello
     *-----------------------------------------------------------------------------*/
#if 1
    struct soap *soap_hello = soap_new1(SOAP_IO_UDP|SOAP_XML_IGNORENS);
    soap_set_namespaces(soap_hello,  namespaces);

    if(!soap_valid_socket(soap_bind(soap_hello, NULL, ONVIF_LISTEN_PORT, 10)))
    {
        soap_print_fault(soap_hello, stderr);
        exit(1);
    }

    if (SOAP_OK != __wsdd__Hello(soap_hello, NULL))
    {
        PRINT_ERR("ERROR!Say Hello\n");
    }

    soap_destroy(soap_hello);
    soap_end(soap_hello);
    //soap_free(soap_hello);
#endif

    /*-----------------------------------------------------------------------------
     *  Recvfrom Mulcast
     *-----------------------------------------------------------------------------*/

    if(!soap_valid_socket(soap_bind(&ServerSoap, NULL, ONVIF_LISTEN_PORT, 10)))
    {
        soap_print_fault(&ServerSoap, stderr);
        exit(1);
    }

    PRINT_DBG("ServerSoap master socket %d\n", ServerSoap.master);

    if (setsockopt(ServerSoap.master, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_opt, sizeof(sock_opt)) < 0) {
        PRINT_ERR("setsockopt SO_REUSEADDR error! error code = %d,err string = %s\n",errno,strerror(errno));
        return 0;
    }

    if (setsockopt(ServerSoap.master, IPPROTO_IP, IP_MULTICAST_LOOP, (void*)&one, sizeof(one)) < 0) {
        PRINT_ERR("setsockopt IP_MULTICAST_LOOP error! error code = %d,err string = %s\n",errno,strerror(errno));
        return 0;
    }

    gNetworkAdapterConfiguration.get_ip(ETHERNET_ADAPT, &addr);

	mcast.imr_multiaddr.s_addr = inet_addr(MULTIADDR);
    mcast.imr_interface.s_addr = (*(struct sockaddr_in *)&addr).sin_addr.s_addr;

    if(setsockopt(ServerSoap.master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0)
    {
        PRINT_ERR("setsockopt error! error code = %d,err string = %s\n",errno,strerror(errno));
        return 0;
    }

    for(;;)
    {
        if(soap_serve(&ServerSoap)) {
            soap_print_fault(&ServerSoap, stderr);
        }

        soap_destroy(&ServerSoap);
        soap_end(&ServerSoap);

        /* IP address of client */
        PRINT_DBG("RECEIVE count %d, connection from IP = %lu.%lu.%lu.%lu socket = %d \r\n",
				count, ((ServerSoap.ip)>>24)&0xFF, ((ServerSoap.ip)>>16)&0xFF, ((ServerSoap.ip)>>8)&0xFF, (ServerSoap.ip)&0xFF, (ServerSoap.socket));
        count++;

    }

    PRINT_DBG("\033[41;32m warning!!!! Sean soap_done advance ===> %s():\033[0m\n", __func__);


/* detach soap runtime */
    soap_done(&ServerSoap);

    return 0;


}


