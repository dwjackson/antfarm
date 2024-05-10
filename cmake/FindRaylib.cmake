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

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Raylib
  REQUIRED_VARS Raylib_LIBRARIES Raylib_INCLUDE_DIR
  FAIL_MESSAGE "Could not find Raylib"
)
