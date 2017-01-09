cmake_minimum_required(VERSION 2.6)

SET(TARGET protobuf_lite)

SET(TARGET_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-unused-local-typedefs -Wno-format -Wno-unused-result -m64 -march=x86-64 -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11 -Wno-narrowing -Wno-literal-suffix")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/unknown_field_set.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/common.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/once.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/extension_set.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/generated_message_util.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/message_lite.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/repeated_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/wire_format_lite.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/coded_stream.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/zero_copy_stream.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
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
  ${WEBRTC_ROOT}/third_party/protobuf
  ${WEBRTC_ROOT}/third_party/protobuf/src
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;LIBPROTOBUF_EXPORTS;PROTOBUF_USE_DLLS;GOOGLE_PROTOBUF_NO_RTTI;GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET protobuf_full_do_not_use)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_doc_comment.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/strutil.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/substitute.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/stringprintf.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/structurally_valid.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/descriptor.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/descriptor.pb.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/descriptor_database.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/dynamic_message.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/extension_set.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/extension_set_heavy.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/generated_message_reflection.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/message.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/reflection_ops.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/service.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/text_format.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/wire_format.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/printer.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/tokenizer.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/zero_copy_stream_impl.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/importer.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/parser.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/unknown_field_set.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/common.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/stubs/once.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/generated_message_util.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/message_lite.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/repeated_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/wire_format_lite.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/coded_stream.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/zero_copy_stream.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
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
  ${WEBRTC_ROOT}/third_party/protobuf
  ${WEBRTC_ROOT}/third_party/protobuf/src
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;GOOGLE_PROTOBUF_NO_RTTI;GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

########################################################################

SET(TARGET protoc)

SET(C_FLAGS "-fstack-protector --param=ssp-buffer-size=4 -pthread -fno-strict-aliasing -Wno-unused-parameter -Wno-missing-field-initializers -pipe -fPIC -Wno-format -Wno-unused-result -Wno-char-subscripts -Wno-unneeded-internal-declaration -Wno-covered-switch-default -Wno-c++11-narrowing -Wno-deprecated-register -Wno-inconsistent-missing-override -O0 -g -funwind-tables -gsplit-dwarf")

SET(CXX_FLAGS "${C_FLAGS} -fno-exceptions -fno-rtti -fno-threadsafe-statics -Wno-deprecated -std=gnu++11")

SET(SOURCES
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/code_generator.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/command_line_interface.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/plugin.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/plugin.pb.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/subprocess.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/zip_writer.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_enum.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_enum_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_extension.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_file.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_generator.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_helpers.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_message.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_message_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_primitive_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_service.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/cpp/cpp_string_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_enum.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_enum_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_extension.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_file.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_generator.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_helpers.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_message.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_message_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_primitive_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_service.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/java/java_string_field.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/python/python_generator.cc
  ${WEBRTC_ROOT}/third_party/protobuf/src/google/protobuf/compiler/main.cc
  )

FOREACH(F ${SOURCES})
  IF(F MATCHES ".+\\.cpp$" OR F MATCHES ".+\\.cc$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${CXX_FLAGS}")
  ELSEIF(F MATCHES ".+\\.c$")
    SET_SOURCE_FILES_PROPERTIES(${F} PROPERTIES COMPILE_FLAGS "${C_FLAGS}")
  ENDIF()
ENDFOREACH()

ADD_EXECUTABLE(${TARGET} ${SOURCES})
ADD_DEPENDENCIES(${TARGET} protobuf_full_do_not_use)
TARGET_LINK_LIBRARIES(${TARGET} ${OUT}/libprotobuf_full_do_not_use.a)

TARGET_INCLUDE_DIRECTORIES(${TARGET} PRIVATE
  ${WEBRTC_ROOT}
  ${WEBRTC_ROOT}/third_party/protobuf
  ${WEBRTC_ROOT}/third_party/protobuf/src/src
  ${WEBRTC_ROOT}/third_party/protobuf/src
  )

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES COMPILE_DEFINITIONS "V8_DEPRECATION_WARNINGS;_FILE_OFFSET_BITS=64;CHROMIUM_BUILD;CR_CLANG_REVISION=239765-1;UI_COMPOSITOR_IMAGE_TRANSPORT;USE_AURA=1;USE_ASH=1;USE_PANGO=1;USE_CAIRO=1;USE_DEFAULT_RENDER_THEME=1;USE_LIBJPEG_TURBO=1;ENABLE_ONE_CLICK_SIGNIN;ENABLE_PRE_SYNC_BACKUP;ENABLE_REMOTING=1;ENABLE_WEBRTC=1;ENABLE_MEDIA_ROUTER=1;ENABLE_PEPPER_CDMS;ENABLE_CONFIGURATION_POLICY;ENABLE_NOTIFICATIONS;ENABLE_HIDPI=1;ENABLE_TOPCHROME_MD=1;USE_UDEV;DONT_EMBED_BUILD_METADATA;ENABLE_TASK_MANAGER=1;ENABLE_EXTENSIONS=1;ENABLE_PLUGINS=1;ENABLE_SESSION_SERVICE=1;ENABLE_AUTOFILL_DIALOG=1;ENABLE_BACKGROUND=1;CLD_VERSION=2;ENABLE_PRINTING=1;ENABLE_BASIC_PRINTING=1;ENABLE_PRINT_PREVIEW=1;ENABLE_CAPTIVE_PORTAL_DETECTION=1;ENABLE_APP_LIST=1;ENABLE_SETTINGS_APP=1;ENABLE_SUPERVISED_USERS=1;ENABLE_MDNS=1;ENABLE_SERVICE_DISCOVERY=1;V8_USE_EXTERNAL_STARTUP_DATA;FULL_SAFE_BROWSING;SAFE_BROWSING_CSD;SAFE_BROWSING_DB_LOCAL;SAFE_BROWSING_SERVICE;GOOGLE_PROTOBUF_NO_RTTI;GOOGLE_PROTOBUF_NO_STATIC_INITIALIZER;USE_LIBPCI=1;USE_NSS_CERTS=1;DYNAMIC_ANNOTATIONS_ENABLED=1;WTF_USE_DYNAMIC_ANNOTATIONS=1;_DEBUG;_GLIBCXX_DEBUG=1")

SET_TARGET_PROPERTIES(${TARGET} PROPERTIES LINK_FLAGS "-Wl,-z,now -Wl,-z,relro -Wl,--fatal-warnings -Wl,-z,defs -pthread -Wl,-z,noexecstack -fPIC -fuse-ld=gold -Wl,--disable-new-dtags")
