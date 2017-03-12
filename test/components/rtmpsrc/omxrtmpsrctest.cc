#include <xlog.h>
#include <xmacro.h>
#include <omx_util.h>
#include <webrtc/base/thread.h>
#include <webrtc/base/physicalsocketserver.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#include "omxrtmpsrctest.h"

class CustomSocketServer : public rtc::PhysicalSocketServer {
public:
  CustomSocketServer(rtc::Thread *thread, AppPrivateType *app_priv)
    : thread_(thread), app_priv_(app_priv) { }
  virtual ~CustomSocketServer() { }

  virtual bool Wait(int cms, bool process_io) override {
    if (app_priv_->bEOS) {
      thread_->Quit();
    }
    return rtc::PhysicalSocketServer::Wait(10, process_io);
  }

protected:
  rtc::Thread *thread_;
  AppPrivateType *app_priv_;
};

class SignalProcessThread : public rtc::Thread {
public:
  SignalProcessThread(sigset_t *set, Thread *main_thread, AppPrivateType *app_priv)
    : set_(set), main_thread_(main_thread), app_priv_(app_priv) { }
  virtual ~SignalProcessThread() { }
  virtual void Run();

private:
  sigset_t *set_;
  Thread *main_thread_;
  AppPrivateType *app_priv_;
};

class FunctorQuit {
public:
  explicit FunctorQuit(AppPrivateType *app_priv)
    : app_priv_(app_priv) { }
  void operator()() {
    app_priv_->bEOS = OMX_TRUE;
  }

private:
  AppPrivateType *app_priv_;
};

void SignalProcessThread::Run()
{
  int ret, sig;

  for ( ; ; ) {
    ret = sigwait(set_, &sig);
    if (ret != 0) {
      LOGE("sigwait failed: %s", ERRNOMSG);
      break;
    }

    if (sig == SIGINT) {
      LOGI("Program received signal %d", sig);
      FunctorQuit f(app_priv_);
      main_thread_->Invoke<void>(f);
      break;
    }
  }
}

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void);
static OMX_CALLBACKTYPE rtmpsrccallbacks = {
  .EventHandler     = rtmpsrcEventHandler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = rtmpsrcFillBufferDone
};

