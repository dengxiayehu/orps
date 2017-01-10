#ifndef _OMXRTMPSRCTEST_H_
#define _OMXRTMPSRCTEST_H_

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

#define BUFFER_OUT_SIZE (640*480*3)

typedef struct appPrivateType {
  tsem_t *rtmpsrcEventSem;
  tsem_t *eofSem;
  OMX_HANDLETYPE rtmpsrchandle;
  OMX_BUFFERHEADERTYPE *outBufferRtmpsrcVideo[2], *outBufferRtmpsrcAudio[2];
  OMX_BOOL bEOS;
} appPrivateType;

OMX_ERRORTYPE rtmpsrcEventHandler(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_EVENTTYPE eEvent,
    OMX_OUT OMX_U32 Data1,
    OMX_OUT OMX_U32 Data2,
    OMX_OUT OMX_PTR pEventData);

OMX_ERRORTYPE rtmpsrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE *pBuffer);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMXRTMPSRCTEST_H_ */
