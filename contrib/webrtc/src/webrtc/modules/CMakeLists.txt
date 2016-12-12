cmake_minimum_required(VERSION 2.6)

SET(TARGET video_render)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_render/video_render_impl.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET webrtc_utility)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/utility/source/audio_frame_operations.cc
  ${WEBRTC_ROOT}/webrtc/modules/utility/source/coder.cc
  ${WEBRTC_ROOT}/webrtc/modules/utility/source/file_player_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/utility/source/file_recorder_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/utility/source/process_thread_impl.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/interface
  ${WEBRTC_ROOT}/webrtc/modules/interface
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_coding_module)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/acm_codec_database.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/acm_receiver.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/acm_resampler.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/audio_coding_module.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/audio_coding_module_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/call_statistics.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/codec_manager.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/codec_owner.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/initial_delay_manager.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/acm2/nack.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/main/interface
  ${WEBRTC_ROOT}/webrtc/modules/interface
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/pcm16b/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/red/include
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  ${WEBRTC_ROOT}/third_party/opus/src/src
  ${WEBRTC_ROOT}/third_party/opus/src/celt
  ${WEBRTC_ROOT}/third_party/opus/src/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;WEBRTC_CODEC_OPUS;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET cng)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -B/home/jwf/workspace/webrtc/webrtc-9540-d92f267-windows/src/third_party/binutils/Linux_x64/Release/bin -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/audio_encoder_cng.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/webrtc_cng.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/cng_helpfuns.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/include
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_encoder_interface)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -B/home/jwf/workspace/webrtc/webrtc-9540-d92f267-windows/src/third_party/binutils/Linux_x64/Release/bin -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/audio_encoder.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET g711)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/g711_interface.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/g711.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/audio_encoder_pcm.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/include
  ${WEBRTC_ROOT}/webrtc
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET g722)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/audio_encoder_g722.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/g722_interface.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/g722_encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/g722_decode.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/include
  ${WEBRTC_ROOT}/webrtc
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET ilbc)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/abs_quant.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/abs_quant_loop.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/audio_encoder_ilbc.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/augmented_cb_corr.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/bw_expand.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_construct.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_mem_energy.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_mem_energy_augmentation.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_mem_energy_calc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_search.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_search_core.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/cb_update_best_index.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/chebyshev.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/comp_corr.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/constants.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/create_augmented_vec.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/decode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/decode_residual.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/decoder_interpolate_lsf.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/do_plc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/energy_inverse.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/enh_upsample.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/enhancer.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/enhancer_interface.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/filtered_cb_vecs.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/frame_classify.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/gain_dequant.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/gain_quant.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/get_cd_vec.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/get_lsp_poly.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/get_sync_seq.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/hp_input.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/hp_output.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/ilbc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/index_conv_dec.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/index_conv_enc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/init_decode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/init_encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/interpolate.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/interpolate_samples.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lpc_encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsf_check.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsf_interpolate_to_poly_dec.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsf_interpolate_to_poly_enc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsf_to_lsp.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsf_to_poly.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/lsp_to_lsf.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/my_corr.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/nearest_neighbor.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/pack_bits.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/poly_to_lsf.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/poly_to_lsp.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/refiner.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/simple_interpolate_lsf.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/simple_lpc_analysis.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/simple_lsf_dequant.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/simple_lsf_quant.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/smooth.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/smooth_out_data.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/sort_sq.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/split_vq.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/state_construct.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/state_search.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/swap_bytes.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/unpack_bits.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/vq3.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/vq4.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/window32_w32.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/xcorr_coef.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/interface
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET isac)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/arith_routines.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/arith_routines_hist.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/arith_routines_logist.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/audio_encoder_isac.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/bandwidth_estimator.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/crc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/decode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/decode_bwe.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/encode_lpc_swb.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/entropy_coding.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/fft.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/filter_functions.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/filterbank_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/intialize.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/isac.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/filterbanks.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/pitch_lag_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lattice.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lpc_gain_swb_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lpc_analysis.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lpc_shape_swb12_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lpc_shape_swb16_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/lpc_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/pitch_estimator.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/pitch_filter.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/pitch_gain_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/spectrum_ar_model_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/source/transform.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/interface
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_decoder_interface)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/audio_decoder.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET isac_fix)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/arith_routines.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/arith_routines_hist.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/arith_routines_logist.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/audio_encoder_isacfix.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/bandwidth_estimator.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/decode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/decode_bwe.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/decode_plc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/encode.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/entropy_coding.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/fft.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/filterbank_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/filterbanks.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/filters.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/initialize.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/isacfix.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/lattice.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/lattice_c.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/lpc_masking_model.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/lpc_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_estimator.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_estimator_c.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_filter.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_filter_c.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_gain_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/pitch_lag_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/spectrum_ar_model_tables.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/transform.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/source/transform_tables.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/interface
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET pcm16b)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/pcm16b/audio_encoder_pcm16b.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/pcm16b/pcm16b.c
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/pcm16b/include
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET red)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/red/audio_encoder_copy_red.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/red/include
  ${WEBRTC_ROOT}/webrtc
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET webrtc_opus)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra  -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O2 -fno-ident -fdata-sections -ffunction-sections -funwind-tables")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/opus/audio_encoder_opus.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/opus/opus_interface.c
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
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/third_party/opus/src/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET neteq)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/accelerate.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/audio_classifier.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/audio_decoder_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/audio_multi_vector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/audio_vector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/background_noise.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/buffer_level_filter.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/comfort_noise.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/decision_logic.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/decision_logic_fax.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/decision_logic_normal.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/decoder_database.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/delay_manager.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/delay_peak_detector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/dsp_helper.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/dtmf_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/dtmf_tone_generator.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/expand.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/merge.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/neteq_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/neteq.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/statistics_calculator.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/normal.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/packet_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/payload_splitter.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/post_decode_vad.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/preemptive_expand.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/random_vector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/rtcp.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/sync_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/timestamp_scaler.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/neteq/time_stretch.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/cng/include
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g711/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/g722/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/ilbc/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/fix/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/pcm16b/include
  ${WEBRTC_ROOT}/third_party/opus/src/src
  ${WEBRTC_ROOT}/third_party/opus/src/celt
  ${WEBRTC_ROOT}/third_party/opus/src/include
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;WEBRTC_CODEC_OPUS;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET media_file)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/media_file/source/media_file_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/media_file/source/media_file_utility.cc
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
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET rtp_rtcp)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/bitrate.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/fec_receiver_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/receive_statistics_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/remote_ntp_time_estimator.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_header_parser.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_rtcp_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtcp_packet.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtcp_receiver.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtcp_receiver_help.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtcp_sender.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtcp_utility.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_header_extension.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_receiver_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_sender.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_utility.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/ssrc_database.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/tmmbr_help.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/dtmf_queue.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_receiver_audio.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_sender_audio.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/forward_error_correction.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/forward_error_correction_internal.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/h264_sps_parser.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/producer_fec.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_packet_history.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_payload_registry.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_receiver_strategy.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_receiver_video.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_sender_video.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_format.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_format_h264.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_format_vp8.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/rtp_format_video_generic.cc
  ${WEBRTC_ROOT}/webrtc/modules/rtp_rtcp/source/vp8_partition_aggregator.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET remote_bitrate_estimator)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/aimd_rate_control.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/inter_arrival.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/mimd_rate_control.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/overuse_detector.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/overuse_estimator.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/rate_statistics.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/remote_bitrate_estimator_abs_send_time.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/remote_bitrate_estimator_single_stream.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/remote_rate_control.cc
  ${WEBRTC_ROOT}/webrtc/modules/remote_bitrate_estimator/test/bwe_test_logging.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;BWE_TEST_LOGGING_COMPILE_TIME_ENABLE=0;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET paced_sender)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/pacing/bitrate_prober.cc
  ${WEBRTC_ROOT}/webrtc/modules/pacing/paced_sender.cc
  ${WEBRTC_ROOT}/webrtc/modules/pacing/packet_router.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET bitrate_controller)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/bitrate_controller/bitrate_allocator.cc
  ${WEBRTC_ROOT}/webrtc/modules/bitrate_controller/bitrate_controller_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/bitrate_controller/send_side_bandwidth_estimation.cc
  ${WEBRTC_ROOT}/webrtc/modules/bitrate_controller/send_time_history.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET video_processing)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/brighten.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/brightness_detection.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/content_analysis.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/deflickering.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/frame_preprocessor.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/spatial_resampler.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/video_decimator.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/video_processing_impl.cc
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
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  ${WEBRTC_ROOT}/webrtc/common_video/interface
  ${WEBRTC_ROOT}/webrtc/common_video/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET video_capture)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/external/device_info_external.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/external/video_capture_external.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET video_processing_sse2)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -msse2 -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_processing/main/source/content_analysis_sse2.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET webrtc_video_coding)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/codec_database.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/codec_timer.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/content_metrics_processing.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/decoding_state.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/encoded_frame.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/frame_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/generic_decoder.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/generic_encoder.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/inter_frame_delay.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/jitter_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/jitter_estimator.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/media_opt_util.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/media_optimization.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/packet.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/qm_select.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/receiver.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/rtt_filter.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/session_info.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/timestamp_map.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/timing.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/video_coding_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/video_sender.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/main/source/video_receiver.cc
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

