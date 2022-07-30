cmake_minimum_required(VERSION 3.23)
project(silog
  VERSION 1.0.0
  DESCRIPTION ""
  LANGUAGES C CXX)

# Harmless but useful
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#####################################################
# Definitions, shared between silog implementations
#####################################################

add_library(silog-defs INTERFACE)
target_compile_features(silog-defs INTERFACE cxx_std_20)
target_compile_options(silog-defs INTERFACE
  $<$<PLATFORM_ID:Darwin>:-fobjc-arc>
  $<$<PLATFORM_ID:iOS>:-fobjc-arc>)
target_link_libraries(silog-defs INTERFACE
  $<$<PLATFORM_ID:Android>:android log>
  "$<$<PLATFORM_ID:Darwin>:-framework Cocoa>"
  "$<$<PLATFORM_ID:iOS>:-framework Foundation>"
  "$<$<PLATFORM_ID:iOS>:-framework UIKit>")
target_link_options(silog-defs INTERFACE
  $<$<PLATFORM_ID:Android>:-u ANativeActivity_onCreate>
  $<$<PLATFORM_ID:iOS>:-ObjC>)
target_sources(silog-defs INTERFACE FILE_SET HEADERS FILES silog.hpp)
install(TARGETS silog-defs EXPORT silog-targets FILE_SET HEADERS)

#####################################
# Base library, minimal requirements
#####################################

add_library(silog STATIC)
target_link_libraries(silog PUBLIC silog-defs)
target_sources(silog PRIVATE
  $<$<PLATFORM_ID:Android>:android.cpp>
  $<$<PLATFORM_ID:Darwin>:apple.mm>
  $<$<PLATFORM_ID:iOS>:apple.mm>
  $<$<PLATFORM_ID:Windows>:windows.cpp>
  $<$<STREQUAL:${CMAKE_SYSTEM_NAME},WASI>:wasm.cpp>
  )

install(TARGETS silog EXPORT silog-targets FILE_SET HEADERS)
install(EXPORT silog-targets DESTINATION cmake/silog)
install(FILES silog-config.cmake DESTINATION cmake/silog)

###########################################################################
# Proof-of-concept, should be a nice way of understanding how to user this
# library
###########################################################################

if(ANDROID)
  add_library(silog-poc SHARED)
else()
  add_executable(silog-poc)
endif()
target_link_libraries(silog-poc PUBLIC silog)
target_sources(silog-poc PRIVATE poc.cpp)
