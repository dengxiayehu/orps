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
    DEBUG(DEB_LEV_ERR, "The OpenMAX core can not be initialized. Exiting...\n");
    exit(EXIT_FAILURE);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Omx core is initialized\n");
  }

  DEBUG(DEFAULT_MESSAGES, "------------------------------------\n");
  test_OMX_ComponentNameEnum();

  DEBUG(DEFAULT_MESSAGES, "Using rtmpsrc\n");
  omxErr = OMX_GetHandle(&appPriv->rtmpsrchandle, (OMX_STRING) RTMP_SRC, appPriv, &rtmpsrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc Component Not Found\n");
    exit(1);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Rtmpsrc Component Found\n");
  }

  omxErr = OMX_GetHandle(&appPriv->clocksrchandle, (OMX_STRING) CLOCK_SRC, appPriv, &clocksrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Clocksrc Component Not Found\n");
    exit(1);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Clocksrc Component Found\n");
  }

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandPortEnable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc Clock Port Enable failed\n");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  DEBUG(DEFAULT_MESSAGES, "In %s Rtmpsrc Clock Port Enabled\n", __func__);

  omxErr = OMX_GetExtensionIndex(appPriv->rtmpsrchandle, (OMX_STRING) "OMX.ST.index.param.inputurl",
                                 &eIndexParamUrl);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Error in get extension index\n");
    exit(1);
  } else {
    char url[1024];
    DEBUG(DEFAULT_MESSAGES, "Url Param Index: %x\n", eIndexParamUrl);
    omxErr = OMX_SetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, (OMX_PTR) TEST_RTMP_URL);
    if (omxErr != OMX_ErrorNone) {
      DEBUG(DEB_LEV_ERR, "Error in input format\n");
      exit(1);
    }
    OMX_GetParameter(appPriv->rtmpsrchandle, eIndexParamUrl, url);
    DEBUG(DEFAULT_MESSAGES, "Test url set to: \"%s\"\n", url);
  }

  omxErr = OMX_SetupTunnel(appPriv->clocksrchandle, RTMPSRC_PORT_INDEX, appPriv->rtmpsrchandle, RTMPSRC_PORT_INDEX);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Setup Tunnel btwn clock and rtmpsrc Failed\n");
    exit(1);
  } else {
    DEBUG(DEB_LEV_ERR, "Setup Tunnel btwn clock and rtmpsrc successfully\n");
  }

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandPortDisable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc clock port disable failed\n");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  DEBUG(DEFAULT_MESSAGES, "In %s Rtmpsrc Clock Port Disabled\n", __func__);
  
  omxErr = OMX_SendCommand(appPriv->clocksrchandle, OMX_CommandPortDisable, 2, NULL);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Clocksrc component's clock port (tunneled to parser's clock port) disable failed\n\n");
    exit(1);
  }
  tsem_down(appPriv->clockEventSem);
  DEBUG(DEFAULT_MESSAGES, "In %s clocksrc Clock Port (connected to parser) Disabled\n", __func__);

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc Set to Idle Failed\n");
    exit(1);
  }

  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[0], VIDEO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcVideo[1], VIDEO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[0], AUDIO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);
  omxErr = OMX_AllocateBuffer(appPriv->rtmpsrchandle, &appPriv->outBufferRtmpsrcAudio[1], AUDIO_PORT_INDEX, appPriv, BUFFER_OUT_SIZE);

  tsem_down(appPriv->rtmpsrcEventSem);
  DEBUG(DEFAULT_MESSAGES, "Rtmpsrc in idle state\n");

  omxErr = OMX_SendCommand(appPriv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc Set to Executing Failed\n");
    exit(1);
  }
  tsem_down(appPriv->rtmpsrcEventSem);
  DEBUG(DEFAULT_MESSAGES, "Rtmpsrc in Executing state\n");

  tsem_down(appPriv->rtmpsrcEventSem);
  tsem_down(appPriv->rtmpsrcEventSem);
  DEBUG(DEFAULT_MESSAGES,"Rtmpsrc Port Settings Changed event \n");

  return 0;
}

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void)
{
  char *name;
  OMX_U32 index;
  OMX_ERRORTYPE omxErr = OMX_ErrorNone;

  DEBUG(DEFAULT_MESSAGES, "GENERAL TEST %s\n", __func__);
  name = (char *) malloc(OMX_MAX_STRINGNAME_SIZE);
  index = 0;
  for ( ; ; ) {
    omxErr = OMX_ComponentNameEnum(name, OMX_MAX_STRINGNAME_SIZE, index);
    if ((name != NULL) && (omxErr == OMX_ErrorNone)) {
      DEBUG(DEFAULT_MESSAGES, "component %i is %s\n", index, name);
    } else break;
    ++index;
  }
  free(name);
  DEBUG(DEFAULT_MESSAGES, "GENERAL TEST %s result: %s\n",
        __func__, omxErr == OMX_ErrorNoMore ? "PASS" : "FAILURE");
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

  DEBUG(DEFAULT_MESSAGES, "Hi there, I am in %s callback\n", __func__);

  if (eEvent == OMX_EventCmdComplete) {
    if (Data1 == OMX_CommandStateSet) {
      DEBUG(DEFAULT_MESSAGES, "Rtmpsrc State Changed in ");
      switch ((int) Data2) {
      case OMX_StateInvalid:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateInvalid\n");
        break;
      case OMX_StateLoaded:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateLoaded\n");
        break;
      case OMX_StateIdle:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateIdle\n");
        break;
      case OMX_StateExecuting:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateExecuting\n");
        break;
      case OMX_StatePause:
        DEBUG(DEFAULT_MESSAGES, "OMX_StatePause\n");
        break;
      case OMX_StateWaitForResources:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateWaitForResources\n");
        break;
      }
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortEnable) {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Port Enable Event\n", __func__);
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandPortDisable) {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Port Disable Event\n", __func__);
      tsem_up(appPriv->rtmpsrcEventSem);
    } else if (Data1 == OMX_CommandFlush) {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Flush Event\n", __func__);
      tsem_up(appPriv->rtmpsrcEventSem);
    } else {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Event Event=%d Data1=%d Data2=%d\n",
            __func__, eEvent, (int) Data1, (int) Data2);
    }
  } else if (eEvent == OMX_EventPortSettingsChanged) {
  } else if (eEvent == OMX_EventPortFormatDetected) {
    DEBUG(DEFAULT_MESSAGES, "In %s Port Format Detected %x\n", __func__, (int) Data1);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Param1 is %i\n", (int) Data1);
    DEBUG(DEFAULT_MESSAGES, "Param2 is %i\n", (int) Data2);
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

  DEBUG(DEFAULT_MESSAGES, "Hi there, I am in the %s callback\n", __func__);

  if (eEvent == OMX_EventCmdComplete) {
    if (Data1 == OMX_CommandStateSet) {
      DEBUG(DEFAULT_MESSAGES, "Clock Component State Changed in ");
      switch ((int) Data2) {
      case OMX_StateInvalid:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateInvalid\n");
        break;
      case OMX_StateLoaded:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateLoaded\n");
        break;
      case OMX_StateIdle:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateIdle\n");
        break;
      case OMX_StateExecuting:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateExecuting\n");
        break;
      case OMX_StatePause:
        DEBUG(DEFAULT_MESSAGES, "OMX_StatePause\n");
        break;
      case OMX_StateWaitForResources:
        DEBUG(DEFAULT_MESSAGES, "OMX_StateWaitForResources\n");
        break;
      }
      tsem_up(appPriv->clockEventSem);
    } else if (Data1 == OMX_CommandPortEnable) {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Port Enable Event\n", __func__);
      tsem_up(appPriv->clockEventSem);
    } else if (Data1 == OMX_CommandPortDisable) {
      DEBUG(DEFAULT_MESSAGES, "In %s Received Port Disable Event\n", __func__);
      tsem_up(appPriv->clockEventSem);
    } else {
      DEBUG(DEFAULT_MESSAGES,"In %s Received Event Event=%d Data1=%d Data2=%d\n",
            __func__, eEvent, (int) Data1, (int) Data2);
    }
  } else if(eEvent == OMX_EventPortSettingsChanged) {
    DEBUG(DEFAULT_MESSAGES,"Clock src Port Setting Changed event\n");
    tsem_up(appPriv->clockEventSem);
  } else if(eEvent == OMX_EventPortFormatDetected) {
    DEBUG(DEFAULT_MESSAGES, "In %s Port Format Detected %x\n", __func__, (int) Data1);
  } else if(eEvent == OMX_EventBufferFlag) {
    DEBUG(DEFAULT_MESSAGES, "In %s OMX_BUFFERFLAG_EOS\n", __func__);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Param1 is %i\n", (int) Data1);
    DEBUG(DEFAULT_MESSAGES, "Param2 is %i\n", (int) Data2);
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
