#ifndef _OMX_RTMPOUT_COMPONENT_H_
#define _OMX_RTMPOUT_COMPONENT_H_

#ifdef _cplusplus
extern "C" {
#endif

#include <OMX_Types.h>
#include <OMX_Component.h>
#include <OMX_Core.h>
#include <omx_base_filter.h>

#define RTMPOUT_COMP_NAME "OMX.st.rtmpout"
#define RTMPOUT_COMP_ROLE "rtmpout"
#define MAX_RTMPOUT_COMPONENTS 1

DERIVEDCLASS(omx_rtmpout_component_PrivateType, omx_base_filter_PrivateType)
#define omx_rtmpout_component_PrivateType_FIELDS omx_base_filter_PrivateType_FIELDS \
  OMX_TIME_CLOCKSTATE clk_state;
ENDCLASS(omx_rtmpout_component_PrivateType)

OMX_ERRORTYPE omx_rtmpout_component_Constructor(OMX_COMPONENTTYPE *omx_comp, OMX_STRING comp_name);
OMX_ERRORTYPE omx_rtmpout_component_Destructor(OMX_COMPONENTTYPE *omx_comp);

#ifdef _cplusplus
}
#endif

#endif /* end of _OMX_RTMPOUT_COMPONENT_H_ */
