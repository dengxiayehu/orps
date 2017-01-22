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

#define BUFFER_OUT_SIZE (640*360*3)

typedef struct appPrivateType {
  OMX_HANDLETYPE rtmpouthandle;
  tsem_t *rtmpout_event_sem;
  OMX_BUFFERHEADERTYPE *inbuffer_video[2], *inbuffer_audio[2];
  OMX_BOOL bEOS;
} appPrivateType;

OMX_ERRORTYPE rtmpoutEventHandler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE rtmpoutEmptyBufferDone(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMXRTMPOUTTEST_H_ */
