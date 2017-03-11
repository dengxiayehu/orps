#include "omx_util.h"

namespace omx_common {

std::string str_omx_state(OMX_STATETYPE omx_state)
{
  switch (omx_state) {
  case OMX_StateInvalid:            return "OMX_StateInvalid";            break;
  case OMX_StateLoaded:             return "OMX_StateLoaded";             break;
  case OMX_StateIdle:               return "OMX_StateIdle";               break;
  case OMX_StateExecuting:          return "OMX_StateExecuting";          break;
  case OMX_StatePause:              return "OMX_StatePause";              break;
  case OMX_StateWaitForResources:   return "OMX_StateWaitForResources";   break;
  case OMX_StateKhronosExtensions:  return "OMX_StateKhronosExtensions";  break;
  case OMX_StateVendorStartUnused:  return "OMX_StateVendorStartUnused";  break;
  case OMX_StateMax:
  default:                          return "OMX_StateMax";                break;
  }
}

std::string str_omx_command(OMX_COMMANDTYPE omx_command)
{
  switch (omx_command) {
  case OMX_CommandStateSet:           return "OMX_CommandStateSet";           break;
  case OMX_CommandFlush:              return "OMX_CommandFlush";              break;
  case OMX_CommandPortDisable:        return "OMX_CommandPortDisable";        break;
  case OMX_CommandPortEnable:         return "OMX_CommandPortEnable";         break;
  case OMX_CommandMarkBuffer:         return "OMX_CommandMarkBuffer";         break;
  case OMX_CommandKhronosExtensions:  return "OMX_CommandKhronosExtensions";  break;
  case OMX_CommandVendorStartUnused:  return "OMX_CommandVendorStartUnused";  break;
  case OMX_CommandMax:
  default:                            return "OMX_CommandMax";                break;
  }
}

}
