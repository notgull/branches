# required stuff
cmake_minimum_required(VERSION 2.8.9)
project(branches)
set(CMAKE_BUILD_TYPE Release)

set(CWS_DEFAULT OFF)

if (MINGW)
  set (CMS_DEFAULT ON)
endif (MINGW)

option(COMPILE_WITH_STATIC "Compile with the -static option" ${CMS_DEFAULT})
option(COMPILE_SERVER "Compile the server edition of branches" OFF)

set(COMPILE_FLAGS "-Iinclude")
set(LINK_FLAGS " ")

if (COMPILE_WITH_STATIC)
  set(COMPILE_FLAGS "${COMPILE_FLAGS} -static")
  message(STATUS "Compiling with static libs...")
endif (COMPILE_WITH_STATIC)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

# set version information
set(br_VERSION "\"BETA\"")
set(br_REVISION "1")
set(br_MINOR_REVISION "2")
set(br_CHANGELOG "\"-Built first trial of the server edition\\n\"")

# set server information
if (COMPILE_SERVER)
  set(br_SERVER "1")
else (COMPILE_SERVER)
  set(br_SERVER "0")
endif (COMPILE_SERVER)

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
