cmake_minimum_required(VERSION 2.6)

SET(TARGET usrsctplib)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -w -I/usr/include/nss -I/usr/include/nspr -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  usrsctplib/netinet/sctp_asconf.c
  usrsctplib/netinet/sctp_auth.c
  usrsctplib/netinet/sctp_bsd_addr.c
  usrsctplib/netinet/sctp_callout.c
  usrsctplib/netinet/sctp_cc_functions.c
  usrsctplib/netinet/sctp_crc32.c
  usrsctplib/netinet/sctp_indata.c
  usrsctplib/netinet/sctp_input.c
  usrsctplib/netinet/sctp_output.c
  usrsctplib/netinet/sctp_pcb.c
  usrsctplib/netinet/sctp_peeloff.c
  usrsctplib/netinet/sctp_sha1.c
  usrsctplib/netinet/sctp_ss_functions.c
  usrsctplib/netinet/sctp_sysctl.c
  usrsctplib/netinet/sctp_timer.c
  usrsctplib/netinet/sctp_userspace.c
  usrsctplib/netinet/sctp_usrreq.c
  usrsctplib/netinet/sctputil.c
  usrsctplib/netinet6/sctp6_usrreq.c
  usrsctplib/user_environment.c
  usrsctplib/user_mbuf.c
  usrsctplib/user_recv_thread.c
  usrsctplib/user_socket.c
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
  ${WEBRTC_ROOT}/third_party/usrsctp/usrsctplib
  ${WEBRTC_ROOT}/third_party/usrsctp/usrsctplib/netinet
  ${WEBRTC_ROOT}/net/third_party/nss/ssl
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "SCTP_PROCESS_LEVEL_LOCKS;SCTP_SIMPLE_ALLOCATOR;__Userspace__;V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;SCTP_USE_NSS_SHA1;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;__Userspace_os_Linux;NON_WINDOWS_DEFINE;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1;")
