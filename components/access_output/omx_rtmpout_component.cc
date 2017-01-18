#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_base_clock_port.h>
#include <omx_rtmpout_component.h>

#include <xmacro.h>
#include <xlog.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1
#define CLOCK_PORT_INDEX 2

static OMX_U32 rtmpout_instance = 0;

OMX_ERRORTYPE omx_rtmpout_component_Constructor(OMX_COMPONENTTYPE *omx_comp, OMX_STRING comp_name)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  omx_rtmpout_component_PrivateType *comp_priv;

  RM_RegisterComponent((OMX_STRING) RTMPOUT_COMP_NAME, MAX_RTMPOUT_COMPONENTS);

  if (!omx_comp->pComponentPrivate) {
    omx_comp->pComponentPrivate = (omx_rtmpout_component_PrivateType *) calloc(1, sizeof(omx_rtmpout_component_PrivateType));
    if (!omx_comp->pComponentPrivate) {
      return OMX_ErrorInsufficientResources;
    }
  }

  comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  comp_priv->ports = NULL;

  omx_err = omx_base_filter_Constructor(omx_comp, comp_name);
  if (omx_err != OMX_ErrorNone) {
    return OMX_ErrorInsufficientResources;
  }

  comp_priv->sPortTypesParam[OMX_PortDomainVideo].nStartPortNumber = VIDEO_PORT_INDEX;
  comp_priv->sPortTypesParam[OMX_PortDomainVideo].nPorts = 1;
  comp_priv->sPortTypesParam[OMX_PortDomainAudio].nStartPortNumber = AUDIO_PORT_INDEX;
  comp_priv->sPortTypesParam[OMX_PortDomainAudio].nPorts = 1;
  comp_priv->sPortTypesParam[OMX_PortDomainOther].nStartPortNumber = CLOCK_PORT_INDEX;
  comp_priv->sPortTypesParam[OMX_PortDomainOther].nPorts = 1;

  if ((comp_priv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
       comp_priv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
       comp_priv->sPortTypesParam[OMX_PortDomainOther].nPorts) &&
      !comp_priv->ports) {
    comp_priv->ports = (omx_base_PortType**) calloc(comp_priv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                                                    comp_priv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                                                    comp_priv->sPortTypesParam[OMX_PortDomainOther].nPorts, sizeof(omx_base_PortType**));
    if (!comp_priv->ports) {
      return OMX_ErrorInsufficientResources;
    }

    comp_priv->ports[VIDEO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!comp_priv->ports[VIDEO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    comp_priv->ports[AUDIO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_audio_PortType));
    if (!comp_priv->ports[AUDIO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    comp_priv->ports[CLOCK_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_clock_PortType));
    if (!comp_priv->ports[AUDIO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
  }

  ++rtmpout_instance;
  if (rtmpout_instance > MAX_RTMPOUT_COMPONENTS) {
    return OMX_ErrorInsufficientResources;
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_Destructor(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_U32 i;

  if (comp_priv->ports) {
    for (i = 0; i < comp_priv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                    comp_priv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                    comp_priv->sPortTypesParam[OMX_PortDomainOther].nPorts; ++i) {
      if (comp_priv->ports[i]) {
        comp_priv->ports[i]->PortDestructor(comp_priv->ports[i]);
        comp_priv->ports[i] = NULL;
      }
    }
    SAFE_FREE(comp_priv->ports);
  }

  --rtmpout_instance;
  return omx_base_filter_Destructor(omx_comp);
}
