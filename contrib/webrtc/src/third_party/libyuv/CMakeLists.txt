cmake_minimum_required(VERSION 2.6)

SET(TARGET yuv)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libyuv/source/compare.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/compare_common.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/compare_gcc.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_argb.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_from.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_from_argb.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_jpeg.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_to_argb.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/convert_to_i420.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/cpu_id.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/mjpeg_decoder.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/mjpeg_validate.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/planar_functions.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/rotate.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/rotate_argb.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/rotate_mips.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/row_any.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/row_common.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/row_mips.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/row_gcc.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale_argb.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale_any.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale_common.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale_mips.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/scale_gcc.cc
  ${WEBRTC_ROOT}/third_party/libyuv/source/video_common.cc
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
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;HAVE_JPEG;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
