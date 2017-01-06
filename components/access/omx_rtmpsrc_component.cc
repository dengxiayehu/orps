#include <omxcore.h>
#include <omx_base_video_port.h>
#include <omx_base_audio_port.h>
#include <omx_base_clock_port.h>
#include <omx_rtmpsrc_component.h>

#define VIDEO_PORT_INDEX 0
#define AUDIO_PORT_INDEX 1
#define CLOCK_PORT_INDEX 2

#define DEFAULT_URL_LENGTH  2048

static OMX_U32 noRtmpsrcInstance = 0;

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *openmaxStandComp, OMX_STRING cComponentName)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  omx_rtmpsrc_component_PrivateType *compPriv;
  omx_base_video_PortType *pPortV;
  omx_base_audio_PortType *pPortA;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  RM_RegisterComponent((char *) RTMPSRC_COMP_NAME, MAX_RTMPSRC_COMPONENTS);

  if (!openmaxStandComp->pComponentPrivate) {
    openmaxStandComp->pComponentPrivate = (omx_rtmpsrc_component_PrivateType *) calloc(1, sizeof(omx_rtmpsrc_component_PrivateType));
    if (openmaxStandComp->pComponentPrivate == NULL) {
      return OMX_ErrorInsufficientResources;
    }
  }

  compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  compPriv->ports = NULL;

  omxErr = omx_base_source_Constructor(openmaxStandComp, cComponentName);
  if (omxErr != OMX_ErrorNone) {
    return OMX_ErrorInsufficientResources;
  }

  compPriv->sPortTypesParam[OMX_PortDomainVideo].nStartPortNumber = VIDEO_PORT_INDEX;
  compPriv->sPortTypesParam[OMX_PortDomainVideo].nPorts = 1;

  compPriv->sPortTypesParam[OMX_PortDomainAudio].nStartPortNumber = AUDIO_PORT_INDEX;
  compPriv->sPortTypesParam[OMX_PortDomainAudio].nPorts = 1;

  compPriv->sPortTypesParam[OMX_PortDomainOther].nStartPortNumber = CLOCK_PORT_INDEX;
  compPriv->sPortTypesParam[OMX_PortDomainOther].nPorts = 1;

  if ((compPriv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
       compPriv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
       compPriv->sPortTypesParam[OMX_PortDomainOther].nPorts) &&
      !compPriv->ports) {
    compPriv->ports = (omx_base_PortType**) calloc(compPriv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                                                   compPriv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                                                   compPriv->sPortTypesParam[OMX_PortDomainOther].nPorts, sizeof(omx_base_PortType**));
    if (!compPriv->ports) {
      return OMX_ErrorInsufficientResources;
    }

    compPriv->ports[VIDEO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!compPriv->ports[VIDEO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    compPriv->ports[AUDIO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!compPriv->ports[AUDIO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    compPriv->ports[CLOCK_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!compPriv->ports[CLOCK_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
  }

  base_video_port_Constructor(openmaxStandComp, &compPriv->ports[VIDEO_PORT_INDEX], VIDEO_PORT_INDEX, OMX_FALSE);
  base_audio_port_Constructor(openmaxStandComp, &compPriv->ports[AUDIO_PORT_INDEX], AUDIO_PORT_INDEX, OMX_FALSE);
  base_clock_port_Constructor(openmaxStandComp, &compPriv->ports[CLOCK_PORT_INDEX], CLOCK_PORT_INDEX, OMX_TRUE);
  compPriv->ports[CLOCK_PORT_INDEX]->sPortParam.bEnabled = OMX_FALSE;

  pPortV = (omx_base_video_PortType *) compPriv->ports[VIDEO_PORT_INDEX];
  pPortA = (omx_base_audio_PortType *) compPriv->ports[AUDIO_PORT_INDEX];

  pPortV->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;
  pPortA->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;

  compPriv->BufferMgmtCallback = omx_rtmpsrc_component_BufferMgmtCallback;
  compPriv->BufferMgmtFunction = omx_base_source_twoport_BufferMgmtFunction;

  compPriv->destructor = omx_rtmpsrc_component_Destructor;
  compPriv->messageHandler = omx_rtmpsrc_component_MessageHandler;

  ++noRtmpsrcInstance;
  if (noRtmpsrcInstance > MAX_RTMPSRC_COMPONENTS) {
    return OMX_ErrorInsufficientResources;
  }

  openmaxStandComp->SetParameter = omx_rtmpsrc_component_SetParameter;
  openmaxStandComp->GetParameter = omx_rtmpsrc_component_GetParameter;
  openmaxStandComp->GetExtensionIndex = omx_rtmpsrc_component_GetExtensionIndex;

  compPriv->pTmpOutputBuffer = (OMX_BUFFERHEADERTYPE *) calloc(1, sizeof(OMX_BUFFERHEADERTYPE));
  if (!compPriv->pTmpOutputBuffer) {
    return OMX_ErrorInsufficientResources;
  }
  compPriv->pTmpOutputBuffer->pBuffer = (OMX_U8 *) calloc(DEFAULT_OUT_BUFFER_SIZE, 1);
  compPriv->pTmpOutputBuffer->nFilledLen = 0;
  compPriv->pTmpOutputBuffer->nAllocLen = DEFAULT_OUT_BUFFER_SIZE;
  compPriv->pTmpOutputBuffer->nOffset = 0;

  compPriv->sInputUrl = (OMX_STRING) calloc(DEFAULT_URL_LENGTH, 1);
  if (!compPriv->sInputUrl) {
    return OMX_ErrorInsufficientResources;
  }

  return omxErr;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *openmaxStandComp)
{
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  OMX_U32 i;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  if (compPriv->sInputUrl) {
    free(compPriv->sInputUrl);
    compPriv->sInputUrl = NULL;
  }

  if (compPriv->pTmpOutputBuffer) {
    free(compPriv->pTmpOutputBuffer);
    compPriv->pTmpOutputBuffer = NULL;
  }

  if (compPriv->ports) {
    for (i = 0; i < compPriv->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                    compPriv->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                    compPriv->sPortTypesParam[OMX_PortDomainOther].nPorts; ++i) {
      if (compPriv->ports[i]) {
        compPriv->ports[i]->PortDestructor(compPriv->ports[i]);
        compPriv->ports[i] = NULL;
      }
    }
    free(compPriv->ports);
    compPriv->ports = NULL;
  }

  --noRtmpsrcInstance;
  return omx_base_source_Destructor(openmaxStandComp);
}

void omx_rtmpsrc_component_BufferMgmtCallback(OMX_COMPONENTTYPE *openmaxStandComp, OMX_BUFFERHEADERTYPE *pOutputBuffer)
{
}

OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR ComponentParameterStructure)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  OMX_U32 nUrlLength;

  OMX_COMPONENTTYPE *openmaxStandComp = (OMX_COMPONENTTYPE *) hComponent;
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;

  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Setting parameter %i\n", __func__, nParamIndex);

  if (ComponentParameterStructure == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch ((long) nParamIndex) {
  case OMX_IndexVendorInputUrl:
    nUrlLength = strlen(((char *) ComponentParameterStructure)) + 1;
    if (nUrlLength > DEFAULT_URL_LENGTH) {
      free(compPriv->sInputUrl);
      compPriv->sInputUrl = (char *) malloc(nUrlLength);
    }
    strcpy(compPriv->sInputUrl, (char *) ComponentParameterStructure);
    break;
  default:
    return omx_base_component_SetParameter(hComponent, nParamIndex, ComponentParameterStructure);
  }
  return omxErr;
}

OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR ComponentParameterStructure)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE *pVideoPortParam, *pAudioPortParam;
  OMX_VIDEO_PARAM_PORTFORMATTYPE *pVideoPortFormat;
  OMX_AUDIO_PARAM_PORTFORMATTYPE *pAudioPortFormat;

  OMX_COMPONENTTYPE *openmaxStandComp = (OMX_COMPONENTTYPE *) hComponent;
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  omx_base_video_PortType *pVideoPort = (omx_base_video_PortType *) compPriv->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX];
  omx_base_audio_PortType *pAudioPort = (omx_base_audio_PortType *) compPriv->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX_1];

  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Getting parameter %i\n", __func__, nParamIndex);

  if (ComponentParameterStructure == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch ((long) nParamIndex) {
  case OMX_IndexParamVideoInit:
    pVideoPortParam = (OMX_PORT_PARAM_TYPE *) ComponentParameterStructure;
    if ((omxErr = checkHeader(ComponentParameterStructure, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    pVideoPortParam->nStartPortNumber = VIDEO_PORT_INDEX;
    pVideoPortParam->nPorts = 1;
    break;
  case OMX_IndexParamVideoPortFormat:
    pVideoPortFormat = (OMX_VIDEO_PARAM_PORTFORMATTYPE *) ComponentParameterStructure;
    if ((omxErr = checkHeader(ComponentParameterStructure, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (pVideoPortFormat->nPortIndex < 1) {
      memcpy(pVideoPortFormat, &pVideoPort->sVideoParam, sizeof(OMX_VIDEO_PARAM_PORTFORMATTYPE));
    } else {
      return OMX_ErrorBadParameter;
    }
    break;
  case OMX_IndexParamAudioInit:
    pAudioPortParam = (OMX_PORT_PARAM_TYPE *) ComponentParameterStructure;
    if ((omxErr = checkHeader(ComponentParameterStructure, sizeof(OMX_PORT_PARAM_TYPE))) != OMX_ErrorNone) {
      break;
    }
    pAudioPortParam->nStartPortNumber = AUDIO_PORT_INDEX;
    pAudioPortParam->nPorts = 1;
    break;
  case OMX_IndexParamAudioPortFormat:
    pAudioPortFormat = (OMX_AUDIO_PARAM_PORTFORMATTYPE *) ComponentParameterStructure;
    if ((omxErr = checkHeader(ComponentParameterStructure, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE))) != OMX_ErrorNone) {
      break;
    }
    if (pAudioPortFormat->nPortIndex <= 1) {
      memcpy(pAudioPortFormat, &pAudioPort->sAudioParam, sizeof(OMX_AUDIO_PARAM_PORTFORMATTYPE));
    } else {
      return OMX_ErrorBadParameter;
    }
    break;
  case OMX_IndexVendorInputUrl:
    strcpy((char *) ComponentParameterStructure, compPriv->sInputUrl);
    break;
  default:
      return omx_base_component_GetParameter(hComponent, nParamIndex, ComponentParameterStructure);
  }
  return omxErr;
}

OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *pIndexType)
{
  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Get extension index %s\n", __func__, cParameterName);

  if (!strcmp(cParameterName, "OMX.ST.index.param.inputurl")) {
    *pIndexType = (OMX_INDEXTYPE) OMX_IndexVendorInputUrl;
  } else {
    return OMX_ErrorBadParameter;
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_rtmpsrc_component_MessageHandler(OMX_COMPONENTTYPE *openmaxStandComp, internalRequestMessageType *message)
{
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  OMX_STATETYPE oldState = compPriv->state;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  omxErr = omx_base_component_MessageHandler(openmaxStandComp, message);

  if (message->messageType == OMX_CommandStateSet) {
    if ((message->messageParam == OMX_StateExecuting) && (oldState == OMX_StateIdle)) {
      omxErr = omx_rtmpsrc_component_Init(openmaxStandComp);
      if (omxErr != OMX_ErrorNone) {
        DEBUG(DEB_LEV_ERR, "In %s Rtmpsrc Init failed Error=%x\n",
              __func__, omxErr);
        return omxErr;
      }
    } else if ((message->messageParam == OMX_StateIdle) && (oldState == OMX_StateExecuting)) {
      omxErr = omx_rtmpsrc_component_Deinit(openmaxStandComp);
      if (omxErr != OMX_ErrorNone) {
        DEBUG(DEB_LEV_ERR, "In %s Rtmpsrc Deinit failed Error=%x\n",
              __func__, omxErr);
        return omxErr;
      }
    }
  }

  return omxErr;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Init(OMX_COMPONENTTYPE *openmaxStandComp)
{
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  omx_base_video_PortType *pPortV;
  omx_base_audio_PortType *pPortA;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

#if 0
  compPriv->pRTMP = RTMP_Alloc();
  RTMP_Init(compPriv->pRTMP);
#endif
  return OMX_ErrorNone;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Deinit(OMX_COMPONENTTYPE *openmaxStandComp)
{
  omx_rtmpsrc_component_PrivateType *compPriv = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

#if 0
  RTMP_Close(compPriv->pRTMP);
  RTMP_Free(compPriv->pRTMP);
#endif
  return OMX_ErrorNone;
}