int main(int argc, const char *argv[])
{
  AppPrivateType *app_priv;
  OMX_ERRORTYPE omx_err;
  OMX_INDEXTYPE index_parm_url;

  xlog::log_add_dst("./omxrtmpsrctest.log");

  int ret = 0;
  sigset_t set;

  // Block SIGINT in main thread and its inheritors.
  sigemptyset(&set);
  sigaddset(&set, SIGINT);

  ret = pthread_sigmask(SIG_BLOCK, &set, NULL);
  if (ret != 0) {
    fprintf(stderr, "pthread_sigmask failed: %s\n", strerror(ret));
    return -1;
  }

  app_priv = (AppPrivateType *) malloc(sizeof(AppPrivateType));
  app_priv->rtmpsrc_event_sem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->bEOS = OMX_FALSE;

  tsem_init(app_priv->rtmpsrc_event_sem, 0);

  rtc::AutoThread auto_thread;
  rtc::Thread *thread = rtc::Thread::Current();
  CustomSocketServer socket_server(thread, app_priv);
  thread->set_socketserver(&socket_server);

  // Create a thread to handle the signals.
  SignalProcessThread spt(&set, thread, app_priv);
  spt.Start();

  omx_err = OMX_Init();
  if (omx_err != OMX_ErrorNone) {
    LOGE("The OpenMAX core can not be initialized. Exiting...");
    exit(EXIT_FAILURE);
  }
  LOGI("Omx core is initialized");

  LOGI("------------------------------------");
  test_OMX_ComponentNameEnum();

  LOGI("Using rtmpsrc");
  omx_err = OMX_GetHandle(&app_priv->rtmpsrchandle, (OMX_STRING) "OMX.st.rtmpsrc", app_priv, &rtmpsrccallbacks);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpsrc component not found");
    exit(1);
  }
  LOGI("Rtmpsrc component found");

  omx_err = OMX_GetExtensionIndex(app_priv->rtmpsrchandle, (OMX_STRING) "OMX.ST.index.param.inputurl",
                                  &index_parm_url);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Error in get extension index");
    exit(1);
  }

  char url[1024];
  LOGI("Url param index: %x", index_parm_url);
  omx_err = OMX_SetParameter(app_priv->rtmpsrchandle, index_parm_url, (OMX_PTR) "rtmp://127.0.0.1/live/va");
  if (omx_err != OMX_ErrorNone) {
    LOGE("Error in input format");
    exit(1);
  }
  OMX_GetParameter(app_priv->rtmpsrchandle, index_parm_url, url);
  LOGI("Test url set to: %s\"", url);

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpsrc set to idle failed");
    exit(1);
  }
  omx_err = OMX_AllocateBuffer(app_priv->rtmpsrchandle, &app_priv->outBufferRtmpsrcVideo[0], 0, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpsrchandle, &app_priv->outBufferRtmpsrcVideo[1], 0, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpsrchandle, &app_priv->outBufferRtmpsrcAudio[0], 1, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpsrchandle, &app_priv->outBufferRtmpsrcAudio[1], 1, app_priv, BUFFER_OUT_SIZE);
  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in idle state");

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpsrc set to executing failed");
    exit(1);
  }
  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in executing state");

  omx_err = OMX_FillThisBuffer(app_priv->rtmpsrchandle, app_priv->outBufferRtmpsrcVideo[0]);
  omx_err = OMX_FillThisBuffer(app_priv->rtmpsrchandle, app_priv->outBufferRtmpsrcVideo[1]);
  omx_err = OMX_FillThisBuffer(app_priv->rtmpsrchandle, app_priv->outBufferRtmpsrcAudio[0]);
  omx_err = OMX_FillThisBuffer(app_priv->rtmpsrchandle, app_priv->outBufferRtmpsrcAudio[1]);

  LOGI("Rtmpsrc test running ..");
  thread->Run();

  thread->set_socketserver(NULL);

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpsrc set to idle failed");
    exit(1);
  }
  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in idle state");

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateLoaded, NULL);
  omx_err = OMX_FreeBuffer(app_priv->rtmpsrchandle, 0, app_priv->outBufferRtmpsrcVideo[0]);
  omx_err = OMX_FreeBuffer(app_priv->rtmpsrchandle, 0, app_priv->outBufferRtmpsrcVideo[1]);
  omx_err = OMX_FreeBuffer(app_priv->rtmpsrchandle, 1, app_priv->outBufferRtmpsrcAudio[0]);
  omx_err = OMX_FreeBuffer(app_priv->rtmpsrchandle, 1, app_priv->outBufferRtmpsrcAudio[1]);
  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in loaded state");

  OMX_FreeHandle(app_priv->rtmpsrchandle);

  OMX_Deinit();

  free(app_priv->rtmpsrc_event_sem);
  app_priv->rtmpsrc_event_sem = NULL;

  free(app_priv);
  app_priv = NULL;

  spt.Stop();
  xlog::log_close();
  return 0;
}

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void)
{
  char *name;
  OMX_U32 index;
  OMX_ERRORTYPE omx_err = OMX_ErrorNone;

  LOGI("GENERAL TEST");
  name = (char *) malloc(OMX_MAX_STRINGNAME_SIZE);
  index = 0;
  for ( ; ; ) {
    omx_err = OMX_ComponentNameEnum(name, OMX_MAX_STRINGNAME_SIZE, index);
    if ((name != NULL) && (omx_err == OMX_ErrorNone)) {
      LOGI("component %i is %s", index, name);
    } else break;
    ++index;
  }
  free(name);
  LOGI("GENERAL TEST result: %s", omx_err == OMX_ErrorNoMore ? "PASS" : "FAILURE");
  return omx_err;
}

OMX_ERRORTYPE rtmpsrcEventHandler(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_EVENTTYPE eEvent,
    OMX_OUT OMX_U32 Data1,
    OMX_OUT OMX_U32 Data2,
    OMX_OUT OMX_PTR pEventData)
{
  AppPrivateType *app_priv = (AppPrivateType *) pAppData;

  if (eEvent == OMX_EventCmdComplete) {
    LOGI("Rtmpsrc received command: %s", STR(omx_common::str_omx_command((OMX_COMMANDTYPE) Data1)));
    if (Data1 == OMX_CommandStateSet) {
      LOGI("Rtmpsrc state changed in: %s", STR(omx_common::str_omx_state((OMX_STATETYPE) Data2)));
      tsem_up(app_priv->rtmpsrc_event_sem);
    }
  } else if (eEvent == OMX_EventError) {
    LOGE("Received error event, data1=%x, data2=%d", Data1, Data2);
    kill(getpid(), SIGINT);
  } else {
    LOGE("eEvent=%x, data1=%u, data2=%u not handled", eEvent, Data1, Data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpsrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_PTR pAppData,
    OMX_OUT OMX_BUFFERHEADERTYPE* pBuffer)
{
  AppPrivateType *app_priv = (AppPrivateType *) pAppData;
  OMX_ERRORTYPE omx_err;

  if (pBuffer != NULL) {
    if (!app_priv->bEOS) {
      if (pBuffer->nFlags == OMX_BUFFERFLAG_EOS) {
        app_priv->bEOS = OMX_TRUE;
      } else {
        if (pBuffer->nFilledLen == 0) {
          LOGE("Ouch! No data in the output buffer");
          return OMX_ErrorNone;
        }

        pBuffer->nFilledLen = 0;
        pBuffer->nFlags = 0;
        omx_err = OMX_FillThisBuffer(hComponent, pBuffer);
        if (omx_err != OMX_ErrorNone) {
          LOGE("OMX_FillThisBuffer failed");
          return omx_err;
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
