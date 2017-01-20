#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_rtmpout_component.h>

#include <xmacro.h>
#include <xlog.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1

#define DEFAULT_OUT_URL_LENGTH 2048

static OMX_U32 rtmpout_instance = 0;

OMX_ERRORTYPE omx_rtmpout_component_Constructor(OMX_COMPONENTTYPE *omx_comp, OMX_STRING comp_name)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  omx_rtmpout_component_PrivateType *comp_priv;
  omx_base_video_PortType *port_v;
  omx_base_audio_PortType *port_a;

  RM_RegisterComponent((OMX_STRING) RTMPOUT_COMP_NAME, MAX_RTMPOUT_COMPONENTS);

  if (!omx_comp->pComponentPrivate) {
    omx_comp->pComponentPrivate = (omx_rtmpout_component_PrivateType *) calloc(1, sizeof(omx_rtmpout_component_PrivateType));
    if (!omx_comp->pComponentPrivate) {
      return OMX_ErrorInsufficientResources;
    }
  }

  comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  comp_priv->ports = NULL;

  omx_err = omx_base_sink_Constructor(omx_comp, comp_name);
  if (omx_err != OMX_ErrorNone) {
    return OMX_ErrorInsufficientResources;
  }

  comp_priv->sPortTypesParam[OMX_PortDomainVideo].nStartPortNumber = VIDEO_PORT_INDEX;
  comp_priv->sPortTypesParam[OMX_PortDomainVideo].nPorts = 1;
  comp_priv->sPortTypesParam[OMX_PortDomainAudio].nStartPortNumber = AUDIO_PORT_INDEX;
  comp_priv->sPortTypesParam[OMX_PortDomainAudio].nPorts = 1;

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
  }

  comp_priv->ports[VIDEO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
  if (!comp_priv->ports[VIDEO_PORT_INDEX]) {
    return OMX_ErrorInsufficientResources;
  }
  comp_priv->ports[AUDIO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_audio_PortType));
  if (!comp_priv->ports[AUDIO_PORT_INDEX]) {
    return OMX_ErrorInsufficientResources;
  }

  base_video_port_Constructor(omx_comp, &comp_priv->ports[VIDEO_PORT_INDEX], VIDEO_PORT_INDEX, OMX_TRUE);
  base_audio_port_Constructor(omx_comp, &comp_priv->ports[AUDIO_PORT_INDEX], AUDIO_PORT_INDEX, OMX_TRUE);

  port_v = (omx_base_video_PortType *) comp_priv->ports[VIDEO_PORT_INDEX];
  port_a = (omx_base_audio_PortType *) comp_priv->ports[AUDIO_PORT_INDEX];

  port_v->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;
  port_a->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;

  comp_priv->BufferMgmtCallback = omx_rtmpout_component_BufferMgmtCallback;
  comp_priv->BufferMgmtFunction = omx_base_sink_twoport_BufferMgmtFunction;

  comp_priv->destructor = omx_rtmpout_component_Destructor;
  comp_priv->messageHandler = omx_rtmpout_component_MessageHandler;

  ++rtmpout_instance;
  if (rtmpout_instance > MAX_RTMPOUT_COMPONENTS) {
    return OMX_ErrorInsufficientResources;
  }

  omx_comp->SetParameter = omx_rtmpout_component_SetParameter;
  omx_comp->GetParameter = omx_rtmpout_component_GetParameter;
  omx_comp->GetExtensionIndex = omx_rtmpout_component_GetExtensionIndex;

  comp_priv->output_url = (OMX_STRING) malloc(DEFAULT_OUT_URL_LENGTH);
  if (!comp_priv->output_url) {
    LOGE("malloc for output_url failed: %s", ERRNOMSG);
    return OMX_ErrorInsufficientResources;
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_Destructor(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_U32 i;

  SAFE_FREE(comp_priv->output_url);

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
  return omx_base_sink_Destructor(omx_comp);
}

void omx_rtmpout_component_BufferMgmtCallback(
    OMX_COMPONENTTYPE *omx_comp,
    OMX_BUFFERHEADERTYPE *input_buffer)
{
  input_buffer->nFilledLen = 0;
  input_buffer->nOffset = 0;
}

OMX_ERRORTYPE omx_rtmpout_component_MessageHandler(OMX_COMPONENTTYPE *omx_comp, internalRequestMessageType *message)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;

  omx_err = omx_base_component_MessageHandler(omx_comp, message);
  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE param_index,
    OMX_IN OMX_PTR comp_param)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_COMPONENTTYPE *omx_comp = (OMX_COMPONENTTYPE *) hcomp;
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  int output_url_length;

  if (!comp_param) {
    return OMX_ErrorBadParameter;
  }

  LOGI("Setting parameter %d", param_index);

  switch ((int) param_index) {
  case OMX_IndexVendorOutputUrl:
    output_url_length = strlen((OMX_STRING) comp_param) + 1;
    if (output_url_length > DEFAULT_OUT_URL_LENGTH) {
      SAFE_FREE(comp_priv->output_url);
      comp_priv->output_url = (OMX_STRING) malloc(output_url_length);
    }
    strcpy(comp_priv->output_url, (OMX_STRING) comp_param);
    break;
  default:
    omx_err = omx_base_component_SetParameter(hcomp, param_index, comp_param);
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE param_index,
    OMX_INOUT OMX_PTR comp_param)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_COMPONENTTYPE *omx_comp = (OMX_COMPONENTTYPE *) hcomp;
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;

  if (!comp_param) {
    return OMX_ErrorBadParameter;
  }

  LOGI("Getting parameter %d", param_index);

  switch ((int) param_index) {
  case OMX_IndexVendorOutputUrl:
    strcpy((OMX_STRING) comp_param, comp_priv->output_url);
    break;
  default:
    omx_err = omx_base_component_GetParameter(hcomp, param_index, comp_param);
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_STRING param_name,
    OMX_OUT OMX_INDEXTYPE *index)
{
  LOGI("Getting extension index %s", param_name);

  if (!strcmp(param_name, "OMX.ST.index.param.outputurl")) {
    *index = (OMX_INDEXTYPE) OMX_IndexVendorOutputUrl;
  } else {
    return OMX_ErrorBadParameter;
  }
  return OMX_ErrorNone;
}
