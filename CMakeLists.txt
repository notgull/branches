# required stuff
cmake_minimum_required(VERSION 2.8.9)
project(branches)
set(CMAKE_BUILD_TYPE Release)

# set compiler flags
set(GCC_COVERAGE_COMPILE_FLAGS "-Iinclude")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

# set version information
set(br_VERSION "\"BETA\"")
set(br_REVISION "1")
set(br_MINOR_REVISION "0")
set(br_CHANGELOG "\"-Converted the entire codebase to C++\\n-Overhauled the entire program structure\\n-Probably added a ton of bugs\\n-Read function is broken again\\n\"")

# get sources
file(GLOB SOURCES "src/*")

# do configuration
configure_file (
  "include/branches_config.hpp.in"
  "include/branches_config.hpp"
  )

# compile sources
add_executable(branches ${SOURCES})
set_property(TARGET branches PROPERTY CXX_STANDARD 11)
set_property(TARGET branches PROPERTY CXX_STANDARD_REQUIRED ON)

# add installation rules
install(TARGETS branches DESTINATION bin)
