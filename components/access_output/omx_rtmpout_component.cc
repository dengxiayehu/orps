#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_rtmpout_component.h>

#include <orps_config.h>
#include <rtmp_util.h>
#include <xmacro.h>
#include <xlog.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1

#define DEFAULT_OUT_URL_LENGTH 2048

#define VIDEO_BUFFER_SIZE 150000
#define AUDIO_BUFFER_SIZE 65536

#define VIDEO_BODY_HEADER_LENGTH    16
#define VIDEO_PAYLOAD_OFFSET        5

#define XDEBUG 1

static OMX_U32 rtmpout_instance = 0;

static int handle_video(OMX_COMPONENTTYPE *omx_comp, OMX_BUFFERHEADERTYPE *input_buffer);
static int handle_audio(OMX_COMPONENTTYPE *omx_comp, OMX_BUFFERHEADERTYPE *input_buffer);
static int make_avc_dcr_body(OMX_U8 *buf, const OMX_U8 *sps, OMX_U32 sps_length, const OMX_U8 *pps, OMX_U32 pps_length);
static int make_video_body(OMX_U8 *buf, OMX_U32 dat_len, int key_frame, OMX_U32 composition_time);
static int make_asc_body(const OMX_U8 asc[], OMX_U8 buf[], uint32_t len);
static int make_audio_body(const OMX_U8 *dat, uint32_t dat_len, OMX_U8 buf[], uint32_t len);
static bool send_rtmp_pkt(OMX_COMPONENTTYPE *omx_comp, int pkttype, uint32_t ts, const OMX_U8 *buf, uint32_t pktsize);

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
  port_a->sPortParam.nBufferSize = AUDIO_BUFFER_SIZE;

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

  comp_priv->avc_dcr = new xmedia::AVCDecorderConfigurationRecord;
  comp_priv->asc = new xmedia::AudioSpecificConfig;
  comp_priv->mholder = new xutil::MemHolder;

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpout_component_Destructor(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_U32 i;

  SAFE_DELETE(comp_priv->avc_dcr);
  SAFE_DELETE(comp_priv->asc);
  SAFE_DELETE(comp_priv->mholder);

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
    if (comp_priv->state == OMX_StateExecuting &&
        comp_priv->rtmp && RTMP_IsConnected(comp_priv->rtmp)) {
      tsem_down(comp_priv->rtmp_sync_sem);
    } else {
      return;
    }
  }

  OMX_U32 port_index = input_buffer->nInputPortIndex;
  int ret = 0;
  if (port_index == VIDEO_PORT_INDEX) {
    ret = handle_video(omx_comp, input_buffer);
  } else if (port_index == AUDIO_PORT_INDEX) {
    ret = handle_audio(omx_comp, input_buffer);
  }
  if (ret < 0) {
    LOGE("Handle %s buffer failed", port_index == VIDEO_PORT_INDEX ? "video" : "audio");
  }

  input_buffer->nFilledLen = 0;
  input_buffer->nOffset = 0;
  input_buffer->nFlags = 0;
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
      if (omx_err != OMX_ErrorNone) {
        LOGE("Rtmpout init failed, error=%x", omx_err);
        (*(comp_priv->callbacks->EventHandler))(omx_comp, comp_priv->callbackData, OMX_EventError, omx_err, 0, NULL);
        return omx_err;
      }
    } else if ((message->messageParam == OMX_StateIdle) && (old_state == OMX_StateExecuting)) {
      omx_err = omx_rtmpout_component_Deinit(omx_comp);
      if (omx_err != OMX_ErrorNone) {
        LOGE("Rtmpout deinit failed, error=%x", omx_err);
        return omx_err;
      }
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
  RTMP_LogSetCallback(rtmp_common::rtmp_log);

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

  LOGI("Rtmpout for url \"%s\" initialized", comp_priv->output_url);
  comp_priv->rtmp_ready = OMX_TRUE;

out:
  if (!comp_priv->rtmp_ready) {
    RTMP_Close(comp_priv->rtmp);
  }
  tsem_up(comp_priv->rtmp_sync_sem);
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

static int handle_video(OMX_COMPONENTTYPE *omx_comp, OMX_BUFFERHEADERTYPE *input_buffer)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;

  if (input_buffer->nFlags&OMX_BUFFERFLAG_CODECCONFIG) {
    if (comp_priv->avc_dcr->parse_from(input_buffer->pBuffer, input_buffer->nFilledLen) < 0)
      return -1;
    OMX_U8 avc_dcr_body[2048];
    int len = make_avc_dcr_body(avc_dcr_body,
                                comp_priv->avc_dcr->sps, comp_priv->avc_dcr->sps_length,
                                comp_priv->avc_dcr->pps, comp_priv->avc_dcr->pps_length);
#if defined(XDEBUG) && (XDEBUG != 0)
    print_avc_dcr(*comp_priv->avc_dcr);
    LOGD("Send avc_dcr, timestamp=%u, len=%d", 0, len);
#endif
    if (!send_rtmp_pkt(omx_comp, RTMP_PACKET_TYPE_VIDEO, 0, avc_dcr_body, len)) {
      LOGE("Send avc_dcr to rtmpserver failed");
      return -1;
    }
  } else {
    OMX_U8 *buf =
      (OMX_U8 *) comp_priv->mholder->alloc(input_buffer->nFilledLen + VIDEO_BODY_HEADER_LENGTH);
    memcpy(buf + VIDEO_PAYLOAD_OFFSET, input_buffer->pBuffer, input_buffer->nFilledLen);
    int len = make_video_body(buf, VIDEO_PAYLOAD_OFFSET + input_buffer->nFilledLen,
                              input_buffer->nFlags&OMX_BUFFERFLAG_KEY_FRAME, 0);
#if defined(XDEBUG) && (XDEBUG != 0)
    LOGD("Send video data, timestamp=%u, len=%d, is_key=%s (nflags=%x)", input_buffer->nTimeStamp/1000, len, input_buffer->nFlags&OMX_BUFFERFLAG_KEY_FRAME ? "yes" : "no", input_buffer->nFlags);
#endif
    if (!send_rtmp_pkt(omx_comp, RTMP_PACKET_TYPE_VIDEO,
                       input_buffer->nTimeStamp/1000, buf, len)) {
      LOGE("Send video data to rtmpserver failed");
      return -1;
    }
  }
  return 0;
}

