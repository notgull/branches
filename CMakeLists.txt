# required stuff
cmake_minimum_required(VERSION 2.8.9)
project(branches)
set(CMAKE_BUILD_TYPE Release)

# set compiler flags
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c99 -Iinclude")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

# get sources
file(GLOB SOURCES "src/*.c")

# compile sources
add_executable(branches ${SOURCES})
