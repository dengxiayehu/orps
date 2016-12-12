cmake_minimum_required(VERSION 2.6)

SET(TARGET jingle_media)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  media/base/capturemanager.cc
  media/base/capturerenderadapter.cc
  media/base/codec.cc
  media/base/constants.cc
  media/base/cpuid.cc
  media/base/mediaengine.cc
  media/base/rtpdataengine.cc
  media/base/rtpdump.cc
  media/base/rtputils.cc
  media/base/streamparams.cc
  media/base/videoadapter.cc
  media/base/videocapturer.cc
  media/base/videocommon.cc
  media/base/videoframe.cc
  media/base/videoframefactory.cc
  media/base/yuvframegenerator.cc
  media/devices/devicemanager.cc
  media/devices/filevideocapturer.cc
  media/devices/yuvframescapturer.cc
  media/sctp/sctpdataengine.cc
  media/webrtc/simulcast.cc
  media/webrtc/webrtcmediaengine.cc
  media/webrtc/webrtcpassthroughrender.cc
  media/webrtc/webrtcvideocapturer.cc
  media/webrtc/webrtcvideocapturerfactory.cc
  media/webrtc/webrtcvideoengine2.cc
  media/webrtc/webrtcvideoframe.cc
  media/webrtc/webrtcvideoframefactory.cc
  media/webrtc/webrtcvoiceengine.cc
  media/devices/libudevsymboltable.cc
  media/devices/linuxdeviceinfo.cc
  media/devices/linuxdevicemanager.cc
  media/devices/v4llookup.cc
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
  ${WEBRTC_ROOT}/third_party
  ${WEBRTC_ROOT}/third_party/webrtc
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/third_party/usrsctp
  ${WEBRTC_ROOT}/talk/third_party/libudev
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/third_party/libyuv
  ${WEBRTC_ROOT}/third_party/usrsctp/usrsctplib
  ${WEBRTC_ROOT}/third_party/usrsctp/usrsctplib/netinet
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS; EXPAT_RELATIVE_PATH; FEATURE_ENABLE_VOICEMAIL; GTEST_RELATIVE_PATH; JSONCPP_RELATIVE_PATH; LOGGING=1; SRTP_RELATIVE_PATH; FEATURE_ENABLE_SSL; FEATURE_ENABLE_PSTN; HAVE_SCTP; HAVE_SRTP; HAVE_WEBRTC_VIDEO; HAVE_WEBRTC_VOICE; _FILE_OFFSET_BITS=64; CHROMIUM_BUILD; CR_CLANG_REVISION=239765-1; UI_COMPOSITOR_IMAGE_TRANSPORT; USE_AURA=1; USE_ASH=1; USE_PANGO=1; USE_CAIRO=1; USE_DEFAULT_RENDER_THEME=1; USE_LIBJPEG_TURBO=1; ENABLE_ONE_CLICK_SIGNIN; ENABLE_PRE_SYNC_BACKUP; ENABLE_REMOTING=1; ENABLE_WEBRTC=1; ENABLE_MEDIA_ROUTER=1; ENABLE_PEPPER_CDMS; ENABLE_CONFIGURATION_POLICY; ENABLE_NOTIFICATIONS; ENABLE_HIDPI=1; ENABLE_TOPCHROME_MD=1; USE_UDEV; DONT_EMBED_BUILD_METADATA; ENABLE_TASK_MANAGER=1; ENABLE_EXTENSIONS=1; ENABLE_PLUGINS=1; ENABLE_SESSION_SERVICE=1; ENABLE_AUTOFILL_DIALOG=1; ENABLE_BACKGROUND=1; CLD_VERSION=2; ENABLE_PRINTING=1; ENABLE_BASIC_PRINTING=1; ENABLE_PRINT_PREVIEW=1; ENABLE_CAPTIVE_PORTAL_DETECTION=1; ENABLE_APP_LIST=1; ENABLE_SETTINGS_APP=1; ENABLE_SUPERVISED_USERS=1; ENABLE_MDNS=1; ENABLE_SERVICE_DISCOVERY=1; V8_USE_EXTERNAL_STARTUP_DATA; FULL_SAFE_BROWSING; SAFE_BROWSING_CSD; SAFE_BROWSING_DB_LOCAL; SAFE_BROWSING_SERVICE; LINUX; WEBRTC_LINUX; HASH_NAMESPACE=__gnu_cxx; WEBRTC_POSIX; DISABLE_DYNAMIC_CAST; _REENTRANT; USE_LIBPCI=1; USE_NSS_CERTS=1; DYNAMIC_ANNOTATIONS_ENABLED=1; WTF_USE_DYNAMIC_ANNOTATIONS=1; _DEBUG; _GLIBCXX_DEBUG=1;")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET jingle_p2p)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/talk/session/media/audiomonitor.cc
  ${WEBRTC_ROOT}/talk/session/media/bundlefilter.cc
  ${WEBRTC_ROOT}/talk/session/media/channel.cc
  ${WEBRTC_ROOT}/talk/session/media/channelmanager.cc
  ${WEBRTC_ROOT}/talk/session/media/currentspeakermonitor.cc
  ${WEBRTC_ROOT}/talk/session/media/mediamonitor.cc
  ${WEBRTC_ROOT}/talk/session/media/mediarecorder.cc
  ${WEBRTC_ROOT}/talk/session/media/mediasession.cc
  ${WEBRTC_ROOT}/talk/session/media/rtcpmuxfilter.cc
  ${WEBRTC_ROOT}/talk/session/media/srtpfilter.cc
  ${WEBRTC_ROOT}/talk/session/media/typingmonitor.cc
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
  ${WEBRTC_ROOT}/third_party
  ${WEBRTC_ROOT}/third_party/webrtc
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/testing/gtest/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/third_party/libsrtp/config
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/include
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;FEATURE_ENABLE_VOICEMAIL;GTEST_RELATIVE_PATH;JSONCPP_RELATIVE_PATH;LOGGING=1;SRTP_RELATIVE_PATH;FEATURE_ENABLE_SSL;FEATURE_ENABLE_PSTN;HAVE_SCTP;HAVE_SRTP;HAVE_WEBRTC_VIDEO;HAVE_WEBRTC_VOICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;LINUX;WEBRTC_LINUX;HASH_NAMESPACE=__gnu_cxx;WEBRTC_POSIX;DISABLE_DYNAMIC_CAST;_REENTRANT;HAVE_INT16_T;HAVE_INT32_T;HAVE_INT8_T;HAVE_UINT16_T;HAVE_UINT32_T;HAVE_UINT64_T;HAVE_UINT8_T;HAVE_STDINT_H;HAVE_INTTYPES_H;HAVE_NETINET_IN_H;CPU_CISC;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

