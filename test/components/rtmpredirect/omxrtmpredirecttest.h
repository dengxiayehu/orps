#ifndef _OMXRTMPREDIRECTTEST_H_
#define _OMXRTMPREDIRECTTEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <OMX_Core.h>
#include <OMX_Component.h>
#include <OMX_Types.h>
#include <tsemaphore.h>

#define VERSIONMAJOR    1
#define VERSIONMINOR    1
#define VERSIONREVISION 0
#define VERSIONSTEP     0

typedef struct AppPrivateType {
  OMX_HANDLETYPE rtmpsrchandle;
  OMX_HANDLETYPE rtmpouthandle;
  tsem_t *rtmpsrc_event_sem;
  tsem_t *rtmpout_event_sem;
  OMX_BOOL bEOS;
} AppPrivateType;

OMX_ERRORTYPE rtmpsrc_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

OMX_ERRORTYPE rtmpout_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMXRTMPREDIRECTTEST_H_ */
