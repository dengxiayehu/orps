cmake_minimum_required(VERSION 2.6)

SET(TARGET genmodule)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/genmodule.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET genmacro)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -B/home/jwf/workspace/webrtc-make/src/third_party/binutils/Linux_x64/Release/bin -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/genmacro/genmacro.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET genperf)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/genperf/genperf.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/genperf/perfect.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})
ADD_DEPENDENCIES(${TARGET} genperf_libs)
TARGET_LINK_LIBRARIES(${TARGET} ${OUT}/libgenperf_libs.a)

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET genperf_libs)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -ansi -pedantic -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/phash.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/xmalloc.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/xstrdup.c
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
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1 ;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;HAVE_CONFIG_H;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET genversion)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/nasm/genversion.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET genstring)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/genstring.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET re2c)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -Wno-switch -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/main.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/code.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/dfa.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/parser.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/actions.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/scanner.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/mbo_getopt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/substr.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/tools/re2c/translate.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET yasm)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -std=gnu99 -ansi -pedantic -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -Wno-incompatible-pointer-types -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/frontends/yasm/yasm-options.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/frontends/yasm/yasm.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/assocdat.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bc-align.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bc-data.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bc-incbin.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bc-org.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bc-reserve.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bitvect.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/bytecode.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/errwarn.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/expr.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/file.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/floatnum.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/hamt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/insn.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/intnum.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/inttree.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/linemap.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/md5.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/mergesort.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/section.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/strcasecmp.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/strsep.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/symrec.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/valparam.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/libyasm/value.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/lc3b/lc3barch.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/lc3b/lc3bbc.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86arch.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86bc.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86expr.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86id.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/codeview/cv-dbgfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/codeview/cv-symline.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/codeview/cv-type.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/dwarf2/dwarf2-aranges.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/dwarf2/dwarf2-dbgfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/dwarf2/dwarf2-info.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/dwarf2/dwarf2-line.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/null/null-dbgfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/dbgfmts/stabs/stabs-dbgfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/listfmts/nasm/nasm-listfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/bin/bin-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/coff/coff-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/coff/win64-except.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/dbg/dbg-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/elf/elf-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/elf/elf-x86-amd64.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/elf/elf-x86-x86.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/elf/elf.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/macho/macho-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/rdf/rdf-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/objfmts/xdf/xdf-objfmt.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/gas/gas-parse.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/gas/gas-parse-intel.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/gas/gas-parser.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/nasm/nasm-parse.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/nasm/nasm-parser.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/cpp/cpp-preproc.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/nasm/nasm-eval.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/nasm/nasm-pp.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/nasm/nasm-preproc.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/nasm/nasmlib.c
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/preprocs/raw/raw-preproc.c
  ${OUT}/gen/third_party/yasm/x86cpu.c
  ${OUT}/gen/third_party/yasm/x86regtmod.c
  ${OUT}/geni/third_party/yasm/nasm-macros.c
  ${OUT}/geni/third_party/yasm/lc3bid.c
  ${OUT}/geni/third_party/yasm/module.c
  ${OUT}/geni/third_party/yasm/gas-token.c
  ${OUT}/geni/third_party/yasm/nasm-token.c
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})
TARGET_LINK_LIBRARIES(${TARGET} ${OUT}/libgenperf_libs.a)

ADD_CUSTOM_COMMAND(
  OUTPUT ${OUT}/gen/third_party/yasm/x86cpu.c
         ${OUT}/gen/third_party/yasm/x86regtmod.c
         ${OUT}/geni/third_party/yasm/nasm-macros.c
         ${OUT}/geni/third_party/yasm/nasm-version.c
         ${OUT}/geni/third_party/yasm/win64-gas.c
         ${OUT}/geni/third_party/yasm/win64-nasm.c
         ${OUT}/geni/third_party/yasm/license.c
         ${OUT}/geni/third_party/yasm/lc3bid.c
         ${OUT}/geni/third_party/yasm/module.c
         ${OUT}/geni/third_party/yasm/x86insn_nasm.c
         ${OUT}/geni/third_party/yasm/x86insn_gas.c
         ${OUT}/geni/third_party/yasm/gas-token.c
         ${OUT}/geni/third_party/yasm/nasm-token.c
  COMMAND mkdir -p ${OUT}/gen/third_party/yasm
  COMMAND ${TARGET_ROOT}/source/patched-yasm/modules/arch/x86/gen_x86_insn.py ${OUT}/gen/third_party/yasm
  COMMAND ${OUT}/genversion ${OUT}/gen/third_party/yasm/version.mac
  COMMAND ${OUT}/genperf ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86cpu.gperf ${OUT}/gen/third_party/yasm/x86cpu.c
  COMMAND ${OUT}/genperf ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/arch/x86/x86regtmod.gperf ${OUT}/gen/third_party/yasm/x86regtmod.c
  COMMAND mkdir -p ${OUT}/geni/third_party/yasm
  COMMAND ${OUT}/genmacro ${OUT}/geni/third_party/yasm/nasm-macros.c nasm_standard_mac source/patched-yasm/modules/parsers/nasm/nasm-std.mac
  COMMAND ${OUT}/genmacro ${OUT}/geni/third_party/yasm/nasm-version.c nasm_version_mac ${OUT}/gen/third_party/yasm/version.mac
  COMMAND ${OUT}/genmacro ${OUT}/geni/third_party/yasm/win64-gas.c win64_gas_stdmac source/patched-yasm/modules/objfmts/coff/win64-gas.mac
  COMMAND ${OUT}/genmacro ${OUT}/geni/third_party/yasm/win64-nasm.c win64_nasm_stdmac source/patched-yasm/modules/objfmts/coff/win64-nasm.mac
  COMMAND ${OUT}/genstring license_msg ${OUT}/geni/third_party/yasm/license.c source/patched-yasm/COPYING
  COMMAND ${OUT}/re2c -s -o ${OUT}/geni/third_party/yasm/lc3bid.c source/patched-yasm/modules/arch/lc3b/lc3bid.re
  COMMAND ${OUT}/genmodule source/patched-yasm/libyasm/module.in source/config/linux/Makefile ${OUT}/geni/third_party/yasm/module.c
  COMMAND ${OUT}/genperf ${OUT}/gen/third_party/yasm/x86insn_nasm.gperf ${OUT}/geni/third_party/yasm/x86insn_nasm.c
  COMMAND ${OUT}/genperf ${OUT}/gen/third_party/yasm/x86insn_gas.gperf ${OUT}/geni/third_party/yasm/x86insn_gas.c
  COMMAND ${OUT}/re2c -b -o ${OUT}/geni/third_party/yasm/gas-token.c ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/gas/gas-token.re
  COMMAND ${OUT}/re2c -b -o ${OUT}/geni/third_party/yasm/nasm-token.c ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm/modules/parsers/nasm/nasm-token.re
  WORKING_DIRECTORY ${TARGET_ROOT}
  DEPENDS genversion genperf
  )

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}/third_party/yasm/source/config/linux
  ${WEBRTC_ROOT}/third_party/yasm/source/patched-yasm
  ${OUT}/gen/third_party/yasm
  ${OUT}/geni/third_party/yasm
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;HAVE_CONFIG_H;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
