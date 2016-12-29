#include "omxrtmpsrctest.h"

#define RTMP_SRC    "OMX.st.rtmpsrc"
#define CLOCK_SRC   "OMX.st.clocksrc"
#define VIDEO_SCHD  "OMX.st.video.scheduler"

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
 
  appPriv = (appPrivateType *) malloc(sizeof(appPrivateType));
  appPriv->rtmpsrcEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->clockEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->videoschdEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  appPriv->eofSem = (tsem_t *) malloc(sizeof(tsem_t));

  tsem_init(appPriv->rtmpsrcEventSem, 0);
  tsem_init(appPriv->clockEventSem, 0);
  tsem_init(appPriv->videoschdEventSem, 0);
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

  DEBUG(DEB_LEV_SIMPLE_SEQ, "Using rtmpsrc\n");
  omxErr = OMX_GetHandle(&appPriv->rtmpsrchandle, (OMX_STRING) RTMP_SRC, appPriv, &rtmpsrccallbacks);
  if (omxErr != OMX_ErrorNone) {
    DEBUG(DEB_LEV_ERR, "Rtmpsrc Component Not Found\n");
    exit(1);
  } else {
    DEBUG(DEFAULT_MESSAGES, "Rtmpsrc Component Found\n");
  }
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
  return OMX_ErrorNoMore;
}

OMX_ERRORTYPE rtmpsrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer)
{
  return OMX_ErrorNoMore;
}