SET(TARGET webrtc_h264)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/codecs/h264/h264.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET webrtc_i420)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_coding/codecs/i420/main/source/i420.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_conference_mixer)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_conference_mixer/source/audio_frame_manipulator.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_conference_mixer/source/level_indicator.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_conference_mixer/source/audio_conference_mixer_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_conference_mixer/source/time_scheduler.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_processing)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/aec_core.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/aec_rdft.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/aec_resampler.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/echo_cancellation.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aecm/aecm_core.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aecm/echo_control_mobile.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/agc.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/agc_manager_direct.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/histogram.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/legacy/analog_agc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/legacy/digital_agc.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/agc/utility.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/audio_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/audio_processing_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/beamformer/covariance_matrix_generator.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/beamformer/nonlinear_beamformer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/echo_cancellation_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/echo_control_mobile_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/gain_control_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/high_pass_filter_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/intelligibility/intelligibility_enhancer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/intelligibility/intelligibility_utils.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/level_estimator_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/noise_suppression_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/processing_component.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/rms_level.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/splitting_filter.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/three_band_filter_bank.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/transient/moving_moments.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/transient/transient_detector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/transient/transient_suppressor.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/transient/wpd_node.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/transient/wpd_tree.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/typing_detection.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/utility/delay_estimator.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/utility/delay_estimator_wrapper.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/gmm.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/pitch_based_vad.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/pitch_internal.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/pole_zero_filter.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/standalone_vad.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/vad_audio_proc.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/vad_circular_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/vad/voice_activity_detector.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/voice_detection_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/ns/noise_suppression.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/ns/ns_core.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aecm/aecm_core_c.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})
ADD_DEPENDENCIES(${TARGET} audioproc_debug_proto)

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_coding/codecs/isac/main/interface
  ${WEBRTC_ROOT}/webrtc
  ${OUT}/gen/protoc_out
  ${WEBRTC_ROOT}/third_party/protobuf
  ${WEBRTC_ROOT}/third_party/protobuf/src
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;WEBRTC_AUDIOPROC_DEBUG_DUMP;WEBRTC_NS_FLOAT;PROTOBUF_USE_DLLS;GOOGLE_PROTOBUF_NO_RTTI;GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_processing_sse2)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -msse2 -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/aec_core_sse2.c
  ${WEBRTC_ROOT}/webrtc/modules/audio_processing/aec/aec_rdft_sse2.c
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audio_device)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/audio_device_buffer.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/audio_device_generic.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/dummy/audio_device_dummy.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/dummy/file_audio_device.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/dummy/file_audio_device_factory.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/audio_device_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/alsasymboltable_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/audio_device_alsa_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/audio_mixer_manager_alsa_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/latebindingsymboltable_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/audio_device_pulse_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/audio_mixer_manager_pulse_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux/pulseaudiosymboltable_linux.cc
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
  ${WEBRTC_ROOT}/webrtc/modules/audio_device
  ${WEBRTC_ROOT}/webrtc/modules/interface
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/include
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/dummy
  ${WEBRTC_ROOT}/webrtc/modules/audio_device/linux
  ${WEBRTC_ROOT}/webrtc/common_audio/resampler/include
  ${WEBRTC_ROOT}/webrtc/common_audio/signal_processing/include
  ${WEBRTC_ROOT}/webrtc/common_audio/vad/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;LINUX_ALSA;LINUX_PULSE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET video_capture_module)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/device_info_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/video_capture_factory.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/video_capture_impl.cc
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

