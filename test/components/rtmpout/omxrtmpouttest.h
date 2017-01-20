#ifndef _OMXRTMPOUTTEST_H_
#define _OMXRTMPOUTTEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <ctype.h>

#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OMX_Types.h>
#include <OMX_Video.h>
#include <OMX_Audio.h>

#include <tsemaphore.h>
#include <user_debug_levels.h>

#define VERSIONMAJOR    1
#define VERSIONMINOR    1
#define VERSIONREVISION 0
#define VERSIONSTEP     0

typedef struct appPrivateType {
  OMX_HANDLETYPE rtmpouthandle;
  OMX_BOOL bEOS;
} appPrivateType;

#ifdef __cplusplus
}
#endif

#endif /* end of _OMXRTMPOUTTEST_H_ */