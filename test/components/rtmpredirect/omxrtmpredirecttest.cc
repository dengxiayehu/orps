#include <xlog.h>
#include <xmacro.h>
#include <webrtc/base/thread.h>
#include <webrtc/base/physicalsocketserver.h>
#include <signal.h>
#include <pthread.h>
#include <user_debug_levels.h>

#include "omxrtmpredirecttest.h"

static OMX_CALLBACKTYPE rtmpsrccallbacks = {
  .EventHandler     = rtmpsrc_event_handler,
  .EmptyBufferDone  = NULL,
  .FillBufferDone   = rtmpsrc_fillbuffer_done
};
static OMX_CALLBACKTYPE rtmpoutcallbacks = {
  .EventHandler     = rtmpout_event_handler,
  .EmptyBufferDone  = rtmpout_emptybuffer_done,
  .FillBufferDone   = NULL
};

static void set_header(OMX_PTR header, OMX_U32 size);

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

int main(int argc, const char *argv[])
{
  AppPrivateType *app_priv;
  OMX_ERRORTYPE omx_err;

  xlog::log_add_dst("./omxrtmpredirecttest.log");

  sigset_t set;
  sigemptyset(&set);
  sigaddset(&set, SIGINT);
  pthread_sigmask(SIG_BLOCK, &set, NULL);

  app_priv = (AppPrivateType *) calloc(1, sizeof(AppPrivateType));
  app_priv->rtmpsrc_event_sem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->rtmpout_event_sem = (tsem_t *) malloc(sizeof(tsem_t));
  app_priv->bEOS = OMX_FALSE;

  tsem_init(app_priv->rtmpsrc_event_sem, 0);
  tsem_init(app_priv->rtmpout_event_sem, 0);

  rtc::AutoThread auto_thread;
  rtc::Thread *thread = rtc::Thread::Current();
  CustomSocketServer socket_server(thread, app_priv);
  thread->set_socketserver(&socket_server);

  SignalProcessThread spt(&set, thread, app_priv);
  spt.Start();

  omx_err = OMX_Init();

  // Get component handles
  omx_err = OMX_GetHandle(&app_priv->rtmpsrchandle, (OMX_STRING) "OMX.st.rtmpsrc", app_priv, &rtmpsrccallbacks);
  omx_err = OMX_GetHandle(&app_priv->rtmpouthandle, (OMX_STRING) "OMX.st.rtmpout", app_priv, &rtmpoutcallbacks);

  // Setup input/output rtmp urls
  OMX_INDEXTYPE omx_index;
  char url[1024];
  omx_err = OMX_GetExtensionIndex(app_priv->rtmpsrchandle, (OMX_STRING) "OMX.ST.index.param.inputurl",
                                  &omx_index);
  omx_err = OMX_SetParameter(app_priv->rtmpsrchandle, omx_index, (OMX_PTR) "rtmp://127.0.0.1/live/va");
  OMX_GetParameter(app_priv->rtmpsrchandle, omx_index, url);
  LOGI("Test rtmpsrc url set to: %s\"", url);

  omx_err = OMX_GetExtensionIndex(app_priv->rtmpouthandle, (OMX_STRING) "OMX.ST.index.param.outputurl",
                                  &omx_index);
  omx_err = OMX_SetParameter(app_priv->rtmpouthandle, omx_index, (OMX_PTR) "rtmp://127.0.0.1/live/xyz");
  OMX_GetParameter(app_priv->rtmpouthandle, omx_index, url);
  LOGI("Test rtmpout url set to: %s\"", url);

  // Setup the tunnels
  omx_err = OMX_SetupTunnel(app_priv->rtmpsrchandle, 0, app_priv->rtmpouthandle, 0);
  omx_err = OMX_SetupTunnel(app_priv->rtmpsrchandle, 1, app_priv->rtmpouthandle, 1);

  OMX_PARAM_BUFFERSUPPLIERTYPE buffer_supplier;
  buffer_supplier.nPortIndex = 0;
  buffer_supplier.eBufferSupplier = OMX_BufferSupplyInput;
  set_header(&buffer_supplier, sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
  omx_err = OMX_SetParameter(app_priv->rtmpouthandle, OMX_IndexParamCompBufferSupplier, &buffer_supplier);

  buffer_supplier.nPortIndex = 1;
  buffer_supplier.eBufferSupplier = OMX_BufferSupplyInput;
  set_header(&buffer_supplier, sizeof(OMX_PARAM_BUFFERSUPPLIERTYPE));
  omx_err = OMX_SetParameter(app_priv->rtmpouthandle, OMX_IndexParamCompBufferSupplier, &buffer_supplier);

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in idle state");
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in idle state");

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateExecuting, NULL);

  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in executing state");
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in executing state");

  LOGI("Pipeline running ..");
  thread->Run();

  thread->set_socketserver(NULL);

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateIdle, NULL);

  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in idle state");
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in idle state");

  omx_err = OMX_SendCommand(app_priv->rtmpsrchandle, OMX_CommandStateSet, OMX_StateLoaded, NULL);
  omx_err = OMX_SendCommand(app_priv->rtmpouthandle, OMX_CommandStateSet, OMX_StateLoaded, NULL);

  tsem_down(app_priv->rtmpsrc_event_sem);
  LOGI("Rtmpsrc in loaded state");
  tsem_down(app_priv->rtmpout_event_sem);
  LOGI("Rtmpout in loaded state");

  OMX_FreeHandle(app_priv->rtmpsrchandle);
  OMX_FreeHandle(app_priv->rtmpouthandle);

  OMX_Deinit();

  tsem_reset(app_priv->rtmpsrc_event_sem);
  tsem_reset(app_priv->rtmpout_event_sem);
  SAFE_FREE(app_priv->rtmpsrc_event_sem);
  SAFE_FREE(app_priv->rtmpout_event_sem);

  free(app_priv);
  app_priv = NULL;
  UNUSED(omx_err);

  xlog::log_close();
  return 0;
}

