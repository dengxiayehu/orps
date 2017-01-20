#include <xlog.h>
#include <xmacro.h>
#include <webrtc/base/thread.h>
#include <webrtc/base/physicalsocketserver.h>
#include <signal.h>
#include <pthread.h>

#include "omxrtmpouttest.h"

class CustomSocketServer : public rtc::PhysicalSocketServer {
public:
  CustomSocketServer(rtc::Thread *thread, appPrivateType *app_priv)
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
  appPrivateType *app_priv_;
};

class SignalProcessThread : public rtc::Thread {
public:
  SignalProcessThread(sigset_t *set, Thread *main_thread, appPrivateType *app_priv)
    : set_(set), main_thread_(main_thread), app_priv_(app_priv) { }
  virtual ~SignalProcessThread() { }
  virtual void Run();

private:
  sigset_t *set_;
  Thread *main_thread_;
  appPrivateType *app_priv_;
};

class FunctorQuit {
public:
  explicit FunctorQuit(appPrivateType *app_priv)
    : app_priv_(app_priv) { }
  void operator()() {
    app_priv_->bEOS = OMX_TRUE;
  }

private:
  appPrivateType *app_priv_;
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

static OMX_CALLBACKTYPE rtmpoutcallbacks = {
  .EventHandler     = rtmpoutEventHandler,
  .EmptyBufferDone  = rtmpoutEmptyBufferDone,
  .FillBufferDone   = NULL
};

static OMX_CALLBACKTYPE clocksrccallbacks = {
  .EventHandler     = clocksrcEventHandler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = clocksrcFillBufferDone,
};

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void);

int main(int argc, const char *argv[])
{
  appPrivateType *app_priv;
  OMX_ERRORTYPE omx_err;
  OMX_INDEXTYPE index_param_url;

  xlog::log_add_dst("./omxrtmpouttest.log");

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

  app_priv = (appPrivateType *) malloc(sizeof(appPrivateType));
  app_priv->rtmpoutEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->clocksrcEventSem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->bEOS = OMX_FALSE;

  tsem_init(app_priv->rtmpoutEventSem, 0);
  tsem_init(app_priv->clocksrcEventSem, 0);

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

  omx_err = OMX_GetHandle(&app_priv->rtmpouthandle, (OMX_STRING) "OMX.st.rtmpout", app_priv, &rtmpoutcallbacks);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout component not found");
    exit(1);
  }
  LOGI("Rtmpout component found");

  omx_err = OMX_GetHandle(&app_priv->clocksrchandle, (OMX_STRING) "OMX.st.clocksrc", app_priv, &clocksrccallbacks);
  if (omx_err != OMX_ErrorNone) {
   LOGE("Clocksrc component not found");
   exit(1);
  }
  LOGI("Clocksrc component found");

  omx_err = OMX_GetExtensionIndex(app_priv->rtmpouthandle, (OMX_STRING) "OMX.ST.index.param.outputurl",
                                  &index_param_url);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Error in get extension index");
    exit(1);
  }

  char url[2048];
  LOGI("Url param index: %x", index_param_url);
  omx_err = OMX_SetParameter(app_priv->rtmpouthandle, index_param_url, (OMX_PTR) "rtmp://127.0.0.1/live/xyz");
  if (omx_err != OMX_ErrorNone) {
    LOGE("Error in output format");
    exit(1);
  }
  OMX_GetParameter(app_priv->rtmpouthandle, index_param_url, url);
  LOGI("Test output url set to: %s\"", url);

  LOGI("Rtmpout test running ..");
  thread->Run();

  thread->set_socketserver(NULL);

  OMX_FreeHandle(app_priv->rtmpouthandle);

  OMX_Deinit();

  SAFE_FREE(app_priv->clocksrcEventSem);
  SAFE_FREE(app_priv->rtmpoutEventSem);

  free(app_priv);
  app_priv = NULL;

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
  LOGI("GENERAL TEST result: %s",
       omx_err == OMX_ErrorNoMore ? "PASS" : "FAILURE");
  return omx_err;
}

OMX_ERRORTYPE rtmpoutEventHandler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data)
{
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpoutEmptyBufferDone(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer)
{
  return OMX_ErrorNone;
}

OMX_ERRORTYPE clocksrcEventHandler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data)
{
  return OMX_ErrorNone;
}

OMX_ERRORTYPE clocksrcFillBufferDone(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer)
{
  return OMX_ErrorNone;
}
