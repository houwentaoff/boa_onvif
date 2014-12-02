/*
 * =====================================================================================
 *       Copyright (c), 2013-2020, Goke
 *       Filename:  struct_Net.c
 *
 *    Description:  获取网络相关参数
 *         Others:
 *   
 *        Version:  1.0
 *        Date:  Wednesday, July 09, 2014 05:15:38 HKT
 *       Revision:  none
 *       Compiler:  arm-gcc
 *
 *         Author:  Sean , houwentaoff@gmail.com
 *   Organization:  Goke
 *        History:  Wednesday, July 09, 2014 Created by SeanHou
 *
 * =====================================================================================
 */

#define __ONVIF_NET_C__
#include"onvif_net.h"
#undef __ONVIF_NET_C__

/* #####   MACROS  -  LOCAL TO THIS SOURCE FILE   ################################### */
#define LEN_NAME_ADAPTER           10 /*  */

#define _PATH_PROCNET_DEV               "/proc/net/dev"
#define _PATH_PROCNET_IFINET6           "/proc/net/if_inet6"
#define _PATH_PROCNET_ROUTE             "/proc/net/route"
#define _PATH_DNS_CONT                  "/etc/resolv.conf"




//static struct interface *int_list, *int_last;
/* #####   FUNCTION DEFINITIONS  -  LOCAL TO THIS SOURCE FILE   ##################### */
static int get_name(char *name[], int *count_adapter);
static int get_mtu(const char* adapter_name, int *mtu);
static int set_mtu(const char* adapter_name, const int mtu);
static int get_hwaddr(const char *adapter_name, unsigned char hwaddr[]);
static int set_hwaddr(const char *adapter_name, const unsigned char hwaddr[]);
static int get_ip(const char *adapter_name, struct sockaddr *addr);
static int set_ip(const char *adapter_name, const struct sockaddr *addr);
static int set_dhcp(const char *adapter_name);

static int get_netmask(const char *adapter_name, struct sockaddr *netmask);
static int set_netmask(const char *adapter_name, const struct sockaddr *netmask);
static int get_broadaddr(const char *adapter_name, struct sockaddr *broadaddr);
static int set_broadaddr(const char *adapter_name, struct sockaddr *broadaddr);
static int get_ipv6(const char *adapter_name, struct sockaddr_in6 *ipv6);
static int get_gateway(const char *adapter_name, struct sockaddr *gateway[], int *count_gateway);
static int set_gateway(const char *adapter_name, struct sockaddr *gateway[], int count_gateway);
static int get_gateway6(const char *adapter_name, struct sockaddr_in6 *gateway6[], int *count_gateway6);
static int get_dns(char ***search, char ***nameserver, char **domain, int *size_search, int *size_ns);
static int set_dns(char **search, char **nameserver, char *domain, int size_search, int size_ns);
static int is_ipaddr(const char *ip_addr, int iptype);
static int covprefixlen(struct sockaddr *paddr);

tNetworkAdapterConfiguration gNetworkAdapterConfiguration =
{
    .get_name       = get_name,
    .get_mtu        = get_mtu,
    .set_mtu        = set_mtu,
    .get_hwaddr     = get_hwaddr,
    .set_hwaddr     = set_hwaddr,
    .get_ip         = get_ip,
    .set_ip         = set_ip,
    .get_netmask    = get_netmask,
    .set_netmask    = set_netmask,
    .get_broadaddr  = get_broadaddr,
    .set_broadaddr  = set_broadaddr,
    .get_ipv6       = get_ipv6,
    .get_gateway    = get_gateway,
    .set_gateway    = set_gateway,
    .get_dns        = get_dns,
    .set_dns        = set_dns,
    .is_ipaddr      = is_ipaddr,
    .covprefixlen   = covprefixlen,
    .set_dhcp       = set_dhcp,
};


