#include "onvif_net.c"



#include <stdlib.h>

#define  ETHERNET_ADAPT   "wlan0"           /*  */
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
    struct sockaddr addr, netmask, broadaddr;
    int i=0;

    memset(&addr, 0, sizeof(addr));
    addr.sa_family = AF_INET;
    (*(struct sockaddr_in *)&addr).sin_addr.s_addr = inet_addr("192.168.1.18");

    /*-----------------------------------------------------------------------------
     *  set_ip will down ETHERNET_ADAPT. so you must set all the net config.
     *-----------------------------------------------------------------------------*/
    struct sockaddr *addr_matrix[MAX_GATE_COUNT]={0};
    int count_gateway=0;
#if 1
    if (0 != gNetworkAdapterConfiguration.get_gateway(ETHERNET_ADAPT, addr_matrix, &count_gateway))
    {
        goto err;
    }
    while (i<count_gateway)
    {
        printf("[%d]gateway[%s]\n", i, inet_ntoa( (*(struct sockaddr_in *)(addr_matrix[i])).sin_addr));
        i++;
    }
//    sleep (1);
    if (0 != gNetworkAdapterConfiguration.get_netmask(ETHERNET_ADAPT, (struct sockaddr *)&netmask))
    {
        goto err;
    } 
#endif
#if 0
//    sleep (1);
    if (0 != gNetworkAdapterConfiguration.get_broadaddr(ETHERNET_ADAPT, (struct sockaddr *)&broadaddr))
    {
        goto err;
    }
#endif
#if 1
    if (0 != gNetworkAdapterConfiguration.set_ip(ETHERNET_ADAPT, (struct sockaddr *)&addr))
    {
        goto err;
    }

//    sleep (1);
    if (0 != gNetworkAdapterConfiguration.set_netmask(ETHERNET_ADAPT, (struct sockaddr *)&netmask))
    {
        goto err;
    }
//    sleep (1);
#if 0
    if (0 != gNetworkAdapterConfiguration.set_broadaddr(ETHERNET_ADAPT, (struct sockaddr *)&broadaddr))
    {
        goto err;
    }
#endif
#endif
    if (0 != gNetworkAdapterConfiguration.set_gateway(ETHERNET_ADAPT, addr_matrix, count_gateway))
    {
        goto err;
    }
//    sleep (1);
    /*free gateway temp  array*/
    for (i=0;i<count_gateway;i++)
    {
        free(addr_matrix[i]);
    }    

    return EXIT_SUCCESS;

err:
    exit(-1);
}				

