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

static void omx_rtmpsrc_component_BufferMgmtCallback(OMX_COMPONENTTYPE *openmaxStandComp, OMX_BUFFERHEADERTYPE *pOutputBuffer);
static OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR ComponentParameterStructure);
static OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR ComponentParameterStructure);
static OMX_ERRORTYPE omx_rtmpsrc_component_SetConfig(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nIndex,
    OMX_IN OMX_PTR pComponentConfigStructure);
static OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *pIndexType);

OMX_ERRORTYPE omx_rtmpsrc_component_Constructor(OMX_COMPONENTTYPE *openmaxStandComp, OMX_STRING cComponentName)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  omx_base_video_PortType *pPortV;
  omx_base_audio_PortType *pPortA;
  omx_rtmpsrc_component_PrivateType *omx_rtmpsrc_component_Private;
  OMX_U32 i;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  RM_RegisterComponent((char *) RTMPSRC_COMP_NAME, MAX_RTMPSRC_COMPONENTS);

  if (!openmaxStandComp->pComponentPrivate) {
    openmaxStandComp->pComponentPrivate =
      (omx_rtmpsrc_component_PrivateType *) calloc(1, sizeof(omx_rtmpsrc_component_PrivateType));
    if (openmaxStandComp->pComponentPrivate == NULL) {
      return OMX_ErrorInsufficientResources;
    }
  }

  omx_rtmpsrc_component_Private =
    (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  omx_rtmpsrc_component_Private->ports = NULL;

  omxErr = omx_base_source_Constructor(openmaxStandComp, cComponentName);
  if (omxErr != OMX_ErrorNone) {
    return OMX_ErrorInsufficientResources;
  }

  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nStartPortNumber = VIDEO_PORT_INDEX;
  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts = 1;

  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nStartPortNumber = AUDIO_PORT_INDEX;
  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts = 1;

  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nStartPortNumber = CLOCK_PORT_INDEX;
  omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts = 1;

  if ((omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts +
       omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts +
       omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts) &&
      !omx_rtmpsrc_component_Private->ports) {
    omx_rtmpsrc_component_Private->ports = (omx_base_PortType**) calloc(omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                                                                        omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                                                                        omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts, sizeof(omx_base_PortType**));
    if (!omx_rtmpsrc_component_Private->ports) {
      return OMX_ErrorInsufficientResources;
    }

    omx_rtmpsrc_component_Private->ports[VIDEO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!omx_rtmpsrc_component_Private->ports[VIDEO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    omx_rtmpsrc_component_Private->ports[AUDIO_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!omx_rtmpsrc_component_Private->ports[AUDIO_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
    omx_rtmpsrc_component_Private->ports[CLOCK_PORT_INDEX] = (omx_base_PortType *) calloc(1, sizeof(omx_base_video_PortType));
    if (!omx_rtmpsrc_component_Private->ports[CLOCK_PORT_INDEX]) {
      return OMX_ErrorInsufficientResources;
    }
  }

  base_video_port_Constructor(openmaxStandComp, &omx_rtmpsrc_component_Private->ports[VIDEO_PORT_INDEX], VIDEO_PORT_INDEX, OMX_FALSE);
  base_audio_port_Constructor(openmaxStandComp, &omx_rtmpsrc_component_Private->ports[AUDIO_PORT_INDEX], AUDIO_PORT_INDEX, OMX_FALSE);
  base_clock_port_Constructor(openmaxStandComp, &omx_rtmpsrc_component_Private->ports[CLOCK_PORT_INDEX], CLOCK_PORT_INDEX, OMX_TRUE);
  omx_rtmpsrc_component_Private->ports[CLOCK_PORT_INDEX]->sPortParam.bEnabled = OMX_FALSE;

  pPortV = (omx_base_video_PortType *) omx_rtmpsrc_component_Private->ports[VIDEO_PORT_INDEX];
  pPortA = (omx_base_audio_PortType *) omx_rtmpsrc_component_Private->ports[AUDIO_PORT_INDEX];

  pPortV->sPortParam.nBufferSize = DEFAULT_OUT_BUFFER_SIZE;
  pPortA->sPortParam.nBufferSize = DEFAULT_IN_BUFFER_SIZE;

  omx_rtmpsrc_component_Private->BufferMgmtCallback = omx_rtmpsrc_component_BufferMgmtCallback;
  omx_rtmpsrc_component_Private->BufferMgmtFunction = omx_base_source_twoport_BufferMgmtFunction;

  setHeader(&omx_rtmpsrc_component_Private->sTimeStamp, sizeof(OMX_TIME_CONFIG_TIMESTAMPTYPE));
  omx_rtmpsrc_component_Private->sTimeStamp.nPortIndex = 0;
  omx_rtmpsrc_component_Private->sTimeStamp.nTimestamp = 0x0;

  omx_rtmpsrc_component_Private->destructor = omx_rtmpsrc_component_Destructor;
  omx_rtmpsrc_component_Private->messageHandler = omx_rtmpsrc_component_MessageHandler;

  ++noRtmpsrcInstance;
  if (noRtmpsrcInstance > MAX_RTMPSRC_COMPONENTS) {
    return OMX_ErrorInsufficientResources;
  }

  openmaxStandComp->SetParameter = omx_rtmpsrc_component_SetParameter;
  openmaxStandComp->GetParameter = omx_rtmpsrc_component_GetParameter;
  openmaxStandComp->SetConfig = omx_rtmpsrc_component_SetConfig;
  openmaxStandComp->GetExtensionIndex = omx_rtmpsrc_component_GetExtensionIndex;

  omx_rtmpsrc_component_Private->pTmpOutputBuffer = (OMX_BUFFERHEADERTYPE *) calloc(1, sizeof(OMX_BUFFERHEADERTYPE));
  if (!omx_rtmpsrc_component_Private->pTmpOutputBuffer) {
    return OMX_ErrorInsufficientResources;
  }
  omx_rtmpsrc_component_Private->pTmpOutputBuffer->pBuffer = (OMX_U8 *) calloc(DEFAULT_OUT_BUFFER_SIZE, 1);
  omx_rtmpsrc_component_Private->pTmpOutputBuffer->nFilledLen = 0;
  omx_rtmpsrc_component_Private->pTmpOutputBuffer->nAllocLen = DEFAULT_OUT_BUFFER_SIZE;
  omx_rtmpsrc_component_Private->pTmpOutputBuffer->nOffset = 0;

  omx_rtmpsrc_component_Private->sInputUrl = (OMX_STRING) malloc(DEFAULT_URL_LENGTH);
  if (!omx_rtmpsrc_component_Private->sInputUrl) {
    return OMX_ErrorInsufficientResources;
  }

  return omxErr;
}

OMX_ERRORTYPE omx_rtmpsrc_component_Destructor(OMX_COMPONENTTYPE *openmaxStandComp)
{
  omx_rtmpsrc_component_PrivateType *omx_rtmpsrc_component_Private = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  OMX_U32 i;

  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  if (omx_rtmpsrc_component_Private->sInputUrl) {
    free(omx_rtmpsrc_component_Private->sInputUrl);
    omx_rtmpsrc_component_Private->sInputUrl = NULL;
  }

  if (omx_rtmpsrc_component_Private->pTmpOutputBuffer) {
    free(omx_rtmpsrc_component_Private->pTmpOutputBuffer);
    omx_rtmpsrc_component_Private->pTmpOutputBuffer = NULL;
  }

  if (omx_rtmpsrc_component_Private->ports) {
    for (i = 0; i < omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                    omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                    omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts; ++i) {
      if (omx_rtmpsrc_component_Private->ports[i]) {
        omx_rtmpsrc_component_Private->ports[i]->PortDestructor(omx_rtmpsrc_component_Private->ports[i]);
        omx_rtmpsrc_component_Private->ports[i] = NULL;
      }
    }
    free(omx_rtmpsrc_component_Private->ports);
    omx_rtmpsrc_component_Private->ports = NULL;
  }

  --noRtmpsrcInstance;
  return omx_base_source_Destructor(openmaxStandComp);
}

static void omx_rtmpsrc_component_BufferMgmtCallback(OMX_COMPONENTTYPE *openmaxStandComp, OMX_BUFFERHEADERTYPE *pOutputBuffer)
{
}

static OMX_ERRORTYPE omx_rtmpsrc_component_SetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_IN OMX_PTR ComponentParameterStructure)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  OMX_U32 nUrlLength;

  OMX_COMPONENTTYPE *openmaxStandComp = (OMX_COMPONENTTYPE *) hComponent;
  omx_rtmpsrc_component_PrivateType *omx_rtmpsrc_component_Private = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;

  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Setting parameter %i\n", __func__, nParamIndex);

  if (ComponentParameterStructure == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch (nParamIndex) {
  case OMX_IndexVendorInputFilename:
    nUrlLength = strlen(((char *) ComponentParameterStructure)) + 1;
    if (nUrlLength > DEFAULT_URL_LENGTH) {
      free(omx_rtmpsrc_component_Private->sInputUrl);
      omx_rtmpsrc_component_Private->sInputUrl = (char *) malloc(nUrlLength);
    }
    strcpy(omx_rtmpsrc_component_Private->sInputUrl, (char *) ComponentParameterStructure);
    break;
  default:
    return omx_base_component_SetParameter(hComponent, nParamIndex, ComponentParameterStructure);
  }
  return omxErr;
}

static OMX_ERRORTYPE omx_rtmpsrc_component_GetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nParamIndex,
    OMX_INOUT OMX_PTR ComponentParameterStructure)
{
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;
  OMX_PORT_PARAM_TYPE *pVideoPortParam, *pAudioPortParam;
  OMX_VIDEO_PARAM_PORTFORMATTYPE *pVideoPortFormat;
  OMX_AUDIO_PARAM_PORTFORMATTYPE *pAudioPortFormat;

  OMX_COMPONENTTYPE *openmaxStandComp = (OMX_COMPONENTTYPE *) hComponent;
  omx_rtmpsrc_component_PrivateType *omx_rtmpsrc_component_Private = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  omx_base_video_PortType *pVideoPort = (omx_base_video_PortType *) omx_rtmpsrc_component_Private->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX];
  omx_base_audio_PortType *pAudioPort = (omx_base_audio_PortType *) omx_rtmpsrc_component_Private->ports[OMX_BASE_SOURCE_OUTPUTPORT_INDEX_1];

  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Getting parameter %i\n", __func__, nParamIndex);

  if (ComponentParameterStructure == NULL) {
    return OMX_ErrorBadParameter;
  }

  switch (nParamIndex) {
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
  case OMX_IndexVendorInputFilename:
    strcpy((char *) ComponentParameterStructure, omx_rtmpsrc_component_Private->sInputUrl);
    break;
  default:
      return omx_base_component_GetParameter(hComponent, nParamIndex, ComponentParameterStructure);
  }
  return omxErr;
}

static OMX_ERRORTYPE omx_rtmpsrc_component_SetConfig(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE nIndex,
    OMX_IN OMX_PTR pComponentConfigStructure)
{
  OMX_TIME_CONFIG_TIMESTAMPTYPE *sTimeStamp;
  OMX_COMPONENTTYPE *openmaxStandComp = (OMX_COMPONENTTYPE *) hComponent;
  omx_rtmpsrc_component_PrivateType *omx_rtmpsrc_component_Private = (omx_rtmpsrc_component_PrivateType *) openmaxStandComp->pComponentPrivate;
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;

  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Set config %i\n", __func__, nIndex);

  switch (nIndex) {
  case OMX_IndexConfigTimePosition:
    sTimeStamp = (OMX_TIME_CONFIG_TIMESTAMPTYPE *) pComponentConfigStructure;
    if (sTimeStamp->nPortIndex >= (omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                                   omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                                   omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts)) {
      DEBUG(DEB_LEV_ERR, "Bad port index %i when the component has %i ports\n",
            (int) sTimeStamp->nPortIndex, omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainVideo].nPorts +
                                          omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainAudio].nPorts +
                                          omx_rtmpsrc_component_Private->sPortTypesParam[OMX_PortDomainOther].nPorts);
      return OMX_ErrorBadPortIndex;
    }

    omxErr = checkHeader(sTimeStamp, sizeof(OMX_TIME_CONFIG_TIMESTAMPTYPE));
    if (omxErr != OMX_ErrorNone) {
      return omxErr;
    }

    memcpy(&omx_rtmpsrc_component_Private->sTimeStamp, sTimeStamp, sizeof(OMX_TIME_CONFIG_TIMESTAMPTYPE));
    break;
  default:
    return omx_base_component_SetConfig(hComponent, nIndex, pComponentConfigStructure);
  }
  return omxErr;
}

static OMX_ERRORTYPE omx_rtmpsrc_component_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_STRING cParameterName,
    OMX_OUT OMX_INDEXTYPE *pIndexType)
{
  DEBUG(DEB_LEV_SIMPLE_SEQ, "In %s Get extension index %s\n", __func__, cParameterName);

  if (!strcmp(cParameterName, "OMX.ST.index.param.inputfilename")) {
    *pIndexType = (OMX_INDEXTYPE) OMX_IndexVendorInputFilename;
  } else {
    return OMX_ErrorBadParameter;
  }
  return OMX_ErrorNone;
}