#if 0
#define  search_nameserver(buf, _3pname)           \
{\
    delimPos = strtok(sch, " ");\
    while (delimPos)\
    {\
        (*_3pname)[i] = (char *)malloc(100 * sizeof(char));\
            strcpy((*_3pname)[i], delimPos);\
            i++;\
        delimPos = strtok(NULL, " \n");\

        printf("Sean ===> %s():line[%d]delimPos[%s]\n", __func__, __LINE__, delimPos);\

    }\
    (*search)[i] = NULL;\
}
#endif
static int set_dhcp(const char *adapter_name)
{
    FILE *fp = NULL;
    char cmd[LEN_CMD];
    char buffer[INFO_LENGTH];

    FUN_IN();

    if (0 == sprintf(cmd, "udhcpc -i %s  2>&1", adapter_name))
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

    return 0;
err:
    return -1;    
}
static int covprefixlen(struct sockaddr *paddr)
{
    unsigned int nmask = 0;
    int countbit=0;

    /*IPv4 */
    if (AF_INET == paddr->sa_family)
    {
        nmask = (*((struct sockaddr_in *)paddr)).sin_addr.s_addr;
        while (nmask)
        {
            nmask >>= 1;
            countbit++;
        }
    }

    return countbit;
}
static int is_ipaddr(const char *ip_addr, int iptype)
{
    unsigned int ip[5]={0};
    int ret;

    if (IPV4 == iptype)
    {
        ret = sscanf(ip_addr, "%3d.%3d.%3d.%3d", &ip[0], &ip[1], &ip[2],&ip[3]);
        if (ret != 4)
        {
            return false;
        }
        if (0xFFFFFFFF == inet_addr(ip_addr))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
static int set_dns(char **search, char **nameserver, char *domain, int size_search, int size_ns)
{
    int i=0;
    FILE *fp = NULL;
    char buf[]={"# Dynamic resolv.conf file for onvif resolver generated by onvif_server\n#     DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN\n"};

    FUN_IN();

#if 1  /*Sean Hou:  DEBUG*/
    while (i<size_search)
    {
        PRINT_DBG("search[%d]:[%s]\n", i, search[i]);
        i++;
    }
    i = 0;
    while (i<size_ns)
    {
        PRINT_DBG("nameserver[%d]:[%s]\n", i, nameserver[i]);
        i++;
    }    
    i=0;
    if (domain)
        PRINT_DBG("domain[%s]\n", domain);   
#endif
    fp= fopen(_PATH_DNS_CONT, "w+");
    if (fp == NULL)
        return -1;  

    fprintf(fp, "%s", buf);
    while (i<size_ns)
    {
        fprintf(fp, "nameserver %s\n", nameserver[i]);
        i++;
    }
    i=0;
    if (size_search!=0)
    {
        fprintf(fp, "%s", "search");
    }
    while (i<size_search)
    {
        fprintf(fp, " %s", search[i]);
        i++;
    }   
    fprintf(fp, "%s", "\n");
    if (domain)
    {
        fprintf(fp, "domain %s\n", domain);
    }
    fclose(fp);

    FUN_OUT();

    return 0;
}
static int get_dns(char ***search, char ***nameserver, char **domain, int *size_search, int *size_ns)
{
    char buf[100]={0};
    int r=0;
    char ns[100]={0};
    char sch[100]={0};
    char dm[100]={0};
    int count_ns=0;
    bool havedm=false;
    int count_sch=0;
    int i=0;
    char *delimPos = NULL;

    FUN_IN();

    FILE *fp = fopen(_PATH_DNS_CONT, "r");
    if (fp == NULL)
        return -1;    
    while ((r = fscanf(fp, "%s", buf)) == 1)
    {
        if (buf[0]=='#')
        {
            if (fscanf(fp, "%*[^\n]\n") < 0) { /* Skip the first line. */
                goto error;                /* Empty or missing line, or read error. */
            } 
            continue;
        }

        if (0 == strncmp(buf, "nameserver", sizeof ("nameserver")))
        {
            r = fscanf(fp, "%s", buf);
            if (r!=1)
                break; 
            count_ns++;
            if (count_ns>1)
            {
                strcat(ns, " ");
            }
            strcat(ns, buf);
        }
        else if (0 == strncmp(buf, "search", sizeof ("search")))
        {
            r = fscanf(fp, "%*[ ]%[^\n]s", buf);/*Sean Hou: skip space */
            if (r!=1)
                break; 
            count_sch++;
            if (count_sch>1)
            {
                strcat(sch, " ");
            }
            strcat(sch, buf);
        }
        else if (0 == strncmp(buf, "domain", sizeof ("domain")))
        {
            r = fscanf(fp, "%s", buf);
            if (r!=1)
                break; 
            strcat(dm, buf);
            havedm = true;
        }
    }

    fclose(fp);

    if (count_sch)
    {
        *search = (char **)malloc((5) * sizeof(char *));
        delimPos = strtok(sch, " ");
        while (delimPos)
        {
            (*search)[i] = (char *)malloc(100 * sizeof(char));
                strcpy((*search)[i], delimPos);
                i++;
            delimPos = strtok(NULL, " \n");
        }
        (*search)[i] = NULL;
    }
    if (count_ns)
    {
        *nameserver = (char **)malloc(count_ns * sizeof(char *));
        i = 0;
        delimPos = strtok(ns, " ");
        while (delimPos)
        {
            (*nameserver)[i] = (char *)malloc(100 * sizeof(char));
            strcpy((*nameserver)[i], delimPos);
            i++;
            delimPos = strtok(NULL, " \n");
        }
        (*nameserver)[i] = NULL;    
    }
    if (havedm)
    {
        *domain = (char *)malloc(64 * sizeof(char));
        strcpy(*domain, dm);
    }
    *size_search = count_sch;
    *size_ns = count_ns;

    FUN_OUT();

    return 0;
error:
    return -1;
}

static int set_mtu(const char* adapter_name, const int mtu)
{
	struct ifreq ifr;
	const char *ifname = adapter_name;
	int skfd;

    FUN_IN()

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);

    ifr.ifr_mtu = mtu;
	if (ioctl(skfd, SIOCSIFMTU, &ifr) < 0)
        PRINT_ERR("set mtu error!!\n");

	close(skfd);

    FUN_OUT()

	return 0;

}
static int set_hwaddr(const char *adapter_name, const unsigned char hwaddr[])
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    memcpy((void *) ifr.ifr_hwaddr.sa_data,hwaddr, 8);
    
	if (ioctl(skfd, SIOCSIFHWADDR, &ifr) < 0)
        PRINT_ERR("set hwaddr error!!\n");

	close(skfd);
	return 0;

}
static int set_netmask(const char *adapter_name, const struct sockaddr *netmask){
	struct ifreq ifr;
	const char *ifname = adapter_name;
	int skfd;

    FUN_IN()

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr = *netmask;

//	if (ioctl(skfd, SIOCSIFADDR, &ifr) == 0){
        if (ioctl(skfd, SIOCSIFNETMASK, &ifr) < 0)
        {
            perror("?");
            PRINT_ERR("set netmask error!!\n");
        }
//    }

	close(skfd);

    FUN_OUT()

	return 0;

}
static int set_ip(const char *adapter_name, const struct sockaddr *addr)
{
	struct ifreq ifr;
	const char *ifname = adapter_name;
	int skfd;
    int ret=0;

    FUN_IN()

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr = *addr;

	if ((ret = ioctl(skfd, SIOCSIFADDR, &ifr)) != 0){
        perror("?");
        PRINT_ERR("set ip error!!\n");
    }

	close(skfd);

    FUN_OUT()

	return ret;
    
}
static int set_gateway(const char *adapter_name, struct sockaddr *gateway[], int count_gateway)
{
    FILE *fp = NULL;
    char cmd[LEN_CMD];
    char buffer[INFO_LENGTH];
    int i=0;

    FUN_IN()

    for(i=0;i<count_gateway;i++)
    {
        if (0 == sprintf(cmd, "route add default gw %s %s ", inet_ntoa((*(struct sockaddr_in *)gateway[i]).sin_addr), adapter_name))
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
    }

    FUN_OUT()

    return 0;
err:
    return -1;
}
static int get_gateway(const char *adapter_name, struct sockaddr *gateway[], int *count_gateway)
{
    char devname[64] /*flags[16],*/ /* * sgw*//**sdest*/;
    char *sdest = NULL;//[18];
    unsigned long d, g, m;
    int flgs, ref, use, metric, mtu, win, ir;
    struct sockaddr_in s_addr;
    int count = 0;
    
    FILE *fp = fopen(_PATH_PROCNET_ROUTE, "r");



    if (fscanf(fp, "%*[^\n]\n") < 0) { /* Skip the first line. */
        goto ERROR;                /* Empty or missing line, or read error. */
	}
	while (1) {
		int r;
		r = fscanf(fp, "%63s%lx%lx%X%d%d%d%lx%d%d%d\n",
				devname, &d, &g, &flgs, &ref, &use, &metric, &m,
				&mtu, &win, &ir);
		if (r != 11) {
			if ((r < 0) && feof(fp)) { /* EOF with no (nonspace) chars read. */
				break;
			}
 ERROR:
            PRINT_ERR("ERROR read route table!");
            ;
		}

#if 0
		if (!(flgs & RTF_UP)) { /* Skip interfaces that are down. */
			continue;
		}
		set_flags(flags, (flgs & IPV4_MASK));
#ifdef RTF_REJECT
		if (flgs & RTF_REJECT) {
			flags[0] = '!';
		}
#endif
#endif

        memset(&s_addr, 0, sizeof(struct sockaddr_in));
        s_addr.sin_family = AF_INET;
        s_addr.sin_addr.s_addr = d;

        sdest = strdup(inet_ntoa(s_addr.sin_addr));

        if (0 == strcmp(sdest, "0.0.0.0"))
        {
            s_addr.sin_addr.s_addr = g;
            gateway[count] = (struct sockaddr *)malloc(sizeof(struct sockaddr));
            memcpy(gateway[count], (void *)&s_addr, sizeof(struct sockaddr));
            count++;
        }
        free(sdest);
	}
    *count_gateway = count;
	fclose(fp);
    return 0;
}
//hwaddr
static int get_ipv6(const char *adapter_name, struct sockaddr_in6 *ipv6)
{
    FILE *f;
    char addr6[40], devname[20];
    struct sockaddr_in6 sap;
    int plen, scope, dad_status, if_idx;
    char addr6p[8][5];

    memset(ipv6, 0, sizeof(struct sockaddr_in6));

    f = fopen(_PATH_PROCNET_IFINET6, "r");

    if (f == NULL)
        return -1;

    while (fscanf
            (f, "%4s%4s%4s%4s%4s%4s%4s%4s %08x %02x %02x %02x %20s\n",
             addr6p[0], addr6p[1], addr6p[2], addr6p[3], addr6p[4],
             addr6p[5], addr6p[6], addr6p[7], &if_idx, &plen, &scope,
             &dad_status, devname) != EOF
          ) {
        if (!strcmp(devname, adapter_name)) {
            sprintf(addr6, "%s:%s:%s:%s:%s:%s:%s:%s",
                    addr6p[0], addr6p[1], addr6p[2], addr6p[3],
                    addr6p[4], addr6p[5], addr6p[6], addr6p[7]);
            inet_pton(AF_INET6, addr6,
                    (struct sockaddr *) &sap.sin6_addr);
            sap.sin6_family = AF_INET6;
            *ipv6 = sap;
        }
    }
	fclose(f);
	return 0;

}

