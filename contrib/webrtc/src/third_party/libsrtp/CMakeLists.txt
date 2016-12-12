cmake_minimum_required(VERSION 2.6)

SET(TARGET srtp)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-unused-variable -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/srtp/ekt.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/srtp/srtp.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/cipher/aes.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/cipher/cipher.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/cipher/null_cipher.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/hash/auth.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/hash/null_auth.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/kernel/alloc.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/kernel/crypto_kernel.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/kernel/err.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/kernel/key.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/math/datatypes.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/math/gf2_8.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/math/stat.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/replay/rdb.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/replay/rdbx.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/replay/ut_sim.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/rng/rand_source.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/cipher/aes_gcm_ossl.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/cipher/aes_icm_ossl.c
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/hash/hmac_ossl.c
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
  ${WEBRTC_ROOT}/third_party/libsrtp/config
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/include
  ${WEBRTC_ROOT}/third_party/libsrtp/srtp/crypto/include
  ${WEBRTC_ROOT}/third_party/boringssl/src/include
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "HAVE_CONFIG_H;HAVE_STDLIB_H;HAVE_STRING_H;TESTAPP_SOURCE;V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;OPENSSL;HAVE_INT16_T;HAVE_INT32_T;HAVE_INT8_T;HAVE_UINT16_T;HAVE_UINT32_T;HAVE_UINT64_T;HAVE_UINT8_T;HAVE_STDINT_H;HAVE_INTTYPES_H;HAVE_NETINET_IN_H;HAVE_ARPA_INET_H;HAVE_UNISTD_H;CPU_CISC;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;USE_LIBPCI=1;USE_OPENSSL=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
