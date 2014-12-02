/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_function.c
**
** \version     $Id$
**
** \brief       Helper function for onvif.
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2014 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/

#if 0
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/route.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
//#include "include.h"
#include "onvif_function.h"

#define PTZPRESETINFORMATION            "/home/onvif_ptz_preset.cfg"

int find_user(const char *name, struct tt__User **User)
{
    const char *username = name;
    int count = g_GkIpc_OnvifInf.Usercount;
    int index=0;

    if (NULL == name || (NULL == User))
    {
        return -2;
    }
    while(index<count)
    {
       if (0 == strcmp(User[index]->Username, username))
       {
           return index;
       }
       index++;
    }
    if (index == count)
        return -1;
    return -3;
}

int compare_match(const char *client, const char *server)
{
    const char *p = client;
    const char *s = server;

    while (*p!='\0' && *s!='\0')
    {
        if (*p != *s)
        {
            break;
        }
        p++;
        s++;
    }
    if (*p == '\0' && (*s == '/' || *s == '\0'))
        return true;
    else
        return false;
}

int netGetMac(const char *pInterface, unsigned char *pMac)
{
	struct ifreq ifreq;
	int sockfd = 0;
	unsigned char mac[6] = {0};

	if((NULL == pInterface) || (NULL == pMac))
	{
		printf("get ip:  == NULL\r\n");
		return -1;
	}

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("netGetMac socket");
		return -1;
	}

	strcpy(ifreq.ifr_name, pInterface);

	if(ioctl(sockfd, SIOCGIFHWADDR, &ifreq) < 0)
	{
		perror("netGetMac ioctl");
		close(sockfd);
		return -2;
	}

	memcpy(mac, ifreq.ifr_hwaddr.sa_data, 6);
//	printf("MAC:%02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
	if(pMac != NULL)
	{
		memcpy(pMac, mac, 6);
	}

	close(sockfd);

	return 0;
}


int netGetIp(const char *pInterface, unsigned int *ip)
{
	int sock = 0;
	struct ifreq ifr;

	if((pInterface == NULL) || (NULL == ip))
	{
		printf("get ip:  == NULL\r\n");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, pInterface, IFNAMSIZ);
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock <= 0)
	{
		printf("get ip: sock error, %s\r\n", strerror(errno));
		return -1;
	}

	((struct sockaddr_in*)&ifr.ifr_addr)->sin_family = PF_INET;
	if(ioctl(sock, SIOCGIFADDR, &ifr) < 0)
	{
		printf("get ip error: %s\r\n", strerror(errno));
		close(sock);
		return -1;
	}
	else
	{
		*ip = ((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr.s_addr;
		printf("get ip(%d:%d:%d:%d) success!\r\n", (*ip)&0xff, (*ip>>8)&0xff, (*ip>>16)&0xff, (*ip>>24)&0xff);
	}
	close(sock);

	return 0;
}

int netGetNetmask(const char *pInterface, unsigned int *netmask)
{
	struct ifreq ifr;
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if (NULL == netmask || NULL == pInterface)
    {
        perror("netmask is NULL");
		return -1;
    }

	strcpy(ifr.ifr_name, pInterface);

 	if(ioctl(sock, SIOCGIFNETMASK, &ifr) < 0)
	{
        perror("get mask error!");
		close(sock);
		return -1;
	}
    else
    {
        *netmask = *(unsigned int *)&ifr.ifr_netmask.sa_data[2];
    }

	close(sock);

	return 0;
}

node *Peset_List_Init()
{
	node *h;

	h = (node*)malloc(sizeof(node));
	memset(h, 0, sizeof(node));

	return h;
}

void Set_Pesets()
{
 	FILE *fp;
	node *p;
	
 	if((fp = fopen(PTZPRESETINFORMATION, "w")) == NULL) {
 		printf("error: Open ptz preset config file failed\n");
 		return;
 	}
	
 	p = head;
 	while(NULL != p->Next) {
		fwrite(&p->Next->Preset, sizeof(Preset), 1, fp);
 		p = p->Next;
 	}
	
	fclose(fp);
 	printf("\nsave %s succeeded\n", PTZPRESETINFORMATION);
	return;
}

int Get_Presets()
{
	FILE *fp;
	node *p;
	node *pt;
	int presetSize = 0;

	if((fp = fopen(PTZPRESETINFORMATION, "r")) == NULL) {
 		printf("error: Open ptz preset config file failed\n");
 		return -1;
 	}
	
	p = head;

	while(!feof(fp)) {
		pt = (node *)malloc(sizeof(node));
		if(fread(&pt->Preset, sizeof(Preset), 1, fp) == 0) {
			free(pt);
			break;
		}
		p->Next = pt;
		p = pt;
		p->Next = NULL;
		printf("%d\t%s\t%s\t%s\n", p->Preset.Num, p->Preset.ProfileToken ,p->Preset.PresetToken, p->Preset.PresetName);
		presetSize++;
	}
	
	fclose(fp);
	return presetSize;
}

node *Check_Preset_Num(Preset *preset) 
{
	node *p;

	p = head->Next;
	
	while (NULL != p) {
		if(p->Preset.Num == preset->Num) {
			printf("The preset already exists\n");
			return p;
		}
		p = p->Next;
	}
	
	return NULL;
}

int Add_Preset(Preset *preset)
{
	node *p;
	node *pst;
	node *pt;
	int flag = 0;

	if((p = Check_Preset_Num(preset)) != NULL) {
		if(strcmp(p->Preset.ProfileToken, preset->ProfileToken) != 0) {
			memcpy(p->Preset.ProfileToken, preset->ProfileToken, sizeof(preset->ProfileToken));
			flag++;
		}
		if(strcmp(p->Preset.PresetName, preset->PresetName) != 0) {
			memcpy(p->Preset.PresetName, preset->PresetName, sizeof(preset->PresetName));
			flag++;
		}
		if(strcmp(p->Preset.PresetToken, preset->PresetToken) != 0) {
			memcpy(p->Preset.PresetToken, preset->PresetToken, sizeof(preset->PresetToken));
			flag++;
		}
		if(flag) {
			printf("Num[%d] preset info modified\n", preset->Num);
			return 0;
		}

		return 1;
	}

	pst = (node *)malloc(sizeof(node));
	memcpy(&pst->Preset, preset, sizeof(Preset));
	p = head;
	
	while(NULL != p->Next) { 
		if(preset->Num < p->Next->Preset.Num) {
			pt = p->Next;
			p->Next = pst;
			pst->Next = pt;
			break;
		}
		p = p->Next;
	}
	if(NULL == p->Next) {
		p->Next = pst;
		pst->Next = NULL;
	}

	return 0;
}

int Delete_Preset(Preset *preset)
{ 
	node *p;
	node *pt;

	p = head;
	while(NULL != p->Next) {
		if(preset->Num == p->Next->Preset.Num) {
			pt = p->Next;
			p->Next = p->Next->Next;
			free(pt);
			return 0;
		}
		p = p->Next;
	}

	printf("The preset does not exists");	
	return 1;
}

