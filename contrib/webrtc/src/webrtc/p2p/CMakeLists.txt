cmake_minimum_required(VERSION 2.6)

SET(TARGET rtc_p2p)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/p2p/base/asyncstuntcpsocket.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/basicpacketsocketfactory.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/constants.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/dtlstransportchannel.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/p2ptransport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/p2ptransportchannel.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/port.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/portallocator.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/pseudotcp.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/rawtransport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/rawtransportchannel.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/relayport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/relayserver.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/session.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/sessiondescription.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/stun.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/stunport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/stunrequest.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/stunserver.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/tcpport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/transport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/transportchannel.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/transportchannelproxy.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/transportdescription.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/transportdescriptionfactory.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/turnport.cc
  ${WEBRTC_ROOT}/webrtc/p2p/base/turnserver.cc
  ${WEBRTC_ROOT}/webrtc/p2p/client/basicportallocator.cc
  ${WEBRTC_ROOT}/webrtc/p2p/client/connectivitychecker.cc
  ${WEBRTC_ROOT}/webrtc/p2p/client/httpportallocator.cc
  ${WEBRTC_ROOT}/webrtc/p2p/client/socketmonitor.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;FEATURE_ENABLE_VOICEMAIL;FEATURE_ENABLE_PSTN;FEATURE_ENABLE_SSL;SSL_USE_NSS;HAVE_NSS_SSL_H;SSL_USE_NSS_RNG;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET stunprober)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/p2p/stunprober/stunprober.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;FEATURE_ENABLE_SSL;SSL_USE_NSS;HAVE_NSS_SSL_H;SSL_USE_NSS_RNG;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET stun_prober)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/p2p/stunprober/main.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})
ADD_DEPENDENCIES(${TARGET} stunprober rtc_p2p rtc_base webrtc_common rtc_base_approved jsoncpp crssl)
TARGET_LINK_LIBRARIES(${TARGET}
  ${OUT}/libstunprober.a
  ${OUT}/librtc_p2p.a
  ${OUT}/librtc_base.a
  ${OUT}/libwebrtc_common.a
  ${OUT}/librtc_base_approved.a
  ${OUT}/libjsoncpp.a
  ${OUT}/libcrssl.a
  )

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;FEATURE_ENABLE_VOICEMAIL;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all -ldl -lrt -lnss3 -lnssutil3 -lsmime3 -lplds4 -lplc4 -lnspr4")
