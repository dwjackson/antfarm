# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Copyright (c) 2024 David Jackson

cmake_minimum_required(VERSION 3.10)

project(AntFarm)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(antfarm antfarm.cpp ants.cpp drawing.cpp grids.cpp app_state.cpp timer.cpp palette.cpp rules.cpp geometry.cpp)
target_compile_options(antfarm PRIVATE -Wall -Wextra)

find_package(Raylib 5.0 REQUIRED)
include_directories(${Raylib_INCLUDE_DIRS})
target_link_libraries(antfarm ${Raylib_LIBRARIES})

# Tests

find_package(Catch2 3 REQUIRED)

add_executable(grids_test grids_test.cpp grids.cpp palette.cpp)
target_link_libraries(grids_test PRIVATE Catch2::Catch2WithMain)

add_executable(ants_test ants_test.cpp ants.cpp grids.cpp palette.cpp)
target_link_libraries(ants_test PRIVATE Catch2::Catch2WithMain)

add_executable(app_state_test app_state_test.cpp app_state.cpp ants.cpp grids.cpp palette.cpp)
target_link_libraries(app_state_test PRIVATE Catch2::Catch2WithMain)

add_executable(rules_test rules_test.cpp palette.cpp rules.cpp)
target_link_libraries(rules_test PRIVATE Catch2::Catch2WithMain)

add_executable(palette_test palette_test.cpp palette.cpp)
target_link_libraries(palette_test PRIVATE Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(grids_test)
catch_discover_tests(ants_test)
catch_discover_tests(app_state_test)
catch_discover_tests(rules_test)
catch_discover_tests(palette_test)
