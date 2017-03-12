#include <xlog.h>
#include <xmacro.h>
#include <omx_util.h>
#include <webrtc/base/thread.h>
#include <webrtc/base/physicalsocketserver.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
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

static OMX_ERRORTYPE test_OMX_ComponentNameEnum(void);

static void setHeader(OMX_PTR header, OMX_U32 size)
{
  OMX_VERSIONTYPE* ver = (OMX_VERSIONTYPE*) ((OMX_U8 *) header + sizeof(OMX_U32));
  *((OMX_U32*) header) = size;

  ver->s.nVersionMajor = VERSIONMAJOR;
  ver->s.nVersionMinor = VERSIONMINOR;
  ver->s.nRevision = VERSIONREVISION;
  ver->s.nStep = VERSIONSTEP;
}

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
  app_priv->rtmpout_event_sem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->bEOS = OMX_FALSE;

  tsem_init(app_priv->rtmpout_event_sem, 0);

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

  OMX_PORT_PARAM_TYPE port_param;
  setHeader(&port_param, sizeof(OMX_PORT_PARAM_TYPE));
  omx_err = OMX_GetParameter(app_priv->rtmpouthandle, OMX_IndexParamVideoInit, &port_param);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout get parameter video init failed");
    exit(1);
  }
  LOGI("video port param, start=%d nports=%d", port_param.nStartPortNumber, port_param.nPorts);

  omx_err = OMX_GetParameter(app_priv->rtmpouthandle, OMX_IndexParamAudioInit, &port_param);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout get parameter audio init failed");
    exit(1);
  }
  LOGI("audio port param, start=%d nports=%d", port_param.nStartPortNumber, port_param.nPorts);

  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout set to idle failed");
    exit(1);
  }
  omx_err = OMX_AllocateBuffer(app_priv->rtmpouthandle, &app_priv->inbuffer_video[0], 0, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpouthandle, &app_priv->inbuffer_video[1], 0, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpouthandle, &app_priv->inbuffer_audio[0], 1, app_priv, BUFFER_OUT_SIZE);
  omx_err = OMX_AllocateBuffer(app_priv->rtmpouthandle, &app_priv->inbuffer_audio[1], 1, app_priv, BUFFER_OUT_SIZE);
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in idle state");

  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout set to executing failed");
    exit(1);
  }
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in executing state");

  omx_err = OMX_EmptyThisBuffer(app_priv->rtmpouthandle, app_priv->inbuffer_video[0]);
  omx_err = OMX_EmptyThisBuffer(app_priv->rtmpouthandle, app_priv->inbuffer_video[1]);
  omx_err = OMX_EmptyThisBuffer(app_priv->rtmpouthandle, app_priv->inbuffer_audio[0]);
  omx_err = OMX_EmptyThisBuffer(app_priv->rtmpouthandle, app_priv->inbuffer_audio[1]);

  LOGI("Rtmpout test running ..");
  thread->Run();

  thread->set_socketserver(NULL);

  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout set to idle failed");
    exit(1);
  }
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in executing state");

  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateLoaded, NULL);
  if (omx_err != OMX_ErrorNone) {
    LOGE("Rtmpout set to loaded failed");
    exit(1);
  }
  OMX_FreeBuffer(app_priv->rtmpouthandle, 0, app_priv->inbuffer_video[0]);
  OMX_FreeBuffer(app_priv->rtmpouthandle, 0, app_priv->inbuffer_video[1]);
  OMX_FreeBuffer(app_priv->rtmpouthandle, 1, app_priv->inbuffer_audio[0]);
  OMX_FreeBuffer(app_priv->rtmpouthandle, 1, app_priv->inbuffer_audio[1]);
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout set to loaded state");

  OMX_FreeHandle(app_priv->rtmpouthandle);

  OMX_Deinit();

  SAFE_FREE(app_priv->rtmpout_event_sem);

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

OMX_ERRORTYPE rtmpoutEventHandler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data)
{
  appPrivateType *app_priv = (appPrivateType *) app_data;

  if (event == OMX_EventCmdComplete) {
    LOGI("Rtmpout received command: %s", STR(omx_common::str_omx_command((OMX_COMMANDTYPE) data1)));
    if (data1 == OMX_CommandStateSet) {
      LOGI("Rtmpout state changed in: %s", STR(omx_common::str_omx_state((OMX_STATETYPE) data2)));
      tsem_up(app_priv->rtmpout_event_sem);
    }
  } else if (event == OMX_EventError) {
    LOGE("Received error event, data1=%x, data2=%d", data1, data2);
    kill(getpid(), SIGINT);
  } else {
    LOGE("event=%x, data1=%u, data2=%u not handled", event, data1, data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpoutEmptyBufferDone(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer)
{
  appPrivateType *app_priv = (appPrivateType *) app_data;
  OMX_ERRORTYPE omx_err;

  if (buffer != NULL) {
    if (!app_priv->bEOS) {
      char str[] = "Hello, world!";
      buffer->nFilledLen = strlen(str) + 1;
      memcpy(buffer->pBuffer, str, buffer->nFilledLen);
      omx_err = OMX_EmptyThisBuffer(app_priv->rtmpouthandle, buffer);
      if (omx_err != OMX_ErrorNone) {
        LOGE("OMX_EmptyThisBuffer failed");
        return omx_err;
      }
    } else {
      LOGI("eos=%x dropping this buffer", buffer->nFlags);
    }
  } else {
    LOGE("NULL buffer to input");
  }
  return omx_err;
}
