#ifndef _OMXRTMPREDIRECTTEST_H_
#define _OMXRTMPREDIRECTTEST_H_

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

#define VERSIONMAJOR    1
#define VERSIONMINOR    1
#define VERSIONREVISION 0
#define VERSIONSTEP     0

#define VIDEO_BUFFER_SIZE (65536)
#define AUDIO_BUFFER_SIZE (65536)

typedef struct appPrivateType {
  OMX_HANDLETYPE rtmpsrchandle;
  OMX_HANDLETYPE rtmpouthandle;
  OMX_HANDLETYPE clocksrchandle;
  OMX_HANDLETYPE videoschdhandle;
  tsem_t *rtmpsrc_event_sem;
  tsem_t *rtmpout_event_sem;
  tsem_t *clocksrc_event_sem;
  tsem_t *videoschd_event_sem;
  OMX_BOOL bEOS;
} appPrivateType;

OMX_ERRORTYPE rtmpsrc_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE rtmpsrc_fillbuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

OMX_ERRORTYPE rtmpout_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE rtmpout_emptybuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

OMX_ERRORTYPE clocksrc_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE clocksrc_fillbuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

OMX_ERRORTYPE videoschd_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE videoschd_fillbuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

OMX_ERRORTYPE videoschd_emptybuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMXRTMPREDIRECTTEST_H_ */
