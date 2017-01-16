#include <xlog.h>

#include "omxrtmpsrctest.h"

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void);
static OMX_CALLBACKTYPE rtmpsrccallbacks = {
  .EventHandler     = rtmpsrcEventHandler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = rtmpsrcFillBufferDone
};

int main(int argc, const char *argv[])
{
  appPrivateType *appPriv;
  OMX_ERRORTYPE omxErr;
  OMX_INDEXTYPE eIndexParamUrl;

  xlog::log_add_dst("./omxrtmpsrctest.log");

  appPriv = (appPrivateType *) malloc(sizeof(appPrivateType));
  appPriv->rtmpsrcEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->eofSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->bEOS = OMX_FALSE;

  tsem_init(appPriv->rtmpsrcEventSem, 0);
  tsem_init(appPriv->eofSem, 0);

  omxErr = OMX_Init();
  if (omxErr != OMX_ErrorNone) {
    LOGE("The OpenMAX core can not be initialized. Exiting...");
    exit(EXIT_FAILURE);
  }
  LOGI("Omx core is initialized");

  LOGI("------------------------------------");
  test_OMX_ComponentNameEnum();

  LOGI("Using rtmpsrc");
  omxErr = OMX_GetHandle(&appPriv->rtmpsrchandle, (OMX_STRING) "OMX.st.rtmpsrc", appPriv, &rtmpsrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc component not found");
    exit(1);
  }
  LOGI("Rtmpsrc component found");

  omxErr = OMX_GetExtensionIndex(appPriv->rtmpsrchandle, (OMX_STRING) "OMX.ST.index.param.inputurl",
                                 &eIndexParamUrl);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Error in get extension index");
    exit(1);
  }

  char url[1024];
  LOGI("Url param index: %x", eIndexParamUrl);
  omxErr = OMX_SetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, (OMX_PTR) "rtmp://127.0.0.1/live/va");
  if (omxErr != OMX_ErrorNone) {
    LOGE("Error in input format");
    exit(1);
  }
  OMX_GetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, url);
  LOGI("Test url set to: %s\"", url);

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc set to idle failed");
    exit(1);
  }
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[0], 0, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[1], 0, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[0], 1, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[1], 1, appPriv, BUFFER_OUT_SIZE);
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in idle state");

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc set to executing failed");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in executing state");

  omxErr = OMX_FillThisBuffer(appPriv->rtmpsrchandle, appPriv->outBufferRtmpsrcVideo[0]);
  omxErr = OMX_FillThisBuffer(appPriv->rtmpsrchandle, appPriv->outBufferRtmpsrcVideo[1]);
  omxErr = OMX_FillThisBuffer(appPriv->rtmpsrchandle, appPriv->outBufferRtmpsrcAudio[0]);
  omxErr = OMX_FillThisBuffer(appPriv->rtmpsrchandle, appPriv->outBufferRtmpsrcAudio[1]);

  LOGI("Waiting for EOS = %d", appPriv->eofSem->semval);
  tsem_down(appPriv->eofSem);

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in idle state");

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateLoaded, NULL);
  omxErr = OMX_FreeBuffer(appPriv->rtmpsrchandle, 0, appPriv->outBufferRtmpsrcVideo[0]);
  omxErr = OMX_FreeBuffer(appPriv->rtmpsrchandle, 0, appPriv->outBufferRtmpsrcVideo[1]);
  omxErr = OMX_FreeBuffer(appPriv->rtmpsrchandle, 1, appPriv->outBufferRtmpsrcAudio[0]);
  omxErr = OMX_FreeBuffer(appPriv->rtmpsrchandle, 1, appPriv->outBufferRtmpsrcAudio[1]);
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in loaded state");

  OMX_FreeHandle(appPriv->rtmpsrchandle);

  OMX_Deinit();

  free(appPriv->rtmpsrcEventSem);
  appPriv->rtmpsrcEventSem = NULL;
  free(appPriv->eofSem);
  appPriv->eofSem = NULL;

  free(appPriv);
  appPriv = NULL;

  xlog::log_close();
  return 0;
}

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void)
{
  char *name;
  OMX_U32 index;
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;

  LOGI("GENERAL TEST");
  name = (char *) malloc(OMX_MAX_STRINGNAME_SIZE);
  index = 0;
  for ( ; ; ) {
    omxErr = OMX_ComponentNameEnum(name, OMX_MAX_STRINGNAME_SIZE, index);
    if ((name != NULL) && (omxErr == OMX_ErrorNone)) {
      LOGI("component %i is %s", index, name);
    } else break;
    ++index;
  }
  free(name);
  LOGI("GENERAL TEST result: %s",
       omxErr == OMX_ErrorNoMore ? "PASS" : "FAILURE");
  return omxErr;
}

OMX_ERRORTYPE rtmpsrcEventHandler(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_EVENTTYPE eEvent,
    OMX_OUT OMX_U32 Data1,
    OMX_OUT OMX_U32 Data2,
    OMX_OUT OMX_PTR pEventData)
{
  appPrivateType *appPriv = (appPrivateType *) pAppData;

  if (eEvent == OMX_EventCmdComplete) {
    if (Data1 == OMX_CommandStateSet) {
      switch ((int) Data2) {
      case OMX_StateInvalid:
        LOGI("Rtmpsrc state changed in OMX_StateInvalid");
        break;
      case OMX_StateLoaded:
        LOGI("Rtmpsrc state changed in OMX_StateLoaded");
        break;
      case OMX_StateIdle:
        LOGI("Rtmpsrc state changed in OMX_StateIdle");
        break;
      case OMX_StateExecuting:
        LOGI("Rtmpsrc state changed in OMX_StateExecuting");
        break;
      case OMX_StatePause:
        LOGI("Rtmpsrc state changed in OMX_StatePause");
        break;
      case OMX_StateWaitForResources:
        LOGI("Rtmpsrc state changed in OMX_StateWaitForResources");
        break;
      }
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortEnable) {
      LOGI("Received port enable event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortDisable) {
      LOGI("Received port disable event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandFlush) {
      LOGI("Received flush event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else {
      LOGI("Received event event=%d data1=%d data2=%d", eEvent, (int) Data1, (int) Data2);
    }
  } else if (eEvent == OMX_EventPortSettingsChanged) {
  } else if (eEvent == OMX_EventPortFormatDetected) {
    LOGI("Port format detected %x", (int) Data1);
  } else {
    LOGI("eEvent=%x, data1=%d, data2=%d", eEvent, Data1, Data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpsrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer)
{
  appPrivateType *appPriv = (appPrivateType *) pAppData;
  OMX_ERRORTYPE omxErr;

  if (pBuffer != NULL) {
    if (!appPriv->bEOS) {
      if (pBuffer->nFlags == OMX_BUFFERFLAG_EOS) {
        appPriv->bEOS = OMX_TRUE;
      } else {
        if (pBuffer->nFilledLen == 0) {
          LOGE("Ouch! No data in the output buffer");
          return OMX_ErrorNone;
        }

        pBuffer->nFilledLen = 0;
        pBuffer->nFlags = 0;

        omxErr = OMX_FillThisBuffer(hComponent, pBuffer);
        if (omxErr != OMX_ErrorNone) {
          LOGE("OMX_FillThisBuffer failed");
          return omxErr;
        }
      }
    } else {
      LOGI("eos=%x dropping this buffer", pBuffer->nFlags);
    }
  } else {
    LOGE("NULL buffer to output");
  }
  return OMX_ErrorNone;
}
