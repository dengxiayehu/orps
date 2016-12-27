#include <st_static_component_loader.h>
#include <omx_rtmpsrc_component.h>

extern "C"
int omx_component_library_Setup(stLoaderComponentType **stComponents)
{
  DEBUG(DEB_LEV_FUNCTION_NAME, "In %s\n", __func__);

  if (stComponents == NULL) {
    DEBUG(DEB_LEV_FUNCTION_NAME, "Out of %s\n", __func__);
    return 1; // Return number of component/s
  }

  stComponents[0]->componentVersion.s.nVersionMajor = 1;
  stComponents[0]->componentVersion.s.nVersionMinor = 1;
  stComponents[0]->componentVersion.s.nRevision = 1;
  stComponents[0]->componentVersion.s.nStep = 1;

  stComponents[0]->name = (char *) calloc(OMX_MAX_STRINGNAME_SIZE, 1);
  if (stComponents == NULL) {
    return OMX_ErrorInsufficientResources;
  }

  strcpy(stComponents[0]->name, RTMPSRC_COMP_NAME);
  stComponents[0]->name_specific_length = 1;
  stComponents[0]->constructor = omx_rtmpsrc_component_Constructor;
  
  stComponents[0]->name_specific = (char **) calloc(stComponents[0]->name_specific_length,sizeof(char *));
  stComponents[0]->role_specific = (char **) calloc(stComponents[0]->name_specific_length,sizeof(char *));

  for (int i = 0; i < stComponents[0]->name_specific_length; ++i) {
    stComponents[0]->name_specific[i] = (char *) calloc(OMX_MAX_STRINGNAME_SIZE, 1);
    if (stComponents[0]->name_specific == NULL) {
      return OMX_ErrorInsufficientResources;
    }
  }
  for (int i = 0; i < stComponents[0]->name_specific_length; ++i) {
    stComponents[0]->role_specific[i] = (char *) calloc(OMX_MAX_STRINGNAME_SIZE, 1);
    if (stComponents[0]->role_specific == NULL) {
      return OMX_ErrorInsufficientResources;
    }
  }

  strcpy(stComponents[0]->name_specific[0], RTMPSRC_COMP_NAME);
  strcpy(stComponents[0]->role_specific[0], RTMPSRC_COMP_ROLE);

  DEBUG(DEB_LEV_FUNCTION_NAME, "Out of %s\n", __func__);
  return 1;
}
