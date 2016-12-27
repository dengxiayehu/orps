#ifndef _OMX_RTMPSRC_COMPONENT_H_
#define _OMX_RTMPSRC_COMPONENT_H_

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Core.h>
#include <pthread.h>
#include <omx_base_source.h>
#include <string.h>

#define RTMPSRC_COMP_NAME "OMX.st.rtmpsrc"
#define RTMPSRC_COMP_ROLE "rtmpsrc"
#define MAX_RTMPSRC_COMPONENTS 1

DERIVEDCLASS(omx_rtmpsrc_component_PrivateType, omx_base_source_PrivateType)
#define omx_rtmpsrc_component_PrivateType_FIELDS omx_base_source_PrivateType_FIELDS \
  OMX_TIME_CONFIG_TIMESTAMPTYPE   sTimeStamp; \
  OMX_BUFFERHEADERTYPE           *pTmpOutputBuffer; \
  OMX_STRING                      sInputUrl;
ENDCLASS(omx_rtmpsrc_component_PrivateType)

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *openmaxStandComp, OMX_STRING cComponentName);
OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *openmaxStandComp);
OMX_ERRORTYPE omx_rtmpsrc_component_MessageHandler(OMX_COMPONENTTYPE *, internalRequestMessageType *);
OMX_ERRORTYPE omx_rtmpsrc_component_Init(OMX_COMPONENTTYPE *openmaxStandComp);
OMX_ERRORTYPE omx_rtmpsrc_component_Deinit(OMX_COMPONENTTYPE *openmaxStandComp);

#endif /* end of _OMX_RTMPSRC_COMPONENT_H_ */
