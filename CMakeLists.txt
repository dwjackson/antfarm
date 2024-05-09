# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Copyright (c) 2024 David Jackson

cmake_minimum_required(VERSION 3.10)

project(AntFarm)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(antfarm antfarm.cpp ants.cpp drawing.cpp grids.cpp app_state.cpp)
target_compile_options(antfarm PRIVATE -Wall -Wextra)

find_library(raylib raylib PATHS /usr/lib)
if (raylib)
	target_link_libraries(antfarm ${raylib})
else()
	message(FATAL_ERROR "Raylib not found")
endif()

# Tests

find_package(Catch2 3 REQUIRED)

add_executable(grids_test grids_test.cpp grids.cpp)
target_link_libraries(grids_test PRIVATE Catch2::Catch2WithMain)

add_executable(ants_test ants_test.cpp ants.cpp grids.cpp)
target_link_libraries(ants_test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(grids_test)
catch_discover_tests(ants_test)
