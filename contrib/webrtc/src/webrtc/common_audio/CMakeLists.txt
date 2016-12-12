cmake_minimum_required(VERSION 2.6)

SET(TARGET common_audio)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/common_audio/audio_converter.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/audio_ring_buffer.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/audio_util.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/blocker.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/channel_buffer.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/fft4g.c
  ${WEBRTC_ROOT}/webrtc/common_audio/fir_filter.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/lapped_transform.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/real_fourier.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/real_fourier_ooura.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/push_resampler.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/push_sinc_resampler.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/resampler.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/sinc_resampler.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/ring_buffer.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/auto_corr_to_refl_coef.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/auto_correlation.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/complex_fft.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/complex_bit_reverse.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/copy_set_operations.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/cross_correlation.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/division_operations.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/dot_product_with_scale.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/downsample_fast.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/energy.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/filter_ar.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/filter_ar_fast_q12.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/filter_ma_fast_q12.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/get_hanning_window.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/get_scaling_square.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/ilbc_specific_functions.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/levinson_durbin.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/lpc_to_refl_coef.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/min_max_operations.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/randomization_functions.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/refl_coef_to_lpc.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/real_fft.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/resample.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/resample_48khz.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/resample_by_2.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/resample_by_2_internal.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/resample_fractional.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/spl_init.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/spl_sqrt.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/spl_sqrt_floor.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/splitting_filter.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/sqrt_of_one_minus_x_squared.c
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/vector_scaling_operations.c
  ${WEBRTC_ROOT}/webrtc/common_audio/sparse_fir_filter.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/vad.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/webrtc_vad.c
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/vad_core.c
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/vad_filterbank.c
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/vad_gmm.c
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/vad_sp.c
  ${WEBRTC_ROOT}/webrtc/common_audio/wav_header.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/wav_file.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/window_generator.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/real_fourier_openmax.cc
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
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/third_party/openmax_dl
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;RTC_USE_OPENMAX_DL;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET common_audio_sse2)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
SET(WEBRTC_ROOT "$ENV{WEBRTC_ROOT}")
IF("${WEBRTC_ROOT}" STREQUAL "")
  MESSAGE(FATAL_ERROR "Env \"WEBRTC_ROOT\" not set.")
ENDIF()

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -msse2 -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/common_audio/fir_filter_sse.cc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/sinc_resampler_sse.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
