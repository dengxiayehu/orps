#ifndef _OMX_UTIL_H_
#define _OMX_UTIL_H_

#include <string>
#include <OMX_Core.h>

namespace omx_common {
  
std::string str_omx_state(OMX_STATETYPE omx_state);
std::string str_omx_command(OMX_COMMANDTYPE omx_command);

}

#endif /* end of _OMX_UTIL_H_ */
