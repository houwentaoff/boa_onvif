/*!
*****************************************************************************
** \file        packages/onvif/src/onvif_imaging.c
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

//#include "mw_struct.h"
//#include "mw_api.h"


#include "onvif_function.h"

#define NO_HARDWARE  

/****************************************************************
	macro 
******************************************************************/
#define IMAGING_OK  0 
#define	DIV_ROUND(divident, divider)    (((divident)+((divider)>>1)) / (divider))

/****************************************************************
	static data 
******************************************************************/

static int blcMode = 1; /*means: enable backlight compensation defualt*/
static int aeMode  = 1; /*means: enable auto exposure defualt*/
static int whiteBlanceMode = 1; /*means: enable auto white balance defualt*/
extern int fd_iav;


/****************************************************************
	functions
******************************************************************/
/*init*/
int imagingInit(void)
{	
	#if 0
	if ((fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) 
	{
		perror("open /dev/iav");
		return -1;
	}
	#endif

#ifndef NO_HARDWARE
	if (mw_start_aaa(fd_iav) < 0) 
	{
		perror("mw_start_aaa");
		return -1;
	}
	
	mw_enable_ae(aeMode);
	
	mw_enable_awb(whiteBlanceMode);
	mw_set_white_balance_mode(MW_WB_AUTO);
#endif

	return IMAGING_OK;
}
int imagingExit(void)
{	
#ifndef NO_HARDWARE
	if (mw_stop_aaa() < 0)
	{
		perror("mw_stop_aaa");
		return -1;
	}
#endif
	
	return IMAGING_OK;
}

/*BLC:0-disable, 1-enable*/
int imagingGetBLCMode(void)
{
	return blcMode;
}

int imagingSetBLCMode(int mode)
{
	int	retVal = 0;
#ifndef NO_HARDWARE
	/*0-disable, 1-enable*/
	retVal = mw_enable_backlight_compensation(mode); 

	if(retVal != 0)
	{
		printf("mw_enable_backlight_compensation error:%d\n", retVal);
		return retVal;
	}
	blcMode = mode;
#endif
	return IMAGING_OK;
}

/*Brightnes: valid range is: -255 - +255*/
int imagingGetBrightness(void)
{
    int brightness = 0;
	
#ifndef NO_HARDWARE
	mw_get_brightness(&brightness);
#endif
	return brightness;
}

int imagingSetBrightness(int brightness)
{
#ifndef NO_HARDWARE
	return mw_set_brightness(brightness);
#endif
    return 0;
}

/*ColorSaturation: unit = 64,valid range is: 0 ~ +255*/
int imagingGetColorSaturation(void)
{
    int saturation = 0;

#ifndef NO_HARDWARE
	mw_get_saturation(&saturation);
#endif
	return saturation;
}

int imagingSetColorSaturation(int saturation)
{
#ifndef NO_HARDWARE
	return mw_set_saturation(saturation);
#endif
    return 0;
}

/*Contrast: unit = 64, valid range is:  0 ~ +128*/
int imagingGetContrast(void)
{
    int contrast = 0;

#ifndef NO_HARDWARE
	mw_get_contrast(&contrast);
#endif
	return contrast;
}

int imagingSetContrast(int contrast)
{
#ifndef NO_HARDWARE
	return mw_set_contrast(contrast);
#endif
    return 0;
}

/*sharpness: unit in 128, 256 is 2X; valid range is 0 ~ +255*/
int imagingGetSharpness(void)
{
    int sharpness = 0;
#ifndef NO_HARDWARE
	mw_get_sharpness(&sharpness);
#endif
	
	return sharpness;
}

int imagingSetSharpness(int sharpness)
{
#ifndef NO_HARDWARE
	return mw_set_sharpness(sharpness);
#endif
    return 0;
}

/*Exposure setting*/
/*Mode:0-disable, 1-enable*/
int imagingGetExposureMode(void)
{
	return aeMode;
}
int imagingSetExposureMode(int mode)
{
	int	retVal = 0;

#ifndef NO_HARDWARE
	retVal = mw_enable_ae(mode); 

	if(retVal != 0)
	{
		printf("mw_enable_ae error:%d\n", retVal);
		return retVal;
	}
	aeMode = mode;
#endif
	return IMAGING_OK;
}

/*Auto exposure shutter time min*/
int imagingGetAEShutterTimeMin(void)
{
	return IMAGING_OK;
}
int imagingSetAEShutterTimeMin(int mode)
{
	return IMAGING_OK;
}

/*Auto exposure shutter time min*/
int imagingGetAEShutterTimeMax(void)
{
	return IMAGING_OK;
}
int imagingSetAEShutterTimeMax(int mode)
{
	return IMAGING_OK;
}
/*Auto exposure sensor gain max*/
/*new AE sensor gain(db): range 0 ~ 60*/
int imagingGetAEGainMax(int *gainMax)
{
	int retVal = 0;
#ifndef NO_HARDWARE
	mw_ae_param aeParams;

	retVal = mw_get_ae_param(&aeParams);
	printf("Current sensor gain max is %d .\n", aeParams.sensor_gain_max);
	*gainMax = aeParams.sensor_gain_max;
#endif
	
	return retVal;
}
int imagingSetAEGainMax(int gainMax)
{
	int retVal = 0;
#ifndef NO_HARDWARE
	mw_ae_param aeParams;

	mw_get_ae_param(&aeParams);
	printf("Current sensor gain max is %d .\n", aeParams.sensor_gain_max);	
	printf("New sensor gain max is %d .\n", gainMax);
	aeParams.sensor_gain_max = gainMax;
	retVal = mw_set_ae_param(&aeParams);
#endif

	return retVal;
}

/*Manual exposure exposuretime*/
int imagingGetMEShutterTime(void)
{
	return IMAGING_OK;
}
int imagingSetMEShutterTime(int shutter)
{
	return IMAGING_OK;
}

/*Manual exposure gain(ISO)*/
int imagingGetMEGain(int *gain)
{
	int fd_iav = 0;
	int retVal = 0;

#ifndef NO_HARDWARE
	// open the iav device
	if ((fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) 
	{
	    printf("-------------\n");
		perror("/dev/iav");
		return -1;
	}

	retVal = mw_get_sensor_gain(fd_iav, gain);
	
	printf("+++++++++retVal=%d\n",retVal);
	close(fd_iav);
#endif
	return retVal;
}
int imagingSetMEGain(int gain)
{
	int fd_iav = 0;
	int retVal = 0;

#ifndef NO_HARDWARE
	// open the iav device
	if ((fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) 
	{
		perror("/dev/iav");
		return -1;
	}

	retVal = mw_set_sensor_gain(fd_iav, gain);
	close(fd_iav);
#endif
	return retVal;

}

/*Manual exposure iris*/
/*Manual exposure iris*/


/*WhiteBalance*/
/*Mode:0-disable, 1-enable*/
int imagingGetWhiteBalanceMode(void)
{
	return whiteBlanceMode;
}
int imagingSetWhiteBalanceMode(int mode)
{
	int	retVal = 0;

#ifndef NO_HARDWARE
	retVal = mw_enable_awb(mode); 

	if(retVal != 0)
	{
		printf("mw_enable_awb error:%d\n", retVal);
		return retVal;
	}
	whiteBlanceMode = mode;
#endif
	return IMAGING_OK;
}

int imagingGetWhiteBalanceRgain(int *gain)
{
	int retVal   = 0;
#ifndef NO_HARDWARE
	mw_wb_gain wbGain;
	
	retVal = mw_get_rgb_gain(&wbGain);

	printf("mw_get_rgb_gain: retval=%d,wbGain.r_gain=%d\n",retVal, wbGain.r_gain);

	*gain = wbGain.r_gain;
#endif
	
	return retVal;
}

int imagingGetWhiteBalanceBgain(int *gain)
{
	int retVal   = 0;
#ifndef NO_HARDWARE
	mw_wb_gain wbGain;
	
	retVal = mw_get_rgb_gain(&wbGain);

	printf("mw_get_rgb_gain: retval=%d,wbGain.b_gain=%d\n",retVal,wbGain.b_gain);

	*gain = wbGain.b_gain;
#endif
	
	return retVal;
}

int imagingSetWhiteBalanceGain(int rgain, int bgain)
{
	int retVal   = 0;
#ifndef NO_HARDWARE
	mw_wb_gain wbGain;
	
	mw_get_rgb_gain(&wbGain);
	printf("Current rgb gain is %d,%d,%d\n", wbGain.r_gain, wbGain.g_gain, wbGain.b_gain);

	wbGain.r_gain = rgain;
	wbGain.b_gain = bgain;
	wbGain.d_gain = 1024;
	retVal  = mw_set_rgb_gain(fd_iav, &wbGain);
#endif

    return retVal;
}