OMX_ERRORTYPE rtmpsrc_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data)
{
  AppPrivateType *app_priv = (AppPrivateType *) app_data;

  if (event == OMX_EventCmdComplete) {
    if (data1 == OMX_CommandStateSet) {
      switch ((int) data2) {
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
      tsem_up(app_priv->rtmpsrc_event_sem);
    } else if (data1 == OMX_CommandPortEnable) {
      LOGI("Rtmpsrc received port enable event");
      tsem_up(app_priv->rtmpsrc_event_sem);
    } else if (data1 == OMX_CommandPortDisable) {
      LOGI("Rtmpsrc received port disable event");
      tsem_up(app_priv->rtmpsrc_event_sem);
    } else if (data1 == OMX_CommandFlush) {
      LOGI("Rtmpsrc received flush event");
      tsem_up(app_priv->rtmpsrc_event_sem);
    } else {
      LOGI("Rtmpsrc received event event=%d data1=%u data2=%u", event, data1, data2);
    }
  } else if (event == OMX_EventPortSettingsChanged) {
  } else if (event == OMX_EventPortFormatDetected) {
    LOGI("Rtmpsrc port format detected %x", (int) data1);
  } else if (event == OMX_EventError) {
    LOGE("Rtmpsrc received error event, data1=%x, data2=%d", data1, data2);
  } else {
    LOGI("Rtmpsrc event=%x, data1=%u, data2=%u", event, data1, data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpsrc_fillbuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer)
{
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpout_event_handler(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_EVENTTYPE event,
    OMX_OUT OMX_U32 data1,
    OMX_OUT OMX_U32 data2,
    OMX_OUT OMX_PTR event_data)
{
  AppPrivateType *app_priv = (AppPrivateType *) app_data;

  if (event == OMX_EventCmdComplete) {
    if (data1 == OMX_CommandStateSet) {
      switch ((int) data2) {
      case OMX_StateInvalid:
        LOGI("Rtmpout state changed in OMX_StateInvalid");
        break;
      case OMX_StateLoaded:
        LOGI("Rtmpout state changed in OMX_StateLoaded");
        break;
      case OMX_StateIdle:
        LOGI("Rtmpout state changed in OMX_StateIdle");
        break;
      case OMX_StateExecuting:
        LOGI("Rtmpout state changed in OMX_StateExecuting");
        break;
      case OMX_StatePause:
        LOGI("Rtmpout state changed in OMX_StatePause");
        break;
      case OMX_StateWaitForResources:
        LOGI("Rtmpout state changed in OMX_StateWaitForResources");
        break;
      }
      tsem_up(app_priv->rtmpout_event_sem);
    } else if (data1 == OMX_CommandPortEnable) {
      LOGI("Rtmpout received port enable event");
      tsem_up(app_priv->rtmpout_event_sem);
    } else if (data1 == OMX_CommandPortDisable) {
      LOGI("Rtmpout received port disable event");
      tsem_up(app_priv->rtmpout_event_sem);
    } else if (data1 == OMX_CommandFlush) {
      LOGI("Rtmpout received flush event");
      tsem_up(app_priv->rtmpout_event_sem);
    } else {
      LOGI("Rtmpout received event event=%d data1=%u data2=%u", event, data1, data2);
    }
  } else if (event == OMX_EventPortSettingsChanged) {
  } else if (event == OMX_EventPortFormatDetected) {
    LOGI("Rtmpout port format detected %x", (int) data1);
  } else if (event == OMX_EventError) {
    LOGE("Rtmpout received error event, data1=%x, data2=%d", data1, data2);
  } else {
    LOGI("Rtmpout event=%x, data1=%u, data2=%u", event, data1, data2);
  }
  return OMX_ErrorNone;
}

OMX_ERRORTYPE rtmpout_emptybuffer_done(
    OMX_OUT OMX_HANDLETYPE hcomp,
    OMX_OUT OMX_PTR app_data,
    OMX_OUT OMX_BUFFERHEADERTYPE *buffer)
{
  return OMX_ErrorNone;
}

static void set_header(OMX_PTR header, OMX_U32 size)
{
  OMX_VERSIONTYPE* ver = (OMX_VERSIONTYPE*) ((OMX_U8 *) header + sizeof(OMX_U32));
  *((OMX_U32*) header) = size;

  ver->s.nVersionMajor = VERSIONMAJOR;
  ver->s.nVersionMinor = VERSIONMINOR;
  ver->s.nRevision = VERSIONREVISION;
  ver->s.nStep = VERSIONSTEP;
}
