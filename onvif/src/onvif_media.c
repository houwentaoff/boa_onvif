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

 /* :TODO:Saturday, July 19, 2014 09:46:00 HKT:SeanHou: PC端避免编译不过 */
#if 0
#include "mw_struct.h"
#include "mw_api.h"
#endif
 /* :TODO:End---  */

int MediaInitHAL()
{
 /* :TODO:Saturday, July 19, 2014 09:46:00 HKT:SeanHou: PC端避免编译不过 */
#if 0
	/*Init HAL*/	
	int i;
	mw_init();
	mw_encode_stream g_mw_stream[MW_MAX_STREAM_NUM];	
	// Get streams settings
	for (i = 0; i < MW_MAX_STREAM_NUM; ++i) {
		g_mw_stream[i].format.stream = i;
		if (mw_get_encode_format(&g_mw_stream[i].format) < 0) {
			return -1;
		}
		g_mw_stream[i].h264.stream = i;
		if (mw_get_h264_config(&g_mw_stream[i].h264) < 0) {
			return -1;
		}
	}
#endif
 /* :TODO:End---  */
	return 0;
}




/*set encoder and resolution*/
int MediaSetResolution(int streamid, int wigth, int height)
{
	int retVal = 0;
 /* :TODO:Saturday, July 19, 2014 09:46:00 HKT:SeanHou: PC端避免编译不过 */
#if 0
	mw_encode_format stFormat;						
	stFormat.stream = streamid;
	mw_get_encode_format(&stFormat);
	stFormat.encode_width = wigth;	
	stFormat.encode_height = height;
	printf("[MediaSetResolution] wigth:%d,height:%d\n",stFormat.encode_width, stFormat.encode_height);
	retVal = mw_set_encode_format(&stFormat);
#endif
 /* :TODO:End---  */
	return retVal;
}


/*set Frame rate*/
int MediaSetFrameRate(int streamid, int value)
{
	int retVal = 0;
 /* :TODO:Saturday, July 19, 2014 09:46:00 HKT:SeanHou: PC端避免编译不过 */
#if 0
	mw_frame_factor stFrame;

	stFrame.id = 1<<streamid;
	stFrame.enc_fps = value;


	printf("[MediaSetFrameRate] id:%d,encfps:%d\n",stFrame.id, stFrame.enc_fps);

	retVal = mw_change_fr(&stFrame);
#endif
 /* :TODO:End---  */

	return retVal;
}

/*set Bit rate*/
int MediaSetBitRate(int streamid, int value)
{
	int retVal = -1;
	retVal = 0;
 /* :TODO:Saturday, July 19, 2014 09:46:00 HKT:SeanHou: PC端避免编译不过 */
#if 0
	mw_h264_config stH264Config;						
	stH264Config.stream = streamid;
	
	mw_get_h264_config(&stH264Config);

	if(stH264Config.brc_mode != MW_CBR_MODE){
		return -1;		
	}

	
	mw_bitrate_range stBitRate;
	stBitRate.id = 1 << streamid;
	stBitRate.max_bps = stH264Config.vbr_max_bps;
	stBitRate.min_bps = value;
	retVal = mw_change_br(&stBitRate);
	
	printf("[MediaSetBitRate] bitrate:%d\n",stBitRate.min_bps);
#endif
 /* :TODO:End---  */
	return retVal;
}

/*set Encoding Interval*/
int MediaSetEncodingInterval(int streamid, int value)
{
	return 0;
}


/*set Quality*/
int MediaSetQuality(int streamid, int value)
{
	return 0;
}

/*set QualitGovLengthy*/
int MediaSetGovLength(int streamid, int value)
{
	return 0;
}

