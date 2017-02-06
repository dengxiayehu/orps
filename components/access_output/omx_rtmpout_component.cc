#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_rtmpout_component.h>

#include <orps_config.h>
#include <xmacro.h>
#include <xlog.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1

#define DEFAULT_OUT_URL_LENGTH 2048

#define VIDEO_BUFFER_SIZE 150000
#define AUDIO_BUFFER_SIZE 65536

static OMX_U32 rtmpout_instance = 0;

static void rtmp_log(int level, const char *fmt, va_list args);

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

  port_v->sPortParam.nBufferSize = VIDEO_BUFFER_SIZE;
  port_v->Port_SendBufferFunction = omx_rtmpout_component_port_SendBufferFunction;
  port_a->sPortParam.nBufferSize = AUDIO_BUFFER_SIZE;
  port_a->Port_SendBufferFunction = omx_rtmpout_component_port_SendBufferFunction;

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

  comp_priv->rtmp_ready = OMX_FALSE;
  if (!comp_priv->rtmp_sync_sem) {
    comp_priv->rtmp_sync_sem = (tsem_t *) calloc(1, sizeof(tsem_t));
    if (!comp_priv->rtmp_sync_sem) {
      return OMX_ErrorInsufficientResources;
    }
    tsem_init(comp_priv->rtmp_sync_sem, 0);
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_Destructor(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_U32 i;

  if (comp_priv->rtmp_sync_sem) {
    tsem_deinit(comp_priv->rtmp_sync_sem);
    SAFE_FREE(comp_priv->rtmp_sync_sem);
  }

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
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;

  if (!comp_priv->rtmp_ready) {
    if (comp_priv->state == OMX_StateExecuting) {
      tsem_down(comp_priv->rtmp_sync_sem);
    } else {
      return;
    }
  }

  OMX_U32 port_index = input_buffer->nInputPortIndex;
  if (port_index == VIDEO_PORT_INDEX) {
    LOGD("Got video frame");
  } else if (port_index == AUDIO_PORT_INDEX) {
    LOGD("Got audio frame");
  }

  input_buffer->nFilledLen = 0;
  input_buffer->nOffset = 0;
}

OMX_ERRORTYPE omx_rtmpout_component_MessageHandler(OMX_COMPONENTTYPE *omx_comp, internalRequestMessageType *message)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_STATETYPE old_state = comp_priv->state;

  omx_err = omx_base_component_MessageHandler(omx_comp, message);
  if (omx_err != OMX_ErrorNone) {
    return omx_err;
  }

  if (message->messageType == OMX_CommandStateSet) {
    if ((message->messageParam == OMX_StateExecuting) && (old_state == OMX_StateIdle)) {
      omx_err = omx_rtmpout_component_Init(omx_comp);
    } else if ((message->messageParam == OMX_StateIdle) && (old_state == OMX_StateExecuting)) {
      omx_err = omx_rtmpout_component_Deinit(omx_comp);
    }
  }

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
  omx_base_video_PortType *video_port = (omx_base_video_PortType *) comp_priv->ports[OMX_BASE_SINK_INPUTPORT_INDEX];
  omx_base_audio_PortType *audio_port = (omx_base_audio_PortType *) comp_priv->ports[OMX_BASE_SINK_INPUTPORT_INDEX_1];
  OMX_VIDEO_PARAM_PORTFORMATTYPE *video_port_format;
  OMX_AUDIO_PARAM_PORTFORMATTYPE *audio_port_format;
  OMX_U32 port_index;
  int output_url_length;

  if (!comp_param) {
    return OMX_ErrorBadParameter;
  }

  LOGI("Setting parameter %d", param_index);

  switch ((int) param_index) {
  case OMX_IndexParamVideoPortFormat:
    video_port_format = (OMX_VIDEO_PARAM_PORTFORMATTYPE *) comp_param;
    port_index = video_port_format->nPortIndex;
    omx_err = omx_base_component_ParameterSanityCheck(hcomp, port_index, video_port_format, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
    if (omx_err != OMX_ErrorNone) {
      LOGE("Parameter check error=%x", omx_err);
      break;
    }
    if (port_index < 1) {
      memcpy(&video_port->sVideoParam, video_port_format, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
    } else {
      omx_err = OMX_ErrorBadPortIndex;
    }
    break;
  case OMX_IndexParamAudioPortFormat:
    audio_port_format = (OMX_AUDIO_PARAM_PORTFORMATTYPE *) comp_param;
    port_index = audio_port_format->nPortIndex;
    omx_err = omx_base_component_ParameterSanityCheck(hcomp, port_index, audio_port_format, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
    if (omx_err != OMX_ErrorNone) {
      LOGE("Parameter check error=%x", omx_err);
      break;
    }
    if (port_index < 1) {
      memcpy(&audio_port->sAudioParam, audio_port_format, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
    } else {
      omx_err = OMX_ErrorBadPortIndex;
    }
    break;
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
  omx_base_video_PortType *video_port = (omx_base_video_PortType *) comp_priv->ports[OMX_BASE_SINK_INPUTPORT_INDEX];
  omx_base_audio_PortType *audio_port = (omx_base_audio_PortType *) comp_priv->ports[OMX_BASE_SINK_INPUTPORT_INDEX_1];
  OMX_PORT_PARAM_TYPE *video_port_param;
  OMX_PORT_PARAM_TYPE *audio_port_param;
  OMX_VIDEO_PARAM_PORTFORMATTYPE *video_port_format;
  OMX_AUDIO_PARAM_PORTFORMATTYPE *audio_port_format;

  if (!comp_param) {
    return OMX_ErrorBadParameter;
  }

  LOGI("Getting parameter %d", param_index);

  switch ((int) param_index) {
  case OMX_IndexParamVideoInit:
    video_port_param = (OMX_PORT_PARAM_TYPE *) comp_param;
    if ((omx_err = checkHeader(comp_param, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    video_port_param->nStartPortNumber = VIDEO_PORT_INDEX;
    video_port_param->nPorts = 1;
    break;
  case OMX_IndexParamVideoPortFormat:
    video_port_format = (OMX_VIDEO_PARAM_PORTFORMATTYPE *) comp_param;
    if ((omx_err = checkHeader(comp_param, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (video_port_format->nPortIndex < 1) {
      memcpy(video_port_format, &video_port->sVideoParam, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
    } else {
      omx_err = OMX_ErrorBadParameter;
    }
    break;
  case OMX_IndexParamAudioInit:
    audio_port_param = (OMX_PORT_PARAM_TYPE *) comp_param;
    if ((omx_err = checkHeader(comp_param, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    audio_port_param->nStartPortNumber = AUDIO_PORT_INDEX;
    audio_port_param->nPorts = 1;
    break;
  case OMX_IndexParamAudioPortFormat:
    audio_port_format = (OMX_AUDIO_PARAM_PORTFORMATTYPE *) comp_param;
    if ((omx_err = checkHeader(comp_param, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (audio_port_format->nPortIndex <= 1) {
      memcpy(audio_port_format, &audio_port->sAudioParam, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
    } else {
      omx_err = OMX_ErrorBadParameter;
    }
    break;
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

OMX_ERRORTYPE omx_rtmpout_component_Init(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  int ret = TRUE;

  comp_priv->rtmp = RTMP_Alloc();
  if (!comp_priv->rtmp) {
    LOGE("RTMP_Alloc failed for url \"%s\"", comp_priv->output_url);
    return OMX_ErrorInsufficientResources;
  }

  RTMP_Init(comp_priv->rtmp);
  comp_priv->rtmp->Link.timeout = RTMP_SOCK_TIMEOUT;

  RTMP_LogSetLevel(RTMP_LOGLEVEL);
  RTMP_LogSetCallback(rtmp_log);

  if (!(ret = RTMP_SetupURL(comp_priv->rtmp, comp_priv->output_url))) {
    LOGE("RTMP_SetupURL failed for url \"%s\"", comp_priv->output_url);
    goto out;
  }

  RTMP_EnableWrite(comp_priv->rtmp);

  if (!(ret = RTMP_Connect(comp_priv->rtmp, NULL))) {
    LOGE("RTMP_Connect failed for url \"%s\"", comp_priv->output_url);
    goto out;
  }

  if (!(ret = RTMP_ConnectStream(comp_priv->rtmp, 0))) {
    LOGE("RTMP_ConnectStream failed for url \"%s\"", comp_priv->output_url);
    goto out;
  }

  comp_priv->rtmp_ready = OMX_TRUE;
  tsem_up(comp_priv->rtmp_sync_sem);

out:
  return ret ? OMX_ErrorNone : OMX_ErrorBadParameter;
}

OMX_ERRORTYPE omx_rtmpout_component_Deinit(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;

  if (comp_priv->rtmp) {
    if (RTMP_IsConnected(comp_priv->rtmp))
      LOGI("Disconnect from url \"%s\"", comp_priv->output_url);
    RTMP_Close(comp_priv->rtmp);
    RTMP_Free(comp_priv->rtmp);
    comp_priv->rtmp = NULL;
  }

  comp_priv->rtmp_ready = OMX_FALSE;
  tsem_reset(comp_priv->rtmp_sync_sem);

  return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_rtmpout_component_port_SendBufferFunction(omx_base_PortType *omx_port, OMX_BUFFERHEADERTYPE *buffer)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_U32 port_index;
  OMX_COMPONENTTYPE *omx_comp = omx_port->standCompContainer;
  omx_base_component_PrivateType *base_comp_priv = (omx_base_component_PrivateType*) omx_comp->pComponentPrivate;

  port_index =
    omx_port->sPortParam.eDir == OMX_DirInput ? buffer->nInputPortIndex : buffer->nOutputPortIndex;
  if (port_index != omx_port->sPortParam.nPortIndex) {
    LOGE("Wrong port for this operation port_index=%d nPortIndex=%d",
         port_index, omx_port->sPortParam.nPortIndex);
    return OMX_ErrorBadPortIndex;
  }

  if (base_comp_priv->state == OMX_StateInvalid) {
    LOGE("We are in OMX_StateInvalid");
    return OMX_ErrorInvalidState;
  }

  if (base_comp_priv->state != OMX_StateExecuting &&
      base_comp_priv->state != OMX_StatePause &&
      base_comp_priv->state != OMX_StateIdle) {
    LOGE("We are not in executing/pause/idle state, but in %d", base_comp_priv->state);
    return OMX_ErrorIncorrectStateOperation;
  }
  if ((!PORT_IS_ENABLED(omx_port)) ||
      (PORT_IS_BEING_DISABLED(omx_port) && !PORT_IS_TUNNELED_N_BUFFER_SUPPLIER(omx_port)) ||
      (base_comp_priv->transientState == OMX_TransStateExecutingToIdle &&
       (PORT_IS_TUNNELED(omx_port) && !PORT_IS_BUFFER_SUPPLIER(omx_port)))) {
    LOGE("Port %u is disabled comp = %s", port_index, base_comp_priv->name);
    return OMX_ErrorIncorrectStateOperation;
  }

  if ((omx_err = checkHeader(buffer, sizeof(OMX_BUFFERHEADERTYPE))) != OMX_ErrorNone) {
    LOGE("Received wrong buffer header on input port %u", port_index);
    return omx_err;
  }

  if (PORT_IS_TUNNELED(omx_port) && !PORT_IS_BEING_FLUSHED(omx_port) &&
      (base_comp_priv->transientState != OMX_TransStateExecutingToIdle) &&
      (buffer->nFlags != OMX_BUFFERFLAG_EOS)) {
    LOGE("Get frame!");
  }

  if (!PORT_IS_BEING_FLUSHED(omx_port) && !(PORT_IS_BEING_DISABLED(omx_port) && PORT_IS_TUNNELED_N_BUFFER_SUPPLIER(omx_port))) {
    queue(omx_port->pBufferQueue, buffer);
    tsem_up(omx_port->pBufferSem);
    tsem_up(base_comp_priv->bMgmtSem);
  } else if (PORT_IS_BUFFER_SUPPLIER(omx_port)) {
    queue(omx_port->pBufferQueue, buffer);
    tsem_up(omx_port->pBufferSem);
  } else {
    LOGE("Error gets here");
    return OMX_ErrorIncorrectStateOperation;
  }
  return omx_err;
}

static void rtmp_log(int level, const char *fmt, va_list args)
{
  if (level == RTMP_LOGDEBUG2)
    return;

  char buf[4096];
  vsnprintf(buf, sizeof(buf)-1, fmt, args);

  switch (level) {
    case RTMP_LOGCRIT:
    case RTMP_LOGERROR:   level = xlog::ERR;  break;
    case RTMP_LOGWARNING: level = xlog::WARN; break;
    case RTMP_LOGINFO:    level = xlog::INFO; break;
    case RTMP_LOGDEBUG:
    case RTMP_LOGDEBUG2:
    default:              level = xlog::DEBUG;break;
  }

  xlog::log_print("rtmpout", "unknown", -1, (xlog::log_level) level, buf);
}
