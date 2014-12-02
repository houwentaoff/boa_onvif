/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke C&S.
 *       Filename:  onvif_client.c
 *
 *    Description:  
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  Saturday, June 21, 2014 05:03:32 HKT
 *       Revision:  none
 *       Compiler:  arm-gcc
 *
 *         Author:  Sean , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:  Saturday, June 21, 2014 Created by SeanHou
 *
 * =====================================================================================
 */

#include "nsmap.h"
#include "soapH.h"
#include "soapStub.h"
#include "onvif_function.h"
//#include "soapStub.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <uuid/uuid.h>

#include "include.h"
#include "struct_net.h"
/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
#define ONVIF_LISTEN_PORT	3702
#define MCAST_ADDR "239.255.255.250"     /*一个局部连接多播地址，路由器不进行转发*/
#define MCAST_DATA "Sean: BROADCAST TEST DATA"             /*多播发送的数据*/

#define ETHERNET_ADAPT          "wlan0" /*  */
#define  MULTIADDR           "239.255.255.250"  /*因为ws-discovery的组播地址和端口就是为239.255.255.250和3702  */

//#define MULTICAST_ADDRESS   "192.168.1.102"  /*因为ws-discovery的组播地址和端口就是为239.255.255.250和3702  */

/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */


int main()  
{  
    printf("[%s][%d][%s][%s] start \n", __FILE__, __LINE__, __TIME__, __func__);
	int count = 0;
	struct soap ServerSoap;
	struct ip_mreq mcast;
	pthread_t thread_request;
	int sock_opt = 1;
	unsigned char one = 1;
	unsigned int ip = 0;

    int result = 0;  
    wsdd__ProbeType req;
    struct __wsdd__ProbeMatches resp;
    wsdd__ScopesType sScope;
    struct SOAP_ENV__Header header;  
    int i;

    struct soap *soap;  
    soap = soap_new();  
    if(NULL == soap )  
    {  
        printf("sopa new error\r\n");  
        return -1;  
    }  
    printf("master[%d]line[%d]\n", soap->master, __LINE__);
	soap_init1(soap, SOAP_IO_UDP | SOAP_XML_IGNORENS);
    printf("master[%d]line[%d]\n", soap->master, __LINE__);


    soap->recv_timeout = 10;  
    soap_set_namespaces(soap, namespaces);  
    soap_default_SOAP_ENV__Header(soap, &header);  

    uuid_t uuid;
    char guid_string[100];
    uuid_generate(uuid);
    uuid_unparse(uuid, guid_string);

    header.wsa__MessageID = guid_string; 
    header.wsa__To = "urn:schemas-xmlsoap-org:ws:2005:04:discovery";  
    //    header.wsa__Action = "http://www.onvif.org/ver10/device/wsdl/GetServices";
    header.wsa__Action = "http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";//http://schemas.xmlsoap.org/ws/2005/04/discovery/";  
    soap->header = &header;  /*Sean Hou: 必须赋值 否则 客户端soap error 2: -1, (null), (null) 服务器挂掉*/

     soap_default_wsdd__ScopesType(soap, &sScope);  
     //	sScope.__item = "onvif://www.onvif.org/type/NetworkVideoTransmitter";  
    sScope.__item = "";//"onvif://www.onvif.org/type/NetworkVideoTransmitter";  
    soap_default_wsdd__ProbeType(soap, &req);  
    req.Scopes = &sScope;
    //	req.Types = "tds:Device";//"daffffffff";//"wsdd:NetworkVideoTransmitter"; //"dn:NetworkVideoTransmitter";  
    req.Types = "";//"tdn:NetworkVideoTransmitter"; //"dn:NetworkVideoTransmitter";  
#if 0
    do{/*{{{*/
        //      soap_call___tdn__Probe(soap,"192.168.1.102", NULL, req, &resp);
        soap_send___wsdd__Probe(soap,"192.168.1.102", NULL, &req);

        if (soap->error)
        {
            printf("soap error 1: %d, %s, %s\n", soap->error, *soap_faultcode(soap), *soap_faultstring(soap));  
            result = soap->error;  
        }
        else
        {
            printf("guog *********************************************\r\n");  
            if(soap->header->wsa__MessageID)  
            {  
                printf("MessageID   : %s\r\n", soap->header->wsa__MessageID);  
            }  
            if(soap->header->wsa__RelatesTo && soap->header->wsa__RelatesTo->__item)  
            {  
                printf("RelatesTo   : %s\r\n", soap->header->wsa__RelatesTo->__item);  
            }  
            if(soap->header->wsa__To)  
            {  
                printf("To          : %s\r\n", soap->header->wsa__To);  
            }  
            if(soap->header->wsa__Action)  
            {  
                printf("Action      : %s\r\n", soap->header->wsa__Action);  
            }  

            for(i = 0; i < resp.wsdd__ProbeMatches->__sizeProbeMatch; i++)  
            {  
                printf("__sizeProbeMatch        : %d\r\n", resp.wsdd__ProbeMatches->__sizeProbeMatch);  
                printf("wsa__EndpointReference       : %p\r\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference);  
                printf("Target EP Address       : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address);  
                printf("Target Type             : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->Types);  
                printf("Target Service Address  : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->XAddrs);  
                printf("Target Metadata Version : %d\r\n", resp.wsdd__ProbeMatches->ProbeMatch->MetadataVersion);  
                if(resp.wsdd__ProbeMatches->ProbeMatch->Scopes)  
                {  
                    printf("Target Scopes Address   : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->Scopes->__item);  
                }  
            }
        }
    }while(0);/*}}}*/

    /*-----------------------------------------------------------------------------
     *  两种方法
     *-----------------------------------------------------------------------------*/
#else
    i = 0;
    int j=0;
    printf("tag[");
    for(j=0;j<50;j++)
        printf("%c ", soap->tag[j]);
    puts("] ");
    if(!soap_valid_socket(soap_bind(soap, NULL, ONVIF_LISTEN_PORT, 0)))
	{
		soap_print_fault(soap, stderr);
		exit(1);
	}
//  soap->master = socket(AF_INET, SOCK_DGRAM, 0);          /*建立套接字*/
//    if (soap->master == -1)
//    {
//        perror("socket()");
//        return -1;
//    }
    printf("master[%d]line[%d]\n", soap->master, __LINE__);

#if 1
	printf("soap master socket %d\n", soap->master);

	if (setsockopt(soap->master, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_opt, sizeof(sock_opt)) < 0) {
	    printf("setsockopt SO_REUSEADDR error! error code = %d,err string = %s\n",errno,strerror(errno));
	    return 0;
	}

	if (setsockopt(soap->master, IPPROTO_IP, IP_MULTICAST_LOOP, (void*)&one, sizeof(one)) < 0) {
	    printf("setsockopt IP_MULTICAST_LOOP error! error code = %d,err string = %s\n",errno,strerror(errno));
	    return 0;
	}

	if (netGetIp(ETHERNET_ADAPT, &ip) < 0) {
	    printf("Get ethernet_adapt ip error\n");
	    return 0;
	}

	mcast.imr_multiaddr.s_addr = inet_addr(MULTIADDR);
    //mcast.imr_interface.s_addr = htonl(INADDR_ANY);
    mcast.imr_interface.s_addr = ip;
#if 1
	if(setsockopt(soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(mcast)) < 0)
	{
		printf("setsockopt error! error code = %d,err string = %s\n line[%d]",errno,strerror(errno), __LINE__);
		return 0;
	}
#endif
#endif
#if 0
    struct sockaddr_in mcast_addr;      

    memset(&mcast_addr, 0, sizeof(mcast_addr));/*初始化IP多播地址为0*/
    mcast_addr.sin_family = AF_INET;                 /*设置协议族类行为AF*/
    mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);/*设置多播IP地址*/
    mcast_addr.sin_port = htons(3702);         /*设置多播端口*/

    /*向多播地址发送数据*/
    for (i=0;i<100;i++)
    {
        int n = sendto(soap->master,                            /*套接字描述符*/
                MCAST_DATA,      /*数据*/
                sizeof(MCAST_DATA),      /*长度*/
                0,
                (struct sockaddr*)&mcast_addr,
                sizeof(mcast_addr)) ;
        if( n < 0)
        {
            perror("sendto()");
            return -2;
        } 
        sleep (2);
        printf("111111111111111\n");
    }
    return 0;
#endif
    result = soap_send___wsdd__Probe(soap, "soap.udp://239.255.255.250:3702/", NULL, &req);  
    printf("tag[");
    for(j=0;j<50;j++)
        printf("%c ", soap->tag[j]);
    puts("] ");

    //	header.wsa__To = NULL;//"urn:schemas-xmlsoap-org:ws:2005:04:discovery";  
    //	header.wsa__Action = NULL;//"http://schemas.xmlsoap.org/ws/2005/04/discovery/Probe";  
    while(result == SOAP_OK)  
    {  
        result = soap_recv___wsdd__ProbeMatches(soap, &resp);  
        printf("tag[");
        for(j=0;j<50;j++)
            printf("%c ", soap->tag[j]);
        puts("] ");

        if(result == SOAP_OK)  
        {  
            if(soap->error)  
            {  
                printf("soap error 1: %d, %s, %s\n", soap->error, *soap_faultcode(soap), *soap_faultstring(soap));  
                result = soap->error;  
            }  
            else  
            {  
                printf("guog *********************************************\r\n");  
                if(soap->header->wsa__MessageID)  
                {  
                    printf("MessageID   : %s\r\n", soap->header->wsa__MessageID);  
                }  
                if(soap->header->wsa__RelatesTo && soap->header->wsa__RelatesTo->__item)  
                {  
                    printf("RelatesTo 从server获取的  : %s\r\n", soap->header->wsa__RelatesTo->__item);  
                }  
                if(soap->header->wsa__To)  
                {  
                    printf("To          : %s\r\n", soap->header->wsa__To);  
                }  
                if(soap->header->wsa__Action)  
                {  
                    printf("Action      : %s\r\n", soap->header->wsa__Action);  
                }  

                for(i = 0; i < resp.wsdd__ProbeMatches->__sizeProbeMatch; i++)  
                {  
                    printf("__sizeProbeMatch        : %d\r\n", resp.wsdd__ProbeMatches->__sizeProbeMatch);  
                    printf("wsa__EndpointReference       : %p\r\n", &resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference);  
                    printf("Target EP Address       : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->wsa__EndpointReference.Address);  
                    printf("Target Type             : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->Types);  
                    printf("Target Service Address  : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->XAddrs);  
                    printf("Target Metadata Version : %d\r\n", resp.wsdd__ProbeMatches->ProbeMatch->MetadataVersion);  
                    if(resp.wsdd__ProbeMatches->ProbeMatch->Scopes)  
                    {  
                        printf("Target Scopes Address   : %s\r\n", resp.wsdd__ProbeMatches->ProbeMatch->Scopes->__item);  
                    }  
                }
            }  
        }  
        else if (soap->error)  
        {  
            printf("[%d] soap error 2: %d, %s, %s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));  
            result = soap->error;  
        }  
    }  
#endif
     printf("[%d] soap error 2: %d, %s, %s\n", __LINE__, soap->error, *soap_faultcode(soap), *soap_faultstring(soap));
    soap_destroy(soap); 
    soap_end(soap); 
    soap_free(soap);

    printf("[%d] guog discover over !\n", __LINE__);

    return result;  
}  
