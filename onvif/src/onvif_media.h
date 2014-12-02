/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_media.h
**
** \version     $Id: onvif_media.h 671 2014-07-16 06:07:45Z zhoulei $
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

#ifndef _ONVIF_MEDIA_H_
#define _ONVIF_MEDIA_H_

/*init HAL*/
int MediaInitHAL();

/*set encoder and resolution*/
int MediaSetResolution(int streamid, int wigth, int height);

/*set Frame rate*/
int MediaSetFrameRate(int streamid, int value);

/*set Bit rate*/
int MediaSetBitRate(int streamid, int value);

/*set Encoding Interval*/
int MediaSetEncodingInterval(int streamid, int value);

/*set Quality*/
int MediaSetQuality(int streamid, int value);

/*set QualitGovLengthy*/
int MediaSetGovLength(int streamid, int value);


#endif