static int get_broadaddr(const char *adapter_name, struct sockaddr *broadaddr)
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr.sa_family = AF_INET;
    memset(broadaddr, 0, sizeof(struct sockaddr));

    if (ioctl(skfd, SIOCGIFADDR, &ifr) == 0){
        if (ioctl(skfd, SIOCGIFBRDADDR, &ifr) >= 0)
            *broadaddr = ifr.ifr_broadaddr;
    }

    close(skfd);
    return 0;

}
static int set_broadaddr(const char *adapter_name, struct sockaddr *broadaddr)
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    FUN_IN()

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr.sa_family = AF_INET;
    ifr.ifr_broadaddr = *broadaddr;

    if (ioctl(skfd, SIOCSIFADDR, &ifr) == 0){
        if (ioctl(skfd, SIOCSIFBRDADDR, &ifr) < 0)
            PRINT_ERR("set netmask error!!\n");
    }

    close(skfd);

    FUN_OUT()

    return 0;

}
static int get_netmask(const char *adapter_name, struct sockaddr *netmask)
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr.sa_family = AF_INET;
    memset(netmask, 0, sizeof(struct sockaddr));

    if (ioctl(skfd, SIOCGIFADDR, &ifr) == 0){
        if (ioctl(skfd, SIOCGIFNETMASK, &ifr) >= 0)
            *netmask = ifr.ifr_netmask;
    }

    close(skfd);
    return 0;

}
static int get_ip(const char *adapter_name, struct sockaddr *addr)
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);
    ifr.ifr_addr.sa_family = AF_INET;
    memset(addr, 0, sizeof(struct sockaddr));

    if (ioctl(skfd, SIOCGIFADDR, &ifr) == 0){
        *addr = ifr.ifr_addr;
    }

    close(skfd);
    return 0;

}
static int get_hwaddr(const char *adapter_name, unsigned char hwaddr[])
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);

    memset(hwaddr, 0, 6);
