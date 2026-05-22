#ifndef __VOCOBOX_COMMON_H
#define __VOCOBOX_COMMON_H


#define PLUGIN_MANUFACTURER_ID	'vcbx'
#define PLUGIN_MANUFACTURER_NAME	"Vocobox"

#ifndef PLUGIN_VERSION
	#define PLUGIN_VERSION	0x00010003
#endif


/* compatibility shims for Mac OS X 10.2.x SDK */
#ifdef __APPLE_CC__
	#if (MAC_OS_X_VERSION_MAX_ALLOWED <= MAC_OS_X_VERSION_10_2)
		#define cosf	(float)cos
		#define sqrtf	(float)sqrt
		#define powf	(float)pow
		#define expf	(float)exp
		#define sinf	(float)sin
	#endif
#endif


#endif
