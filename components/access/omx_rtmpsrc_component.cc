#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_rtmpsrc_component.h>

#include <orps_config.h>
#include <get_bits.h>
#include <xmedia.h>
#include <xutil.h>
#include <xlog.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1

#define DEFAULT_URL_LENGTH  2048

static OMX_U32 rtmpsrc_instance = 0;

static void rtmp_log(int level, const char *fmt, va_list args);

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *omx_comp, OMX_STRING comp_name)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  omx_rtmpsrc_component_PrivateType *comp_priv;
  omx_base_video_PortType *port_v;
  omx_base_audio_PortType *port_a;

  RM_RegisterComponent((char *) RTMPSRC_COMP_NAME, MAX_RTMPSRC_COMPONENTS);

  if (!omx_comp->pComponentPrivate) {
    omx_comp->pComponentPrivate = (omx_rtmpsrc_component_PrivateType *) calloc(1, sizeof(omx_rtmpsrc_component_PrivateType));
    if (omx_comp->pComponentPrivate == NULL) {
      return OMX_ErrorInsufficientResources;
    }
  }

  comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;
  comp_priv->ports = NULL;

  omx_err = omx_base_source_Constructor(omx_comp, comp_name);
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

    comp_priv->ports[VIDEO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!comp_priv->ports[VIDEO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    comp_priv->ports[AUDIO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!comp_priv->ports[AUDIO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
  }

  base_video_port_Constructor(omx_comp, &comp_priv->ports[VIDEO_PORT_INDEX], VIDEO_PORT_INDEX, OMX_FALSE);
  base_audio_port_Constructor(omx_comp, &comp_priv->ports[AUDIO_PORT_INDEX], AUDIO_PORT_INDEX, OMX_FALSE);

  port_v = (omx_base_video_PortType *) comp_priv->ports[VIDEO_PORT_INDEX];
  port_a = (omx_base_audio_PortType *) comp_priv->ports[AUDIO_PORT_INDEX];

  port_v->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;
  port_a->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;

  comp_priv->BufferMgmtCallback = omx_rtmpsrc_component_BufferMgmtCallback;
  comp_priv->BufferMgmtFunction = omx_base_source_twoport_BufferMgmtFunction;

  comp_priv->destructor = omx_rtmpsrc_component_Destructor;
  comp_priv->messageHandler = omx_rtmpsrc_component_MessageHandler;

  ++rtmpsrc_instance;
  if (rtmpsrc_instance > MAX_RTMPSRC_COMPONENTS) {
    return OMX_ErrorInsufficientResources;
  }

  omx_comp->SetParameter = omx_rtmpsrc_component_SetParameter;
  omx_comp->GetParameter = omx_rtmpsrc_component_GetParameter;
  omx_comp->GetExtensionIndex = omx_rtmpsrc_component_GetExtensionIndex;

  comp_priv->tmp_output_buffer = (OMX_BUFFERHEADERTYPE *) calloc(1, sizeof(OMX_BUFFERHEADERTYPE));
  if (!comp_priv->tmp_output_buffer) {
    return OMX_ErrorInsufficientResources;
  }
  comp_priv->tmp_output_buffer->pBuffer = (OMX_U8 *) calloc(DEFAULT_OUT_BUFFER_SIZE, 1);
  comp_priv->tmp_output_buffer->nFilledLen = 0;
  comp_priv->tmp_output_buffer->nAllocLen = DEFAULT_OUT_BUFFER_SIZE;
  comp_priv->tmp_output_buffer->nOffset = 0;

  comp_priv->input_url = (OMX_STRING) calloc(DEFAULT_URL_LENGTH, 1);
  if (!comp_priv->input_url) {
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

OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_U32 i;

  if (comp_priv->rtmp_sync_sem) {
    tsem_deinit(comp_priv->rtmp_sync_sem);
    SAFE_FREE(comp_priv->rtmp_sync_sem);
  }

  SAFE_FREE(comp_priv->input_url);

  SAFE_FREE(comp_priv->tmp_output_buffer);

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

  --rtmpsrc_instance;
  return omx_base_source_Destructor(omx_comp);
}

void omx_rtmpsrc_component_BufferMgmtCallback(OMX_COMPONENTTYPE *omx_comp, OMX_BUFFERHEADERTYPE *output_buffer)
{
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_BUFFERHEADERTYPE *temp_buffer;
  RTMPPacket packet = { 0 };

  temp_buffer = comp_priv->tmp_output_buffer;

  if (!comp_priv->rtmp_ready) {
    if (comp_priv->state == OMX_StateExecuting) {
      tsem_down(comp_priv->rtmp_sync_sem);
    } else {
      return;
    }
  }

  output_buffer->nFilledLen = 0;
  output_buffer->nOffset = 0;

#define BAIL_RETURN do { \
  RTMPPacket_Free(&packet); \
  output_buffer->nFlags = OMX_BUFFERFLAG_EOS; \
  return; \
} while (0)

again:
  if (temp_buffer->nFilledLen == 0) {
    if (!comp_priv->rtmp->m_bPlaying ||
        !RTMP_IsConnected(comp_priv->rtmp) ||
        !RTMP_ReadPacket(comp_priv->rtmp, &packet)) {
      output_buffer->nFlags = OMX_BUFFERFLAG_EOS;
    } else {
      if (RTMPPacket_IsReady(&packet)) {
        if (!packet.m_nBodySize) {
          goto again;
        }

        xutil::GetBitContext bits;
        init_get_bits(&bits, (const OMX_U8 *) packet.m_body, packet.m_nBodySize*8);

        OMX_BUFFERHEADERTYPE *dst_buffer;

        if (packet.m_packetType == RTMP_PACKET_TYPE_VIDEO) {
          get_bits(&bits, 4); // skip frame_type
          OMX_U8 codec_id = get_bits(&bits, 4);
          if (codec_id != 7) {
            LOGE("Video codec(%d) not supported for url \"%s\"", codec_id, comp_priv->input_url);
            BAIL_RETURN;
          }

          OMX_U8 avc_pkt_type = get_bits(&bits, 8);
          get_bits(&bits, 24); // skip composition_time
          OMX_U32 data_offset = (4 + 4 + 8 + 24)/8;
          const OMX_U8 *data = (const OMX_U8 *) packet.m_body + data_offset;
          OMX_U32 data_size = packet.m_nBodySize - data_offset;

          if (output_buffer->nOutputPortIndex == VIDEO_PORT_INDEX) {
            dst_buffer = output_buffer;
          } else {
            dst_buffer = temp_buffer;
            dst_buffer->nOutputPortIndex = VIDEO_PORT_INDEX;
          }

          if (avc_pkt_type == 0 /* AVC sequence header */) {
            memcpy(dst_buffer->pBuffer, data, data_size);
            dst_buffer->nFilledLen = data_size;
            dst_buffer->nFlags = OMX_BUFFERFLAG_CODECCONFIG;
          } else if (avc_pkt_type == 1 /* AVC NALU */) {
            if (dst_buffer->nAllocLen >= data_size) {
              memcpy(dst_buffer->pBuffer, data, data_size);
              dst_buffer->nFilledLen = data_size;
              dst_buffer->nTimeStamp = packet.m_nTimeStamp * 1000;
              if (!comp_priv->first_timestamp_flag[0]) {
                comp_priv->first_timestamp_flag[0] = OMX_TRUE;
                dst_buffer->nFlags = OMX_BUFFERFLAG_STARTTIME;
              }
            } else {
              LOGE("Buffer size=%d less than pkt size=%d buffer=%p port_index=%d",
                   dst_buffer->nAllocLen, data_size, dst_buffer, dst_buffer->nOutputPortIndex);
            }
          } else if (avc_pkt_type == 2 /* AVC end of sequence */) {
            // Fall through
          } else {
            LOGE("Unknown avc packet type(%d) for url \"%s\"", avc_pkt_type, comp_priv->input_url);
            BAIL_RETURN;
          }
        } else if (packet.m_packetType == RTMP_PACKET_TYPE_AUDIO) {
          OMX_U8 sound_format = get_bits(&bits, 4);
          OMX_U8 sound_rate = get_bits(&bits, 2);
          OMX_U8 sound_size = get_bits(&bits, 1);
          OMX_U8 sound_type = get_bits(&bits, 1);

          if (sound_format != 10 || sound_rate != 3 || sound_size != 1 || sound_type != 1) {
            LOGE("Unsupported audio paket(sound_format=%d sound_rate=%d sound_size=%d sound_type=%d) for url \"%s\"",
                 sound_format, sound_rate, sound_size, sound_type, comp_priv->input_url);
            BAIL_RETURN;
          }

          OMX_U8 aac_packet_type = get_bits(&bits, 8);
          OMX_U32 data_offset = (4 + 2 + 1 + 1 + 8)/8;
          const OMX_U8 *data = (const OMX_U8 *) packet.m_body + data_offset;
          OMX_U32 data_size = packet.m_nBodySize - data_offset;

          if (output_buffer->nOutputPortIndex == AUDIO_PORT_INDEX) {
            dst_buffer = output_buffer;
          } else {
            dst_buffer = temp_buffer;
            dst_buffer->nOutputPortIndex = AUDIO_PORT_INDEX;
          }

          if (aac_packet_type == 0 /* AAC sequence header */) {
            if (data_size >= 2) {
              memcpy(dst_buffer->pBuffer, data, data_size);
              dst_buffer->nFilledLen = data_size;
            } else {
              xmedia::generate_asc(dst_buffer->pBuffer,
                                   xmedia::str_to_audioprof("LC"), xmedia::str_to_samplerate_idx("44100"), 2);
              dst_buffer->nFilledLen = 2;
            }
            dst_buffer->nFlags = OMX_BUFFERFLAG_CODECCONFIG;
          } else if (aac_packet_type == 1 /* AAC raw */) {
            memcpy(dst_buffer->pBuffer, data, data_size);
            dst_buffer->nFilledLen = data_size;
            dst_buffer->nTimeStamp = packet.m_nTimeStamp * 1000;
            if (!comp_priv->first_timestamp_flag[1]) {
              comp_priv->first_timestamp_flag[1] = OMX_TRUE;
              dst_buffer->nFlags = OMX_BUFFERFLAG_STARTTIME;
            }
          } else {
            LOGE("Unknown aac_packet_type(%d) for url \"%s\"", aac_packet_type, comp_priv->input_url);
            BAIL_RETURN;
          }
        } else if (packet.m_packetType == RTMP_PACKET_TYPE_INFO) {
          // Fall through
        }

        RTMPPacket_Free(&packet);
      } else {
        goto again;
      }
    }
  } else {
    if (((temp_buffer->nOutputPortIndex == VIDEO_PORT_INDEX) && (output_buffer->nOutputPortIndex == VIDEO_PORT_INDEX)) ||
        ((temp_buffer->nOutputPortIndex == AUDIO_PORT_INDEX) && (output_buffer->nOutputPortIndex == AUDIO_PORT_INDEX))) {
      if (output_buffer->nAllocLen >= temp_buffer->nFilledLen) {
        memcpy(output_buffer->pBuffer, temp_buffer->pBuffer, temp_buffer->nFilledLen);
        output_buffer->nFilledLen = temp_buffer->nFilledLen;
        output_buffer->nTimeStamp = temp_buffer->nTimeStamp;
        output_buffer->nFlags = temp_buffer->nFlags;
        temp_buffer->nFilledLen = 0;
        temp_buffer->nFlags = 0;
      } else {
        LOGE("Buffer size=%d less than pkt size=%d buffer=%p port_index=%d",
             output_buffer->nAllocLen, temp_buffer->nFilledLen, output_buffer, output_buffer->nOutputPortIndex);
      }
    }
  }

#undef BAIL_RETURN
}

OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR comp_parm)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_U32 url_length;

  OMX_COMPONENTTYPE *omx_comp = (OMX_COMPONENTTYPE *) hcomp;
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;

  LOGI("Setting parameter %i", nParamIndex);

  if (comp_parm == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch ((long) nParamIndex) {
  case OMX_IndexVendorInputUrl:
    url_length = strlen(((char *) comp_parm)) + 1;
    if (url_length > DEFAULT_URL_LENGTH) {
      SAFE_FREE(comp_priv->input_url);
      comp_priv->input_url = (char *) malloc(url_length);
    }
    strcpy(comp_priv->input_url, (char *) comp_parm);
    break;
  default:
    return omx_base_component_SetParameter(hcomp, nParamIndex, comp_parm);
  }
  return omx_err;
}

OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR comp_parm)
{
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE *video_port_parm, *audio_port_parm;
  OMX_VIDEO_PARAM_PORTFORMATTYPE *video_port_format;
  OMX_AUDIO_PARAM_PORTFORMATTYPE *audio_port_format;

  OMX_COMPONENTTYPE *omx_comp = (OMX_COMPONENTTYPE *) hcomp;
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;
  omx_base_video_PortType *video_port = (omx_base_video_PortType *) comp_priv->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX];
  omx_base_audio_PortType *audio_port = (omx_base_audio_PortType *) comp_priv->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX_1];

  LOGI("Getting parameter %i", nParamIndex);

  if (comp_parm == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch ((long) nParamIndex) {
  case OMX_IndexParamVideoInit:
    video_port_parm = (OMX_PORT_PARAM_TYPE *) comp_parm;
    if ((omx_err = checkHeader(comp_parm, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    video_port_parm->nStartPortNumber = VIDEO_PORT_INDEX;
    video_port_parm->nPorts = 1;
    break;
  case OMX_IndexParamVideoPortFormat:
    video_port_format = (OMX_VIDEO_PARAM_PORTFORMATTYPE *) comp_parm;
    if ((omx_err = checkHeader(comp_parm, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (video_port_format->nPortIndex < 1) {
      memcpy(video_port_format, &video_port->sVideoParam, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
    } else {
      return OMX_ErrorBadParameter;
    }
    break;
  case OMX_IndexParamAudioInit:
    audio_port_parm = (OMX_PORT_PARAM_TYPE *) comp_parm;
    if ((omx_err = checkHeader(comp_parm, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    audio_port_parm->nStartPortNumber = AUDIO_PORT_INDEX;
    audio_port_parm->nPorts = 1;
    break;
  case OMX_IndexParamAudioPortFormat:
    audio_port_format = (OMX_AUDIO_PARAM_PORTFORMATTYPE *) comp_parm;
    if ((omx_err = checkHeader(comp_parm, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (audio_port_format->nPortIndex <= 1) {
      memcpy(audio_port_format, &audio_port->sAudioParam, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
    } else {
      return OMX_ErrorBadParameter;
    }
    break;
  case OMX_IndexVendorInputUrl:
    strcpy((char *) comp_parm, comp_priv->input_url);
    break;
  default:
      return omx_base_component_GetParameter(hcomp, nParamIndex, comp_parm);
  }
  return omx_err;
}

OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hcomp,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *index)
{
  LOGI("Get extension index %s", cParameterName);

  if (!strcmp(cParameterName, "OMX.ST.index.param.inputurl")) {
    *index = (OMX_INDEXTYPE) OMX_IndexVendorInputUrl;
  } else {
    return OMX_ErrorBadParameter;
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_rtmpsrc_component_MessageHandler(OMX_COMPONENTTYPE *omx_comp, internalRequestMessageType *message)
{
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;
  OMX_STATETYPE oldState = comp_priv->state;

  omx_err = omx_base_component_MessageHandler(omx_comp, message);

  if (message->messageType == OMX_CommandStateSet) {
    if ((message->messageParam == OMX_StateExecuting) && (oldState == OMX_StateIdle)) {
      omx_err = omx_rtmpsrc_component_Init(omx_comp);
      if (omx_err != OMX_ErrorNone) {
        LOGE("Rtmpsrc Init failed Error=%x", omx_err);
        return omx_err;
      }
    } else if ((message->messageParam == OMX_StateIdle) && (oldState == OMX_StateExecuting)) {
      omx_err = omx_rtmpsrc_component_Deinit(omx_comp);
      if (omx_err != OMX_ErrorNone) {
        LOGE("Rtmpsrc Deinit failed Error=%x", omx_err);
        return omx_err;
      }
    }
  }

  return omx_err;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Init(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;

  comp_priv->rtmp = RTMP_Alloc();
  if (!comp_priv->rtmp) {
    LOGE("RTMP_Alloc failed for url \"%s\"", comp_priv->input_url);
    return OMX_ErrorInsufficientResources;
  }

  RTMP_Init(comp_priv->rtmp);
  comp_priv->rtmp->Link.timeout = RTMP_SOCK_TIMEOUT;

  RTMP_LogSetLevel(RTMP_LOGLEVEL);
  RTMP_LogSetCallback(rtmp_log);

  AVal parsed_host, parsed_app, parsed_playpath;
  unsigned int parsed_port = 0;
  int parsed_protocol = RTMP_PROTOCOL_UNDEFINED;
  char buf[512] = { 0 };
  AVal sockhost = { 0, 0 }, tcurl = { buf, 0 };
  int ret = TRUE;

  if (!(ret = RTMP_ParseURL(comp_priv->input_url, &parsed_protocol,
                            &parsed_host, &parsed_port,
                            &parsed_playpath, &parsed_app))) {
    LOGE("RTMP_ParseURL failed for url \"%s\"", comp_priv->input_url);
    goto out;
  }

  tcurl.av_len = snprintf(buf, sizeof(buf)-1, "%s://%.*s:%d/%.*s",
                          RTMPProtocolStringsLower[parsed_protocol],
                          parsed_host.av_len, parsed_host.av_val,
                          parsed_port,
                          parsed_app.av_len, parsed_app.av_val);

  RTMP_SetupStream(comp_priv->rtmp, parsed_protocol, &parsed_host, parsed_port,
                   &sockhost, &parsed_playpath, &tcurl, NULL, NULL,
                   &parsed_app, NULL, NULL, 0,
                   NULL, NULL, NULL, 0, 0, TRUE, RTMP_SOCK_TIMEOUT);

  RTMP_SetBufferMS(comp_priv->rtmp, RTMP_BUFFER_TIME);

  if (!(ret = RTMP_Connect(comp_priv->rtmp, NULL))) {
    LOGE("RTMP_Connect failed for url \"%s\"", comp_priv->input_url);
    goto out;
  }

  if (!(ret = RTMP_ConnectStream(comp_priv->rtmp, 0))) {
    LOGE("RTMP_ConnectStream failed for url \"%s\"", comp_priv->input_url);
    goto out;
  }

  comp_priv->rtmp_ready = OMX_TRUE;
  tsem_up(comp_priv->rtmp_sync_sem);

  LOGI("Rtmpsrc for url \"%s\" initialized", comp_priv->input_url);

out:
  SAFE_FREE(parsed_playpath.av_val);
  return ret == TRUE ? OMX_ErrorNone : OMX_ErrorBadParameter;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Deinit(OMX_COMPONENTTYPE *omx_comp)
{
  omx_rtmpsrc_component_PrivateType *comp_priv = (omx_rtmpsrc_component_PrivateType *) omx_comp->pComponentPrivate;

  if (comp_priv->rtmp) {
    if (RTMP_IsConnected(comp_priv->rtmp))
      LOGI("Disconnect from url \"%s\"", comp_priv->input_url);
    RTMP_Close(comp_priv->rtmp);
    RTMP_Free(comp_priv->rtmp);
    comp_priv->rtmp = NULL;
  }

  comp_priv->rtmp_ready = OMX_FALSE;
  tsem_reset(comp_priv->rtmp_sync_sem);

  return OMX_ErrorNone;
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

  xlog::log_print("rtmpsrc", "unknown", -1, (xlog::log_level) level, buf);
}
