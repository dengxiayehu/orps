cmake_minimum_required(VERSION 2.6)

SET(OUT ${PROJECT_BINARY_DIR}/out)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUT})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUT})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUT})

SET(CONTRIB_INCLUDE "$ENV{CONTRIB_LINUX_INSTALL_DIR}/include")
SET(CONTRIB_LIBRARY "$ENV{CONTRIB_LINUX_INSTALL_DIR}/lib")

SET(COMMON_INCLUDES ${CONTRIB_INCLUDE} ${CONTRIB_INCLUDE}/bellagio .)
SET(COMMON_COMPILE_DEFINITIONS "HAVE_CONFIG_H")
SET(COMMON_COMPILE_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")
SET(COMMON_LINK_FLAGS "-pthread -ldl")

ADD_SUBDIRECTORY(access)
