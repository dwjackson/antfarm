# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Copyright (c) 2024 David Jackson

find_path(Raylib_INCLUDE_DIR raylib.h
  PATHS
  /usr/include
  /include
)

find_library(Raylib_LIBRARIES
  NAMES raylib
  PATHS
    /usr/lib
    /lib
)

file(READ "${Raylib_INCLUDE_DIR}/raylib.h" header_contents)
string(REGEX MATCH "#define RAYLIB_VERSION \"([0-9]+\.[0-9]+)\"" _ "${header_contents}")
set(Raylib_VERSOIN ${CMAKE_MATCH_1})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Raylib
  REQUIRED_VARS Raylib_LIBRARIES Raylib_INCLUDE_DIR
  VERSION_VAR Raylib_VERSION
  FAIL_MESSAGE "Could not find Raylib"
)