static int handle_audio(OMX_COMPONENTTYPE *omx_comp, OMX_BUFFERHEADERTYPE *input_buffer)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;

  if (input_buffer->nFlags&OMX_BUFFERFLAG_CODECCONFIG) {
    if (input_buffer->nFilledLen != 2) {
      LOGW("AudioSpecificConfig's length is %d, not the desired 2, truncated", input_buffer->nFilledLen);
    }
    memcpy(comp_priv->asc->dat, input_buffer->pBuffer, 2);

    OMX_U8 asc_body[4];
    make_asc_body(comp_priv->asc->dat, asc_body, sizeof(asc_body));
#if defined(XDEBUG) && (XDEBUG != 0)
    xmedia::print_asc(*comp_priv->asc);
    LOGD("Send asc, timestamp=%u, 0x%x 0x%x 0x%x 0x%x", 0, asc_body[0], asc_body[1], asc_body[2], asc_body[3]);
#endif
    if (!send_rtmp_pkt(omx_comp, RTMP_PACKET_TYPE_AUDIO, 0, asc_body, 4)) {
      LOGE("Send asc to rtmpserver failed");
      return -1;
    }
  } else {
    OMX_U8 *buf = (OMX_U8 *) comp_priv->mholder->alloc(input_buffer->nFilledLen + 2);
    int len = make_audio_body(input_buffer->pBuffer, input_buffer->nFilledLen, buf, input_buffer->nFilledLen + 2);
#if defined(XDEBUG) && (XDEBUG != 0)
    LOGD("Send audio data, timestamp=%u", input_buffer->nTimeStamp/1000);
#endif
    if (!send_rtmp_pkt(omx_comp, RTMP_PACKET_TYPE_AUDIO,
                       input_buffer->nTimeStamp/1000, buf, len)) {
      LOGE("Send audio data to rtmpserver failed");
      return -1;
    }
  }
  return 0;
}

