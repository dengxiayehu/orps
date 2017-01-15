#ifndef _OMX_RTMPSRC_COMPONENT_H_
#define _OMX_RTMPSRC_COMPONENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Core.h>
#include <pthread.h>
#include <omx_base_source.h>
#include <string.h>

#include <librtmp/rtmp.h>

#define RTMPSRC_COMP_NAME "OMX.st.rtmpsrc"
#define RTMPSRC_COMP_ROLE "rtmpsrc"
#define MAX_RTMPSRC_COMPONENTS 1

DERIVEDCLASS(omx_rtmpsrc_component_PrivateType, omx_base_source_PrivateType)
#define omx_rtmpsrc_component_PrivateType_FIELDS omx_base_source_PrivateType_FIELDS \
  OMX_BUFFERHEADERTYPE *tmp_output_buffer; \
  OMX_STRING input_url; \
  RTMP *rtmp; \
  OMX_VIDEO_CODINGTYPE video_codec; \
  OMX_AUDIO_CODINGTYPE audio_codec; \
  OMX_BOOL rtmp_ready; \
  tsem_t *rtmp_sync_sem; \
  OMX_BOOL first_timestamp_flag[2];
ENDCLASS(omx_rtmpsrc_component_PrivateType)

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *omx_comp, OMX_STRING comp_name);
OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *omx_comp);
OMX_ERRORTYPE omx_rtmpsrc_component_MessageHandler(OMX_COMPONENTTYPE *, internalRequestMessageType *);
OMX_ERRORTYPE omx_rtmpsrc_component_Init(OMX_COMPONENTTYPE *omx_comp);
OMX_ERRORTYPE omx_rtmpsrc_component_Deinit(OMX_COMPONENTTYPE *omx_comp);

void omx_rtmpsrc_component_BufferMgmtCallback(
    OMX_COMPONENTTYPE *omx_comp,
    OMX_BUFFERHEADERTYPE *output_buffer);

OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR comp_parm);

OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR comp_parm);

OMX_ERRORTYPE omx_rtmpsrc_component_GetConfig(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE index,
    OMX_IN OMX_PTR comp_param);

OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *index);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMX_RTMPSRC_COMPONENT_H_ */
