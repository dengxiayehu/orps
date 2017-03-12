#include <xlog.h>
#include <librtmp/rtmp.h>
#include <librtmp/log.h>

#include "rtmp_util.h"

namespace rtmp_common {

void rtmp_log(int level, const char *fmt, va_list args)
{
  if (level == RTMP_LOGDEBUG2)
    return;

  char buf[4096];
  vsnprintf(buf, sizeof(buf)-1, fmt, args);

  switch (level) {
    case RTMP_LOGCRIT:
    case RTMP_LOGERROR:   level = xlog::ERR;  break;
    case RTMP_LOGWARNING: level = xlog::WARN; break;
    case RTMP_LOGINFO:    level = xlog::INFO; break;
    case RTMP_LOGDEBUG:
    case RTMP_LOGDEBUG2:
    default:              level = xlog::DEBUG;break;
  }

  xlog::log_print("rtmpout", "unknown", -1, (xlog::log_level) level, buf);
}

uint8_t pkttyp2channel(uint8_t typ)
{
  if (typ == RTMP_PACKET_TYPE_VIDEO) {
    return RTMP_VIDEO_CHANNEL;
  } else if (typ == RTMP_PACKET_TYPE_AUDIO || typ == RTMP_PACKET_TYPE_INFO) {
    return RTMP_AUDIO_CHANNEL;
  } else {
    return RTMP_SYSTEM_CHANNEL;
  }
}

}