static int make_avc_dcr_body(OMX_U8 *buf, const OMX_U8 *sps, OMX_U32 sps_length, const OMX_U8 *pps, OMX_U32 pps_length)
{
  OMX_U32 idx = 0;

  buf[idx++] = 0x17;

  buf[idx++] = 0x00;

  xutil::put_be24(buf + idx, 0);
  idx += 3;

  buf[idx++] = 0x01;
  buf[idx++] = sps[1];
  buf[idx++] = sps[2];
  buf[idx++] = sps[3];
  buf[idx++] = 0xFF;
  buf[idx++] = 0xE1;
  buf[idx++] = (OMX_U8) ((sps_length>>8)&0xFF);
  buf[idx++] = (OMX_U8) (sps_length&0xFF);
  memcpy(buf+idx, sps, sps_length);
  idx += sps_length;

  buf[idx++] = 0x01;
  buf[idx++] = (OMX_U8) ((pps_length>>8)&0xFF);
  buf[idx++] = (OMX_U8) (pps_length&0xFF);
  memcpy(buf+idx, pps, pps_length);
  idx += pps_length;

#if defined(XDEBUG) && (XDEBUG != 0)
  LOGI("[avc_dcr] SPS: %02x %02x %02x %02x ... (%u bytes in total)",
       sps[0], sps[1], sps[2], sps[3], sps_length);
  LOGI("[avc_dcr] PPS: %02x %02x %02x %02x ... (%u bytes in total)",
       pps[0], pps[1], pps[2], pps[3], pps_length);
#endif
  return idx;
}

static int make_video_body(OMX_U8 *buf, OMX_U32 dat_len, int key_frame, OMX_U32 composition_time)
{
  OMX_U32 idx = 0;

  buf[idx++] = key_frame ? 0x17 : 0x27;

  buf[idx++] = 0x01;

  xutil::put_be24(buf + idx, composition_time);
  return dat_len;
}

static int make_asc_body(const OMX_U8 asc[2], OMX_U8 buf[], uint32_t len)
{
  buf[0] = 0xAF;
  buf[1] = 0x00;
  memcpy(buf + 2, asc, 2);
  return 1 + 1 + 2;
}

static int make_audio_body(const OMX_U8 *dat, uint32_t dat_len, OMX_U8 buf[], uint32_t len)
{
  buf[0] = 0xAF;
  buf[1] = 0x01;
  memcpy(buf + 2, dat, dat_len);
  return dat_len + 2;
}

static bool send_rtmp_pkt(OMX_COMPONENTTYPE *omx_comp, int pkttype, uint32_t ts, const OMX_U8 *buf, uint32_t pktsize)
{
  omx_rtmpout_component_PrivateType *comp_priv = (omx_rtmpout_component_PrivateType *) omx_comp->pComponentPrivate;
  ::RTMPPacket rtmp_pkt;
  RTMPPacket_Reset(&rtmp_pkt);
  RTMPPacket_Alloc(&rtmp_pkt, pktsize);
  memcpy(rtmp_pkt.m_body, buf, pktsize);
  rtmp_pkt.m_packetType = pkttype;
  rtmp_pkt.m_nChannel = rtmp_common::pkttyp2channel(pkttype);
  rtmp_pkt.m_headerType = RTMP_PACKET_SIZE_LARGE;
  rtmp_pkt.m_nTimeStamp = ts;
  rtmp_pkt.m_hasAbsTimestamp = 0;
  rtmp_pkt.m_nInfoField2 = comp_priv->rtmp->m_stream_id;
  rtmp_pkt.m_nBodySize = pktsize;
  bool retval = RTMP_SendPacket(comp_priv->rtmp, &rtmp_pkt, FALSE);
  RTMPPacket_Free(&rtmp_pkt);
  return retval;
}
