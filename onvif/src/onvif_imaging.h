/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_imaging.h
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

#ifndef _ONVIF_IMAGING_H_
#define _ONVIF_IMAGING_H_
#if 0
/*BLC*/
int imagingGetBLCMode(void);
int imagingSetBLCMode(int backlight_enable);

/*Brightness*/
int imagingGetBrightness(void);
int imagingSetBrightness(int brightness);

/*Color Saturation*/
int imagingGetColorSaturation(void);
int imagingSetColorSaturation(int saturation);

/*Contrast*/
int imagingGetContrast(void);
int imagingSetContrast(int contrast);

/*sharpness*/
int imagingGetSharpness(void);
int imagingSetSharpness(int sharpness);

/*Auto exposure mode: disable/enable*/
int imagingGetExposureMode(void);
int imagingSetExposureMode(int mode);

/*Auto exposure shutter time min*/
//int imagingGetAEShutterTimeMin(int *shutterMin);
int imagingSetAEShutterTimeMin(int shutterMin);

/*Auto exposure shutter time min*/
//int imagingGetAEShutterTimeMax(int *shutterMax);
int imagingSetAEShutterTimeMax(int shutterMax);

/*Auto exposure sensor gain max*/
//int imagingGetAEGainMax(int *gainMax);
int imagingSetAEGainMax(int gainMax);

/*Manual exposure exposuretime*/
//int imagingGetMEShutterTime(int *shutter);
int imagingSetMEShutterTime(int shutter);

/*Manual exposure gain(ISO)*/
//int imagingGetMEGain(int *gain);
int imagingSetMEGain(int gain);

/*WhiteBalance*/
int imagingGetWhiteBalanceMode(void);
int imagingSetWhiteBalanceMode(int mode);
int imagingGetWhiteBalanceRgain(int *gain);
int imagingGetWhiteBalanceBgain(int *gain);
int imagingSetWhiteBalanceGain(int rgain, int bgain);
#endif
#endif

