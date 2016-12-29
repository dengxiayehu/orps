#include "omxrtmpsrctest.h"

#define RTMP_SRC    "OMX.st.rtmpsrc"
#define CLOCK_SRC   "OMX.st.clocksrc"
#define VIDEO_SCHD  "OMX.st.video.scheduler"

extern "C" int tsem_init(tsem_t* tsem, unsigned int val);

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
    DEBUG(DEB_LEV_SIMPLE_SEQ, "Omx core is initialized\n");
  }
  return 0;
}
