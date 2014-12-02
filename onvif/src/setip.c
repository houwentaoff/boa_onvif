/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke C&S.
 *       Filename:  setip.c
 *
 *    Description:  
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  Wednesday, July 23, 2014 10:18:19 HKT
 *       Revision:  none
 *       Compiler:  arm-gcc
 *
 *         Author:  Sean , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:  Wednesday, July 23, 2014 Created by SeanHou
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "onvif_net.c"
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
#if 0/*Sean Hou: get_ip */
    struct  sockaddr_in local_addr;
        /*初始化地址*/
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = inet_addr("192.168.1.2");
//    local_addr.sin_port = htons(8888);
    gNetworkAdapterConfiguration.set_ip("eth0", (struct sockaddr*)&local_addr);
#endif
#if 1
    /*Sean Hou:  get_name*/
    char *name[10]={0};
    int count=0;
    int i=0;
    gNetworkAdapterConfiguration.get_name(name, &count);
    while(i<count)
        printf("%s\n", name[i++]);
#endif

    return EXIT_SUCCESS;
}