//    printf("==>%s():hwaddr_size[%d]\n", sizeof(hwaddr));
    if (ioctl(skfd, SIOCGIFHWADDR, &ifr) >= 0)
        memcpy(hwaddr, ifr.ifr_hwaddr.sa_data, 6);

    close(skfd);

    return 0;

}
static int get_mtu(const char *adapter_name, int *mtu)
{
    struct ifreq ifr;
    const char *ifname = adapter_name;
    int skfd;

    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, ifname);

    *mtu = 0;
    if (ioctl(skfd, SIOCGIFMTU, &ifr) >= 0)
        *mtu = ifr.ifr_mtu;

    close(skfd);
    return 0;
}
static int get_name(char *name[], int *count_adapter)
{
    int numreqs = 30;
    struct ifconf ifc;
    struct ifreq *ifr;
    int n, err = -1;
    int skfd;

    *count_adapter = 0;
    ifc.ifc_buf = NULL;

    /* SIOCGIFCONF currently seems to only work properly on AF_INET sockets
       (as of 2.1.128) */
    skfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (skfd < 0) {
        PRINT_ERR("error: no inet socket available\n");
        return -1;
    }
    for (;;) {
        ifc.ifc_len = sizeof(struct ifreq) * numreqs;
        ifc.ifc_buf = realloc(ifc.ifc_buf, ifc.ifc_len);

        if (ioctl(skfd, SIOCGIFCONF, &ifc) < 0) {
            goto out;
        }
        if (ifc.ifc_len == (int)(sizeof(struct ifreq) * numreqs)) {
            /* assume it overflowed and try again */
            numreqs += 10;
            continue;
        }
        break;
    }

    ifr = ifc.ifc_req;
    for (n = 0; n < ifc.ifc_len; n += sizeof(struct ifreq)) {
        name[*count_adapter] = (char *)malloc(LEN_NAME_ADAPTER * sizeof(char)); 
        strcpy(name[*count_adapter], ifr->ifr_name);
        (*count_adapter)++ ;
//        printf("Sean: mtu[%d]\n",ifr->ifr_ifru.ifru_mtu);
        ifr++;
    }
    err = 0;

out:
    close(skfd);
    free(ifc.ifc_buf);
    return err;

    return 0;
}

