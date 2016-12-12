cmake_minimum_required(VERSION 2.6)

SET(TARGET jpeg_turbo)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcapimin.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcapistd.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jccoefct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jccolor.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcdctmgr.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jchuff.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcinit.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcmainct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcmarker.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcmaster.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcomapi.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcparam.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcphuff.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcprepct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jcsample.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdapimin.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdapistd.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdatadst.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdatasrc.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdcoefct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdcolor.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jddctmgr.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdhuff.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdinput.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdmainct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdmarker.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdmaster.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdmerge.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdphuff.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdpostct.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jdsample.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jerror.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jfdctflt.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jfdctfst.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jfdctint.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jidctflt.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jidctfst.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jidctint.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jidctred.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jmemmgr.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jmemnobs.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jquant1.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jquant2.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/jutils.c
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jsimd_x86_64.c
  ${OUT}/gen/third_party/libjpeg_turbo/jccolss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcgrass2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2f-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2i-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcsamss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdcolss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdmerss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdsamss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfss2fst-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfss2int-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfsseflt-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2flt-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2fst-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2int-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2red-64.o
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
  ${WEBRTC_ROOT}/third_party/libjpeg_turbo
  )

ADD_CUSTOM_COMMAND(OUTPUT
  ${OUT}/gen/third_party/libjpeg_turbo/jccolss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcgrass2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2f-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2i-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jcsamss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdcolss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdmerss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jdsamss2-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfss2fst-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfss2int-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jfsseflt-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2flt-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2fst-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2int-64.o
  ${OUT}/gen/third_party/libjpeg_turbo/jiss2red-64.o
  COMMAND mkdir -p ${OUT}/gen/third_party/libjpeg_turbo
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jccolss2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jccolss2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jcgrass2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jcgrass2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2f-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jcqnts2f-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jcqnts2i-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jcqnts2i-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jcsamss2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jcsamss2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jdcolss2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jdcolss2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jdmerss2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jdmerss2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jdsamss2-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jdsamss2-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jfss2fst-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jfss2fst-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jfss2int-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jfss2int-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jfsseflt-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jfsseflt-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jiss2flt-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jiss2flt-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jiss2fst-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jiss2fst-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jiss2int-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jiss2int-64.asm
  COMMAND ${OUT}/yasm -felf64 -D__x86_64__ -DELF -Ilinux/ -DRGBX_FILLER_0XFF -DSTRICT_MEMORY_ACCESS -Isimd/ -o ${OUT}/gen/third_party/libjpeg_turbo/jiss2red-64.o ${WEBRTC_ROOT}/third_party/libjpeg_turbo/simd/jiss2red-64.asm
  DEPENDS yasm
  WORKING_DIRECTORY ${TARGET_ROOT}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;WITH_SIMD;MOTION_JPEG_SUPPORTED;NO_GETENV;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
