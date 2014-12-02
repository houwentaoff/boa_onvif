/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke
 *       Filename:  include.h
 *
 *    Description:  
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  2014/7/8 19:51:26
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:  Created by housir
 *
 * =====================================================================================
 */
#ifndef  __INCLUDE__
#define  __INCLUDE__
#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>          
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <net/if_arp.h>
#ifdef HAVE_NET_ETHERNET_H
# include <net/ethernet.h>
#endif
#include <sys/ioctl.h>
#include <string.h>
#include "soapStub.h"


/* #####   DEBUG MACROS   ########################################################### */
#define     INOUT_DEBUG                          1  /*1 is open , o is close */
#define     ONVIF_DEBUG                          1  /*1 is open , 0 is close */
#define     ONVIF_ERROR                          1  /*1 is open , 0 is close */

/* #####   EXPORTED MACROS   ######################################################## */
#define      IPV4                                4            /*  */
#define      IPV6                                6            /*  */
#define      MIN_PROF_TOKEN                     32            /*  */
#define      MAX_SCOPE                          10 /*  */
#define      MAX_USER                           10/*  */
#define      LEN_USRNAME                        24/*  */
#define      LEN_PASSWD                         24/*  */
#define      LEN_URL                            100   /*  */
#define ONVIF_LISTEN_PORT		                3702
#define ONVIF_HTTP_PORT                         858/*  */
#define ONVIF_HTTPS_PORT                        1111/*  */
#define ONVIF_RTSP_PORT                         554/*  */
#define	ONVIF_REQ_LISTEN_PORT	                858
#define ADAPTERNUM_MAX                          5 /*  */
#define MCAST_DATA 				                "Sean: BROADCAST TEST DATA"    /*?ಥ???͵?????*/
#define	ETHERNET_ADAPT                          "eth0" 
#define	MULTIADDR           	                "239.255.255.250"  			   /*ws-discovery的组播地址和端口是239.255.255.250???702  */
#define	ADAPTERNUM_MAX                          5
#define MAX_GATE_COUNT                          10            /* gateway???? */


#define ONVIF_TRUE    			1            
#define ONVIF_FALSE   			0            

#define MAX_PROF_TOKEN			64
#define NTP_SERVER              "10.10.10.10"/*  */
#define MAC_ADDR				"1e:2e:3e:4e"
#define ADDR_IP					"192.168.0.222"
#define SIZE_MTU				1500
#define NETMASK                 16
#define LEN_HOSTNAME            100 /* len of hostname*/
#define LEN_ERR_INFO            100 /*len of err info*/
#define LEN_DNS                 64
#define LEN_CMD                 100 /* length of cmd */
#define NUM_NETWORK_CARD        1
#define LEN_NEC                 30 
#define PTZ_DEVICE_NAME         64
#define PTZ_CONFIG_NAME         32
#define ETHERNET                6
#define SPEED_ETH               10
#define MACH_ADDR_LENGTH        6
#define INFO_LENGTH             512
#define LARGE_INFO_LENGTH       1024
#define SMALL_INFO_LENGTH       512
#define URL_WSDL            	"http://www.onvif.org/ver10/media/wsdl"
#define TIME_ZONE            	"China(GMT+8)\n"
#define TIME_ZONE_NUM           8            /*  */
#define MULTICAST_ADDRESS       "239.255.255.250"
#define MUL_ONVIFMUL_PORT		3702


#define DEFAULT_PROFILE_NUM 			2
#define DEFAULT_VIDEOSOURCE_NUM  		1
#define DEFAULT_VIDEOENCODE_NUM 		2
#define DEFAULT_VIDEOSOURCEOPTION_NUM	1
#define DEFAULT_VIDEOENCODEOPTION_NUM	2
#define MAX_PROFILE_NUM					4
#define MAX_VIDEOSOURCE_NUM				4
#define MAX_VIDEOENCODE_NUM				4
#define MAX_VIDEOSOURCEOPTION_NUM		4
#define MAX_VIDEOENCODEOPTION_NUM		4
#define PTZ_CONFIGURATIONS_NUM 1


#define  SOAP_HELLO             SIGUSR1  /*  */
#define  SOAP_BYE               SIGUSR2  /*  */


#if INOUT_DEBUG
#define FUN_IN(fmt, args...)            printf("===> %s():"fmt"\n", __func__, ##args);/*  */
#define FUN_OUT(fmt, args...)           printf("<=== %s():"fmt"\n", __func__, ##args); /*  */
#else
#define FUN_IN(fmt, args...)
#define FUN_OUT(fmt, args...) 
#endif

#if ONVIF_DEBUG
#define PRINT_DBG(fmt, args...)            printf("Sean: %s():"fmt"\n", __func__, ##args);/*  */
#else
#define PRINT_DBG(fmt, args...)
#endif    

#if ONVIF_ERROR
#define PRINT_ERR(fmt, args...)                                                             \
do                                                                                          \
{                                                                                           \
    printf("\033[5;41;32m [ERROR] ---> %s ():line[%d]:\033[0m\n", __func__, __LINE__);      \
    printf(" "fmt, ##args);                                                                 \
}while(0)    /* */    
#else
#define PRINT_ERR(fmt, args...)  
#endif


/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */
typedef enum __bool { false = 0, true = 1, } bool;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;


struct gkonvif_NetworkProtocols
{
    int __sizeNetworkProtocols;
    struct tt__NetworkProtocol *NetworkProtocols;
};
typedef struct gkonvif_NetworkProtocols Gkonvif_NetworkProtocols;

typedef struct gkIpc_OnvifInf {
    bool is_reboot;
    /* Discovery */
    enum tt__DiscoveryMode discoverymode;
    struct tt__Scope **Scopes;/*match info*/
    char *XAddrs;/*Device Server Address*/
    /* Security */
    U8 Usercount;
    struct tt__User **User;	
    /*network */
    enum xsd__boolean DHCP;
    enum xsd__boolean DHCPv6;
    enum tt__IPv6DHCPConfiguration DHCPs6;
    bool NIC_alive;/*network interface card is alive or not*/
    struct gkonvif_NetworkProtocols NetworkProtocolsInf;

    /*time */
    enum tt__SetDateTimeType DateTimeType;
    enum xsd__boolean DaylightSavings;
    int  time_zone;
	/*media profile*/
	U8 ProfileNum;
	struct tt__Profile *gokeIPCameraProfiles;
	/*media source*/
	U8 VideoSourceNum;
	struct tt__VideoSourceConfiguration *gokeIPCameraVideoSource;
	/*media encode*/
	U8 VideoEncodeNum;
	struct tt__VideoEncoderConfiguration *gokeIPCameraVideoEncode;
	/*media source option*/
	U8 VideoSourceOptionNum;
	struct tt__VideoSourceConfigurationOptions *gokeVideoSourceConfigurationOption;
	/*media encode option*/
	U8 VideoEncodeOptionNum;
	struct tt__VideoEncoderConfigurationOptions *gokeVideoEncoderConfigurationOption;
}GkIpc_OnvifInf;

/* #####   EXPORTED VARIABLES   ##################################################### */
#ifndef __ONVIF_SERVER_C__
extern  GkIpc_OnvifInf g_GkIpc_OnvifInf;
#endif

#ifdef __cplusplus
}
#endif
#endif     /* -----  __INCLUDE__  ----- */
