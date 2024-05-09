cmake_minimum_required(VERSION 3.10)

project(AntFarm)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(antfarm antfarm.cpp ants.cpp drawing.cpp grids.cpp)
target_compile_options(antfarm PRIVATE -Wall -Wextra)

find_library(raylib raylib PATHS /usr/lib)
if (raylib)
	target_link_libraries(antfarm ${raylib})
else()
	message(FATAL_ERROR "Raylib not found")
endif()

find_package(Catch2 3 REQUIRED)
add_executable(grids_test grids_test.cpp grids.cpp)
target_link_libraries(grids_test PRIVATE Catch2::Catch2WithMain)
