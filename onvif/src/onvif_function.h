/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_function.h
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

#ifndef _ONVIF_FUNCTION_H_
#define _ONVIF_FUNCTION_H_

#include "onvif_common.h"

#define ONVIF_PTZ_PRESET_NAME_PREFIX    "Preset"
#define ONVIF_PTZ_PRESET_TOKEN_PREFIX   "onvif_Preset_token"

typedef struct PtzPreset
{
	int Num;
	char ProfileToken[64];	
	char PresetName[64];	
	char PresetToken[64];
}Preset;

typedef struct ListNode
{
	struct PtzPreset Preset;
	struct ListNode *Next;
}node;

extern int preset_size;
extern node *head;


int netGetIp(const char *pInterface, unsigned int *ip);

int netGetMac(const char *pInterface, unsigned char *pMac);

int netGetNetmask(const char *pInterface, unsigned int *netmask);

/**
 * @brief scope的匹配算法
 *
 * @param client
 * @param server
 *
 * @return 匹配返回true 否则返回false
 */
int compare_match(const char *client, const char *server);

/**
 * @brief 查找User列表中的名字是否匹配
 *
 * @param name
 * @param User
 *
 * @return 找到返回索引值i，未找到返回-1
 */
int find_user(const char *name, struct tt__User **User);

node *Peset_List_Init();

void Set_Pesets();

int Get_Presets();

int Add_Preset(Preset *preset);

int Delete_Preset(Preset *preset);
#endif

