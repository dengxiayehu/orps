#ifndef _OMXRTMPSRCTEST_H_
#define _OMXRTMPSRCTEST_H_

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

extern "C" {
#include <tsemaphore.h>
}
#include <user_debug_levels.h>

typedef struct appPrivateType {
  tsem_t *rtmpsrcEventSem;
  tsem_t *clockEventSem;
  tsem_t *videoschdEventSem;
  tsem_t *eofSem;
  OMX_HANDLETYPE rtmpsrchandle;
  OMX_HANDLETYPE clockhandle;
  OMX_HANDLETYPE videoschdhandle;
} appPrivateType;

#define VERSIONMAJOR    1
#define VERSIONMINOR    1
#define VERSIONREVISION 0
#define VERSIONSTEP     0

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

OMX_ERRORTYPE clocksrcEventHandler(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_EVENTTYPE eEvent,
    OMX_OUT OMX_U32 Data1,
    OMX_OUT OMX_U32 Data2,
    OMX_OUT OMX_PTR pEventData);

OMX_ERRORTYPE clocksrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE *pBuffer);

#endif /* end of _OMXRTMPSRCTEST_H_ */
