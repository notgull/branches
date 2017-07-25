# This file is part of Branches.
# 
# Branches is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Branches is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Branches.  If not, see <http://www.gnu.org/licenses/>.

# required stuff
cmake_minimum_required(VERSION 2.8.9)
project(branches)
set(CMAKE_BUILD_TYPE Release)

set(CWS_DEFAULT OFF)

if (MINGW OR MSYS)
  set (CWS_DEFAULT ON)
endif (MINGW OR MSYS)

option(COMPILE_WITH_STATIC "Compile with the -static option" ${CWS_DEFAULT})
option(COMPILE_SERVER "Compile the server edition of branches" OFF)

set(COMPILE_FLAGS "-Iinclude -pthread -Wsizeof-array-argument")
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
set(br_REVISION "3")
set(br_MINOR_REVISION "1")
set(br_CHANGELOG "\"-Added a patch to prevent swearing\\n-Fixed a bug that prevented the Apple Edition from working\\n-Fixed several Windows-specific bugs\\n\"")

# set server information
if (COMPILE_SERVER)
  set(br_SERVER "1")
else (COMPILE_SERVER)
  set(br_SERVER "0")
endif (COMPILE_SERVER)

# get sources
file(GLOB SOURCES "src/*")

if (APPLE)
  set(MACOS_ACTIVE "1")
endif (APPLE)

# do configuration
configure_file (
  "include/branches_config.hpp.in"
  "include/branches_config.hpp"
  )

# compile sources
add_executable(branches ${SOURCES})
set_property(TARGET branches PROPERTY CXX_STANDARD 11)
set_property(TARGET branches PROPERTY CXX_STANDARD_REQUIRED ON)

# get additional libs
if (WIN32 OR MINGW OR MSYS)
  target_link_libraries(branches wsock32 ws2_32) 
endif (WIN32 OR MINGW OR MSYS)



# add installation rules
install(TARGETS branches DESTINATION bin)
