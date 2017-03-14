#ifndef _FLAGDEFS_H_
#define _FLAGDEFS_H_

#include <webrtc/base/flags.h>

DEFINE_bool(help, false, "Print this message [dengxiayehu@yeah.net]");
DEFINE_string(src_rtmp, "rtmp://127.0.0.1/live/va", "The source rtmp url to connect to.");
DEFINE_string(dst_rtmp, "rtmp://127.0.0.1/live/xyz", "The destination rtmp url to push to.");

#endif /* end of _FLAGDEFS_H_ */
