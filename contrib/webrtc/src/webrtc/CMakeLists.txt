cmake_minimum_required(VERSION 2.6)

SET(TARGET webrtc_common)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  common_types.cc
  config.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET webrtc)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/video/audio_receive_stream.cc
  ${WEBRTC_ROOT}/webrtc/video/call.cc
  ${WEBRTC_ROOT}/webrtc/video/encoded_frame_callback_adapter.cc
  ${WEBRTC_ROOT}/webrtc/video/receive_statistics_proxy.cc
  ${WEBRTC_ROOT}/webrtc/video/send_statistics_proxy.cc
  ${WEBRTC_ROOT}/webrtc/video/transport_adapter.cc
  ${WEBRTC_ROOT}/webrtc/video/video_capture_input.cc
  ${WEBRTC_ROOT}/webrtc/video/video_decoder.cc
  ${WEBRTC_ROOT}/webrtc/video/video_encoder.cc
  ${WEBRTC_ROOT}/webrtc/video/video_receive_stream.cc
  ${WEBRTC_ROOT}/webrtc/video/video_send_stream.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/call_stats.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/encoder_state_feedback.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/overuse_frame_detector.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/payload_router.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/report_block_stats.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/stream_synchronization.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_channel.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_channel_group.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_encoder.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_receiver.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_remb.cc
  ${WEBRTC_ROOT}/webrtc/video_engine/vie_sync_module.cc
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
  ${WEBRTC_ROOT}/webrtc/common_video/interface
  ${WEBRTC_ROOT}/webrtc/common_video/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

ADD_SUBDIRECTORY(voice_engine)
ADD_SUBDIRECTORY(libjingle)
ADD_SUBDIRECTORY(base)
ADD_SUBDIRECTORY(p2p)
ADD_SUBDIRECTORY(modules)
ADD_SUBDIRECTORY(system_wrappers)
ADD_SUBDIRECTORY(sound)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(tools)
ADD_SUBDIRECTORY(common_video)
ADD_SUBDIRECTORY(common_audio)
