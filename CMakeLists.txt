# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Copyright (c) 2024 David Jackson

cmake_minimum_required(VERSION 3.10)

project(AntFarm)

set(exe_name "antfarm")

enable_testing()

add_subdirectory(src)
