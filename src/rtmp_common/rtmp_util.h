#ifndef _RTMP_UTIL_H_
#define _RTMP_UTIL_H_

#include <stdint.h>
#include <stdarg.h>

namespace rtmp_common {

void rtmp_log(int level, const char *fmt, va_list args);

enum RTMPChannel {
  RTMP_NETWORK_CHANNEL = 2,
  RTMP_SYSTEM_CHANNEL,
  RTMP_AUDIO_CHANNEL,
  RTMP_VIDEO_CHANNEL   = 6,
  RTMP_SOURCE_CHANNEL  = 8,
}; 
uint8_t pkttyp2channel(uint8_t typ);

}

#endif /* end of _RTMP_UTIL_H_ */
