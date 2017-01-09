cmake_minimum_required(VERSION 2.6)

SET(TARGET rtc_xmpp)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/chatroommoduleimpl.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/constants.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/discoitemsquerytask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/hangoutpubsubclient.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/iqtask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/jid.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/moduleimpl.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/mucroomconfigtask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/mucroomdiscoverytask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/mucroomlookuptask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/mucroomuniquehangoutidtask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/pingtask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/presenceouttask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/presencereceivetask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/presencestatus.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/pubsub_task.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/pubsubclient.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/pubsubstateclient.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/pubsubtasks.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/receivetask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/rostermoduleimpl.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/saslmechanism.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppauth.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppclient.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppengineimpl.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppengineimpl_iq.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmpplogintask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmpppump.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppsocket.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppstanzaparser.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmpptask.cc
  ${WEBRTC_ROOT}/webrtc/libjingle/xmpp/xmppthread.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;FEATURE_ENABLE_SSL;FEATURE_ENABLE_VOICEMAIL;FEATURE_ENABLE_PSTN;SSL_USE_NSS;HAVE_NSS_SSL_H;SSL_USE_NSS_RNG;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")
