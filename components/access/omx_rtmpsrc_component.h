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
  OMX_BUFFERHEADERTYPE *pTmpOutputBuffer; \
  OMX_STRING sInputUrl; \
  RTMP *pRTMP;
ENDCLASS(omx_rtmpsrc_component_PrivateType)

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *openmaxStandComp, OMX_STRING cComponentName);
OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *openmaxStandComp);
OMX_ERRORTYPE omx_rtmpsrc_component_MessageHandler(OMX_COMPONENTTYPE *, internalRequestMessageType *);
OMX_ERRORTYPE omx_rtmpsrc_component_Init(OMX_COMPONENTTYPE *openmaxStandComp);
OMX_ERRORTYPE omx_rtmpsrc_component_Deinit(OMX_COMPONENTTYPE *openmaxStandComp);

void omx_rtmpsrc_component_BufferMgmtCallback(
    OMX_COMPONENTTYPE *openmaxStandComp,
    OMX_BUFFERHEADERTYPE *pOutputBuffer);

OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR ComponentParameterStructure);

OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR ComponentParameterStructure);

OMX_ERRORTYPE omx_rtmpsrc_component_GetConfig(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nIndex,
    OMX_IN OMX_PTR pComponentConfigStructure);

OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *pIndexType);

#ifdef __cplusplus
}
#endif

#endif /* end of _OMX_RTMPSRC_COMPONENT_H_ */