SET(TARGET video_capture_module_internal_impl)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/linux/device_info_linux.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_capture/linux/video_capture_linux.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET video_render_module)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_render/external/video_render_external_impl.cc
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

SET(TARGET video_render_module_internal_impl)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/modules/video_render/video_render_internal_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_render/linux/video_render_linux_impl.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_render/linux/video_x11_channel.cc
  ${WEBRTC_ROOT}/webrtc/modules/video_render/linux/video_x11_render.cc
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

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET audioproc_debug_proto)

SET(C_FLAGS "-Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -Wnon-virtual-dtor -Woverloaded-virtual -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${OUT}/gen/protoc_out/webrtc/audio_processing/debug.pb.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_LIBRARY(${TARGET} STATIC ${SOURCES})

SET(PROTOC ${OUT}/protoc)
SET(PROTOC_WRAPPER ${WEBRTC_ROOT}/tools/protoc_wrapper/protoc_wrapper.py)
ADD_CUSTOM_COMMAND(
  OUTPUT ${OUT}/gen/protoc_out/webrtc/audio_processing/debug.pb.cc
  COMMAND mkdir -p ${OUT}/gen/protoc_out/webrtc/audio_processing ${OUT}/pyproto/webrtc/audio_processing
  COMMAND python ${PROTOC_WRAPPER} --include '' --protobuf ${OUT}/gen/protoc_out/webrtc/audio_processing/debug.pb.h --proto-in-dir ${TARGET_ROOT}/audio_processing --proto-in-file ${TARGET_ROOT}/audio_processing/debug.proto --use-system-protobuf=0 -- ${PROTOC} --cpp_out "${OUT}/gen/protoc_out/webrtc/audio_processing"
  DEPENDS protoc
  )

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  ${OUT}/gen/protoc_out
  ${WEBRTC_ROOT}/third_party/protobuf
  ${WEBRTC_ROOT}/third_party/protobuf/src
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;PROTOBUF_USE_DLLS;GOOGLE_PROTOBUF_NO_RTTI;GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

ADD_SUBDIRECTORY(video_coding)
