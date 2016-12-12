cmake_minimum_required(VERSION 2.6)

SET(TARGET peerconnection_direct)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/main.cc
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/defaults.cc
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/fake_main_wnd.cc
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/peer_connection_client.cc
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/conductor.cc
  ${WEBRTC_ROOT}/talk/examples/peerconnection/direct/fakeaudiocapturemodule.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})
ADD_DEPENDENCIES(${TARGET} jingle_peerconnection jsoncpp rtc_base webrtc_common rtc_base_approved crssl jingle_media video_render_module webrtc_utility audio_coding_module cng common_audio system_wrappers openmax_dl common_audio_sse2 audio_encoder_interface g711 g722 ilbc isac audio_decoder_interface isac_fix pcm16b red webrtc_opus opus neteq media_file common_video yuv jpeg_turbo webrtc bitrate_controller rtp_rtcp paced_sender remote_bitrate_estimator video_capture_module video_processing video_processing_sse2 webrtc_video_coding webrtc_h264 webrtc_i420 video_coding_utility webrtc_vp8 vpx vpx_intrinsics_mmx vpx_intrinsics_sse2 vpx_intrinsics_ssse3 vpx_intrinsics_sse4_1 vpx_intrinsics_avx2 webrtc_vp9 voice_engine audio_conference_mixer audio_processing audioproc_debug_proto protobuf_lite audio_processing_sse2 audio_device rtc_sound field_trial_default metrics_default rtc_xmllite rtc_xmpp rtc_p2p usrsctplib video_capture_module_internal_impl video_render_module_internal_impl jingle_p2p srtp boringssl)
TARGET_LINK_LIBRARIES(${TARGET}
  -Wl,--start-group 
  ${OUT}/libjingle_peerconnection.a
  ${OUT}/libjsoncpp.a
  ${OUT}/librtc_base.a
  ${OUT}/libwebrtc_common.a
  ${OUT}/librtc_base_approved.a
  ${OUT}/libcrssl.a
  ${OUT}/libjingle_media.a
  ${OUT}/libvideo_render_module.a
  ${OUT}/libwebrtc_utility.a
  ${OUT}/libaudio_coding_module.a
  ${OUT}/libcng.a
  ${OUT}/libcommon_audio.a
  ${OUT}/libsystem_wrappers.a
  ${OUT}/libopenmax_dl.a
  ${OUT}/libcommon_audio_sse2.a
  ${OUT}/libaudio_encoder_interface.a
  ${OUT}/libg711.a
  ${OUT}/libg722.a
  ${OUT}/libilbc.a
  ${OUT}/libisac.a
  ${OUT}/libaudio_decoder_interface.a
  ${OUT}/libisac_fix.a
  ${OUT}/libpcm16b.a
  ${OUT}/libred.a
  ${OUT}/libwebrtc_opus.a
  ${OUT}/libopus.a
  ${OUT}/libneteq.a
  ${OUT}/libmedia_file.a
  ${OUT}/libcommon_video.a
  ${OUT}/libyuv.a
  ${OUT}/libjpeg_turbo.a
  ${OUT}/libwebrtc.a
  ${OUT}/libbitrate_controller.a
  ${OUT}/librtp_rtcp.a
  ${OUT}/libpaced_sender.a
  ${OUT}/libremote_bitrate_estimator.a
  ${OUT}/libvideo_capture_module.a
  ${OUT}/libvideo_processing.a
  ${OUT}/libvideo_processing_sse2.a
  ${OUT}/libwebrtc_video_coding.a
  ${OUT}/libwebrtc_h264.a
  ${OUT}/libwebrtc_i420.a
  ${OUT}/libvideo_coding_utility.a
  ${OUT}/libwebrtc_vp8.a
  ${OUT}/libvpx.a
  ${OUT}/libvpx_intrinsics_mmx.a
  ${OUT}/libvpx_intrinsics_sse2.a
  ${OUT}/libvpx_intrinsics_ssse3.a
  ${OUT}/libvpx_intrinsics_sse4_1.a
  ${OUT}/libvpx_intrinsics_avx2.a
  ${OUT}/libwebrtc_vp9.a
  ${OUT}/libvoice_engine.a
  ${OUT}/libaudio_conference_mixer.a
  ${OUT}/libaudio_processing.a
  ${OUT}/libaudioproc_debug_proto.a
  ${OUT}/libprotobuf_lite.a
  ${OUT}/libaudio_processing_sse2.a
  ${OUT}/libaudio_device.a
  ${OUT}/librtc_sound.a
  ${OUT}/libfield_trial_default.a
  ${OUT}/libmetrics_default.a
  ${OUT}/librtc_xmllite.a
  ${OUT}/librtc_xmpp.a
  ${OUT}/librtc_p2p.a
  ${OUT}/libusrsctplib.a
  ${OUT}/libvideo_capture_module_internal_impl.a
  ${OUT}/libvideo_render_module_internal_impl.a
  ${OUT}/libjingle_p2p.a
  ${OUT}/libsrtp.a
  ${OUT}/libboringssl.a
  -Wl,--end-group
  )

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  ${WEBRTC_ROOT}/third_party
  ${WEBRTC_ROOT}/third_party/webrtc
  ${WEBRTC_ROOT}/webrtc
  ${WEBRTC_ROOT}/third_party/jsoncpp/overrides/include
  ${WEBRTC_ROOT}/third_party/jsoncpp/source/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;EXPAT_RELATIVE_PATH;FEATURE_ENABLE_VOICEMAIL;GTEST_RELATIVE_PATH;JSONCPP_RELATIVE_PATH;LOGGING=1;SRTP_RELATIVE_PATH;FEATURE_ENABLE_SSL;FEATURE_ENABLE_PSTN;HAVE_SCTP;HAVE_SRTP;HAVE_WEBRTC_VIDEO;HAVE_WEBRTC_VOICE;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;LINUX;WEBRTC_LINUX;HASH_NAMESPACE=__gnu_cxx;WEBRTC_POSIX;DISABLE_DYNAMIC_CAST;_REENTRANT;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all -ldl -lrt -lnss3 -lnssutil3 -lsmime3 -lplds4 -lplc4 -lnspr4 -lexpat -lm -lX11 -lXext")
