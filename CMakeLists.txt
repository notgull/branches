# required stuff
cmake_minimum_required(VERSION 2.8.9)
project(branches)
set(CMAKE_BUILD_TYPE Release)

# set compiler flags
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c99 -Iinclude")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

# set version information
set(br_VERSION "2")
set(br_REVISION "3")
set(br_MINOR_REVISION "0")

# get sources
file(GLOB SOURCES "src/*.c")

# do configuration
configure_file (
  "include/branches_config.h.in"
  "include/branches_config.h"
  )

# compile sources
add_executable(branches ${SOURCES})