SET(TARGET jingle_peerconnection)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/talk/app/webrtc/audiotrack.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/audiotrackrenderer.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/datachannel.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/dtlsidentityservice.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/dtlsidentitystore.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/dtmfsender.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/jsepicecandidate.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/jsepsessiondescription.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/localaudiosource.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/mediaconstraintsinterface.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/mediastream.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/mediastreamhandler.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/mediastreamsignaling.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/peerconnection.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/peerconnectionfactory.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/portallocatorfactory.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/remoteaudiosource.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/remotevideocapturer.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/sctputils.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/statscollector.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/statstypes.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/videosource.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/videotrack.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/videotrackrenderers.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/webrtcsdp.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/webrtcsession.cc
  ${WEBRTC_ROOT}/talk/app/webrtc/webrtcsessiondescriptionfactory.cc
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
  ${WEBRTC_ROOT}/third_party
  ${WEBRTC_ROOT}/third_party/webrtc
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  ${WEBRTC_ROOT}/third_party/libyuv/include
  ${WEBRTC_ROOT}/testing/gtest/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;FEATURE_ENABLE_VOICEMAIL;GTEST_RELATIVE_PATH;JSONCPP_RELATIVE_PATH;LOGGING=1;SRTP_RELATIVE_PATH;FEATURE_ENABLE_SSL;FEATURE_ENABLE_PSTN;HAVE_SCTP;HAVE_SRTP;HAVE_WEBRTC_VIDEO;HAVE_WEBRTC_VOICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;LINUX;WEBRTC_LINUX;HASH_NAMESPACE=__gnu_cxx;WEBRTC_POSIX;DISABLE_DYNAMIC_CAST;_REENTRANT;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")

########################################################################

ADD_SUBDIRECTORY(examples)
