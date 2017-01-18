cmake_minimum_required(VERSION 2.6)

SET(TARGET omxrtmpsrctest)

SET(SOURCES
  omxrtmpsrctest.cc
  )

SET_SOURCE_FILES_PROPERTIES(${SOURCES} PROPERTIES COMPILE_FLAGS "${COMMON_COMPONENT_COMPILE_FLAGS}")

ADD_EXECUTABLE(${TARGET} ${SOURCES})
ADD_DEPENDENCIES(${TARGET} xutil)
TARGET_LINK_LIBRARIES(${TARGET} ${WEBRTC_OUT}/libwebrtc_common.a ${WEBRTC_OUT}/librtc_base.a ${WEBRTC_OUT}/librtc_base_approved.a ${WEBRTC_OUT}/libcrssl.a ${LIBOMXIL_BELLAGIO_STATIC_LIBRARY} $ENV{TARGET_OUT}/libxutil.a pthread dl)

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${COMMON_COMPONENT_INCLUDES}
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "${COMMON_COMPONENT_COMPILE_DEFINITIONS};")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags -m64 -Wl,--detect-odr-violations -Wl,--icf=all")
