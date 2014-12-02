/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke
 *       Filename:  struct_net.h
 *
 *    Description:  
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  Wednesday, July 09, 2014 05:15:40 HKT
 *       Revision:  none
 *       Compiler:  xxx-gcc
 *
 *         Author:  Sean Hou , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:   History:  Wednesday, July 09, 2014 Created by SeanHou
 *
 * =====================================================================================
 */

#ifndef  __ONVIF_NET_H__
#define  __ONVIF_NET_H__

#include "onvif_common.h"


/* #####   EXPORTED TYPE DEFINITIONS   ############################################## */

typedef struct NetworkAdapterConfiguration
{

    struct NetworkAdapterConfiguration * next;/*Sean Hou: 多个网卡多个结构 有些是公有的不必放入下一个链*/
    char *name;/* 网卡名字 */
    int (*get_name)(char *name[], int *count_adapter);
    int (*get_mtu)(const char *adapter_name, int *mtu);
    int (*set_mtu)(const char *adapter_name, const int mtu);
    int (*get_hwaddr)(const char *adapter_name, unsigned char hwaddr[]);
    int (*set_hwaddr)(const char *adapter_name, const unsigned char hwaddr[]);
    int (*get_ip)(const char *adapter_name, struct sockaddr *addr);
    int (*set_ip)(const char *adapter_name, const struct sockaddr *addr);
    int (*set_dhcp)(const char *adapter_name);
    int (*get_netmask)(const char *adapter_name, struct sockaddr *netmask);
    int (*set_netmask)(const char *adapter_name, const struct sockaddr *netmask);
    int (*get_broadaddr)(const char *adapter_name, struct sockaddr *broadaddr);
    int (*set_broadaddr)(const char *adapter_name, struct sockaddr *broadaddr);
    int (*get_ipv6)(const char *adapter_name, struct sockaddr_in6 *ipv6);
    //全双工，速度，等等信
    //获取网关


    int (*get_gateway)(const char *adapter_name, struct sockaddr *gateway[], int *count_gateway);
    int (*set_gateway)(const char *adapter_name, struct sockaddr *gateway[], int count_gateway);
    int (*get_gateway6)(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);
    //动态DNS
    int (*get_ddns)(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);//类型3?TTL+name
    int (*set_ddns)(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);//类型3TTL+name
    //静态DNS
    int (*get_dns)(char ***search, char ***nameserver, char **domain, int *size_search, int *size_ns);//需要手动释放指针
    int (*set_dns)(char **search, char **nameserver, char *domain, int size_search, int size_ns);//全部重新填写
    //获取主机名字 (从DHCP处获)
    int (*get_hostname)(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);
    int (*set_hostname)(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);
    int (*is_running)(const char *adapter_name, int *is_running);
    int (*is_ipaddr)(const char *ip_addr, int iptype);
    int (*covprefixlen)(struct sockaddr *paddr);
}tNetworkAdapterConfiguration;

/* #####   EXPORTED VARIABLES   ##################################################### */
#ifndef __ONVIF_NET_C__
extern tNetworkAdapterConfiguration gNetworkAdapterConfiguration;
#endif   /* ----- #ifndef __ONVIF_NET_C__  ----- */

#endif   /* ----- #ifndef __ONVIF_NET_H__  ----- */
