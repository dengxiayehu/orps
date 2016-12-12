cmake_minimum_required(VERSION 2.6)

SET(TARGET rtc_base)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -I/usr/include/nss -I/usr/include/nspr -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/webrtc/base/asyncfile.cc
  ${WEBRTC_ROOT}/webrtc/base/asynchttprequest.cc
  ${WEBRTC_ROOT}/webrtc/base/asyncinvoker.cc
  ${WEBRTC_ROOT}/webrtc/base/asyncpacketsocket.cc
  ${WEBRTC_ROOT}/webrtc/base/asyncresolverinterface.cc
  ${WEBRTC_ROOT}/webrtc/base/asyncsocket.cc
  ${WEBRTC_ROOT}/webrtc/base/asynctcpsocket.cc
  ${WEBRTC_ROOT}/webrtc/base/asyncudpsocket.cc
  ${WEBRTC_ROOT}/webrtc/base/autodetectproxy.cc
  ${WEBRTC_ROOT}/webrtc/base/bandwidthsmoother.cc
  ${WEBRTC_ROOT}/webrtc/base/base64.cc
  ${WEBRTC_ROOT}/webrtc/base/common.cc
  ${WEBRTC_ROOT}/webrtc/base/cpumonitor.cc
  ${WEBRTC_ROOT}/webrtc/base/crc32.cc
  ${WEBRTC_ROOT}/webrtc/base/cryptstring.cc
  ${WEBRTC_ROOT}/webrtc/base/dbus.cc
  ${WEBRTC_ROOT}/webrtc/base/diskcache.cc
  ${WEBRTC_ROOT}/webrtc/base/fileutils.cc
  ${WEBRTC_ROOT}/webrtc/base/firewallsocketserver.cc
  ${WEBRTC_ROOT}/webrtc/base/flags.cc
  ${WEBRTC_ROOT}/webrtc/base/helpers.cc
  ${WEBRTC_ROOT}/webrtc/base/httpbase.cc
  ${WEBRTC_ROOT}/webrtc/base/httpclient.cc
  ${WEBRTC_ROOT}/webrtc/base/httpcommon.cc
  ${WEBRTC_ROOT}/webrtc/base/httprequest.cc
  ${WEBRTC_ROOT}/webrtc/base/httpserver.cc
  ${WEBRTC_ROOT}/webrtc/base/ipaddress.cc
  ${WEBRTC_ROOT}/webrtc/base/json.cc
  ${WEBRTC_ROOT}/webrtc/base/latebindingsymboltable.cc
  ${WEBRTC_ROOT}/webrtc/base/libdbusglibsymboltable.cc
  ${WEBRTC_ROOT}/webrtc/base/linux.cc
  ${WEBRTC_ROOT}/webrtc/base/linuxfdwalk.c
  ${WEBRTC_ROOT}/webrtc/base/messagedigest.cc
  ${WEBRTC_ROOT}/webrtc/base/messagehandler.cc
  ${WEBRTC_ROOT}/webrtc/base/messagequeue.cc
  ${WEBRTC_ROOT}/webrtc/base/multipart.cc
  ${WEBRTC_ROOT}/webrtc/base/natserver.cc
  ${WEBRTC_ROOT}/webrtc/base/natsocketfactory.cc
  ${WEBRTC_ROOT}/webrtc/base/nattypes.cc
  ${WEBRTC_ROOT}/webrtc/base/nethelpers.cc
  ${WEBRTC_ROOT}/webrtc/base/network.cc
  ${WEBRTC_ROOT}/webrtc/base/optionsfile.cc
  ${WEBRTC_ROOT}/webrtc/base/pathutils.cc
  ${WEBRTC_ROOT}/webrtc/base/physicalsocketserver.cc
  ${WEBRTC_ROOT}/webrtc/base/posix.cc
  ${WEBRTC_ROOT}/webrtc/base/profiler.cc
  ${WEBRTC_ROOT}/webrtc/base/proxydetect.cc
  ${WEBRTC_ROOT}/webrtc/base/proxyinfo.cc
  ${WEBRTC_ROOT}/webrtc/base/proxyserver.cc
  ${WEBRTC_ROOT}/webrtc/base/ratelimiter.cc
  ${WEBRTC_ROOT}/webrtc/base/sha1.cc
  ${WEBRTC_ROOT}/webrtc/base/sha1digest.cc
  ${WEBRTC_ROOT}/webrtc/base/sharedexclusivelock.cc
  ${WEBRTC_ROOT}/webrtc/base/signalthread.cc
  ${WEBRTC_ROOT}/webrtc/base/sigslot.cc
  ${WEBRTC_ROOT}/webrtc/base/socketadapters.cc
  ${WEBRTC_ROOT}/webrtc/base/socketaddress.cc
  ${WEBRTC_ROOT}/webrtc/base/socketaddresspair.cc
  ${WEBRTC_ROOT}/webrtc/base/socketpool.cc
  ${WEBRTC_ROOT}/webrtc/base/socketstream.cc
  ${WEBRTC_ROOT}/webrtc/base/ssladapter.cc
  ${WEBRTC_ROOT}/webrtc/base/sslfingerprint.cc
  ${WEBRTC_ROOT}/webrtc/base/sslidentity.cc
  ${WEBRTC_ROOT}/webrtc/base/sslsocketfactory.cc
  ${WEBRTC_ROOT}/webrtc/base/sslstreamadapter.cc
  ${WEBRTC_ROOT}/webrtc/base/sslstreamadapterhelper.cc
  ${WEBRTC_ROOT}/webrtc/base/stream.cc
  ${WEBRTC_ROOT}/webrtc/base/systeminfo.cc
  ${WEBRTC_ROOT}/webrtc/base/task.cc
  ${WEBRTC_ROOT}/webrtc/base/taskparent.cc
  ${WEBRTC_ROOT}/webrtc/base/taskrunner.cc
  ${WEBRTC_ROOT}/webrtc/base/testclient.cc
  ${WEBRTC_ROOT}/webrtc/base/thread.cc
  ${WEBRTC_ROOT}/webrtc/base/timing.cc
  ${WEBRTC_ROOT}/webrtc/base/transformadapter.cc
  ${WEBRTC_ROOT}/webrtc/base/unixfilesystem.cc
  ${WEBRTC_ROOT}/webrtc/base/urlencode.cc
  ${WEBRTC_ROOT}/webrtc/base/versionparsing.cc
  ${WEBRTC_ROOT}/webrtc/base/virtualsocketserver.cc
  ${WEBRTC_ROOT}/webrtc/base/worker.cc
  ${WEBRTC_ROOT}/webrtc/base/nssidentity.cc
  ${WEBRTC_ROOT}/webrtc/base/nssstreamadapter.cc
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
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  ${WEBRTC_ROOT}/net/third_party/nss/ssl
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;EXPAT_RELATIVE_PATH;WEBRTC_POSIX;WEBRTC_LINUX;WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE;FEATURE_ENABLE_SSL;LOGGING=1;SSL_USE_NSS;HAVE_NSS_SSL_H;SSL_USE_NSS_RNG;USE_LIBPCI=1;USE_NSS_CERTS=1;__STDC_CONSTANT_MACROS;__STDC_FORMAT_MACROS;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET rtc_base_approved)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -Werror -pthread -fno-strict-aliasing -Wall -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wno-strict-overflow -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wsign-compare -Wnon-virtual-dtor -Woverloaded-virtual -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  bitbuffer.cc
  buffer.cc
  bufferqueue.cc
  bytebuffer.cc
  checks.cc
  criticalsection.cc
  event.cc
  event_tracer.cc
  exp_filter.cc
  logging.cc
  md5.cc
  md5digest.cc
  platform_file.cc
  platform_thread.cc
  ratetracker.cc
  stringencode.cc
  stringutils.cc
  thread_checker_impl.cc
  timeutils.cc
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
