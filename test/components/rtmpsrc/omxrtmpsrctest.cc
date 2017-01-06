#include <xlog.h>

#include "omxrtmpsrctest.h"

#define RTMP_SRC    "OMX.st.rtmpsrc"
#define CLOCK_SRC   "OMX.st.clocksrc"

#define TEST_RTMP_URL "rtmp://127.0.0.1/live/va"

#define VIDEO_PORT_INDEX    0
#define AUDIO_PORT_INDEX    1
#define RTMPSRC_PORT_INDEX  2

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void);
static OMX_CALLBACKTYPE rtmpsrccallbacks = {
  .EventHandler     = rtmpsrcEventHandler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = rtmpsrcFillBufferDone
};

static OMX_CALLBACKTYPE clocksrccallbacks = {
  .EventHandler     = clocksrcEventHandler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = clocksrcFillBufferDone
};

int main(int argc, const char *argv[])
{
  appPrivateType *appPriv;
  OMX_ERRORTYPE omxErr;
  OMX_INDEXTYPE eIndexParamUrl;

  xlog::log_add_dst("./omxrtmpsrctest.log");

  appPriv = (appPrivateType *) malloc(sizeof(appPrivateType));
  appPriv->rtmpsrcEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->clockEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->eofSem = (tsem_t *) malloc(sizeof(tsem_t));

  tsem_init(appPriv->rtmpsrcEventSem, 0);
  tsem_init(appPriv->clockEventSem, 0);
  tsem_init(appPriv->eofSem, 0);

  omxErr = OMX_Init();
  if (omxErr != OMX_ErrorNone) {
    LOGE("The OpenMAX core can not be initialized. Exiting...");
    exit(EXIT_FAILURE);
  } else {
    LOGI("Omx core is initialized");
  }

  LOGI("------------------------------------");
  test_OMX_ComponentNameEnum();

  LOGI("Using rtmpsrc");
  omxErr = OMX_GetHandle(&appPriv->rtmpsrchandle, (OMX_STRING) RTMP_SRC, appPriv, &rtmpsrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc Component Not Found");
    exit(1);
  } else {
    LOGI("Rtmpsrc Component Found");
  }

  omxErr = OMX_GetHandle(&appPriv->clocksrchandle, (OMX_STRING) CLOCK_SRC, appPriv, &clocksrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Clocksrc Component Not Found");
    exit(1);
  } else {
    LOGI("Clocksrc Component Found");
  }

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandPortEnable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc Clock Port Enable failed");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("In %s Rtmpsrc Clock Port Enabled", __func__);

  omxErr = OMX_GetExtensionIndex(appPriv->rtmpsrchandle, (OMX_STRING) "OMX.ST.index.param.inputurl",
                                 &eIndexParamUrl);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Error in get extension index");
    exit(1);
  } else {
    char url[1024];
    LOGI("Url Param Index: %x", eIndexParamUrl);
    omxErr = OMX_SetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, (OMX_PTR) TEST_RTMP_URL);
    if (omxErr != OMX_ErrorNone) {
      LOGE("Error in input format");
      exit(1);
    }
    OMX_GetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, url);
    LOGI("Test url set to: %s\"", url);
  }

  omxErr = OMX_SetupTunnel(appPriv->clocksrchandle, RTMPSRC_PORT_INDEX, appPriv->rtmpsrchandle, RTMPSRC_PORT_INDEX);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Setup Tunnel btwn clock and rtmpsrc Failed");
    exit(1);
  } else {
    LOGI("Setup Tunnel btwn clock and rtmpsrc successfully");
  }

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandPortDisable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc clock port disable failed");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc Clock Port Disabled");
  
  omxErr = OMX_SendCommand(appPriv->clocksrchandle, OMX_CommandPortDisable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Clocksrc component's clock port (tunneled to parser's clock port) disable failed");
    exit(1);
  }
  tsem_down(appPriv->clockEventSem);
  LOGI("1:clocksrc Clock Port (connected to parser) Disabled");
  LOGI("2:clocksrc Clock Port (connected to parser) Disabled");
  LOGI("3:clocksrc Clock Port (connected to parser) Disabled");

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc Set to Idle Failed");
    exit(1);
  }

  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[0], VIDEO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[1], VIDEO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[0], AUDIO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[1], AUDIO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);

  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in idle state");

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  if (omxErr != OMX_ErrorNone) {
    LOGE("Rtmpsrc Set to Executing Failed");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc in Executing state");

  tsem_down(appPriv->rtmpsrcEventSem);
  tsem_down(appPriv->rtmpsrcEventSem);
  LOGI("Rtmpsrc Port Settings Changed event ");

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
      LOGI("Rtmpsrc State Changed in ");
      switch ((int) Data2) {
      case OMX_StateInvalid:
        LOGI("OMX_StateInvalid");
        break;
      case OMX_StateLoaded:
        LOGI("OMX_StateLoaded");
        break;
      case OMX_StateIdle:
        LOGI("OMX_StateIdle");
        break;
      case OMX_StateExecuting:
        LOGI("OMX_StateExecuting");
        break;
      case OMX_StatePause:
        LOGI("OMX_StatePause");
        break;
      case OMX_StateWaitForResources:
        LOGI("OMX_StateWaitForResources");
        break;
      }
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortEnable) {
      LOGI("Received Port Enable Event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortDisable) {
      LOGI("Received Port Disable Event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandFlush) {
      LOGI("Received Flush Event");
      tsem_up(appPriv->rtmpsrcEventSem);
    } else {
      LOGI("Received Event Event=%d Data1=%d Data2=%d",
            eEvent, (int) Data1, (int) Data2);
    }
  } else if (eEvent == OMX_EventPortSettingsChanged) {
  } else if (eEvent == OMX_EventPortFormatDetected) {
    LOGI("Port Format Detected %x", (int) Data1);
  } else {
    LOGI("Param1 is %i", (int) Data1);
    LOGI("Param2 is %i", (int) Data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpsrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer)
{
  return OMX_ErrorNone;
}

OMX_ERRORTYPE clocksrcEventHandler(
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
      LOGI("Clock Component State Changed in ");
      switch ((int) Data2) {
      case OMX_StateInvalid:
        LOGI("OMX_StateInvalid");
        break;
      case OMX_StateLoaded:
        LOGI("OMX_StateLoaded");
        break;
      case OMX_StateIdle:
        LOGI("OMX_StateIdle");
        break;
      case OMX_StateExecuting:
        LOGI("OMX_StateExecuting");
        break;
      case OMX_StatePause:
        LOGI("OMX_StatePause");
        break;
      case OMX_StateWaitForResources:
        LOGI("OMX_StateWaitForResources");
        break;
      }
      tsem_up(appPriv->clockEventSem);
    } else if (Data1 == OMX_CommandPortEnable) {
      LOGI("Received Port Enable Event");
      tsem_up(appPriv->clockEventSem);
    } else if (Data1 == OMX_CommandPortDisable) {
      LOGI("Received Port Disable Event");
      tsem_up(appPriv->clockEventSem);
    } else {
      LOGI("Received Event Event=%d Data1=%d Data2=%d",
            eEvent, (int) Data1, (int) Data2);
    }
  } else if(eEvent == OMX_EventPortSettingsChanged) {
    LOGI("Clock src Port Setting Changed event");
    tsem_up(appPriv->clockEventSem);
  } else if(eEvent == OMX_EventPortFormatDetected) {
    LOGI("Port Format Detected %x", (int) Data1);
  } else if(eEvent == OMX_EventBufferFlag) {
    LOGI("OMX_BUFFERFLAG_EOS");
  } else {
    LOGI("Param1 is %i", (int) Data1);
    LOGI("Param2 is %i", (int) Data2);
  }

  xlog::log_close();
  return OMX_ErrorNone;
}

OMX_ERRORTYPE clocksrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer)
{
  return OMX_ErrorNone;
}
