/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "grids.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Grids;

TEST_CASE("invert a cell", "[grid]")
{
  auto grid = Grid(2, 2);
  REQUIRE(grid.cell(0, 0) == 0);
  grid.set_cell(0, 0, 1);
  REQUIRE(grid.cell(0, 0) == 1);
}

TEST_CASE("out of bounds", "[grid]")
{
  auto grid = Grid(2, 2);
  REQUIRE(grid.is_out_of_bounds(3, 3) == true);
}

TEST_CASE("resize grid from smaller to larger centers the drawings", "[grid]")
{
  auto grid = Grid(2, 2);

  // Set up the "picture"
  grid.set_cell(0, 1, 1);
  grid.set_cell(1, 0, 1);

  grid.resize(6, 8);

  // Ensure that the picture is still "centered"
  REQUIRE(grid.cell(2, 4) == 1);
  REQUIRE(grid.cell(3, 3) == 1);
}

TEST_CASE("resize grid from larger to smaller centers the drawings", "[grid]")
{
  auto grid = Grid(6, 8);

  // Set up the "picture"
  grid.set_cell(2, 4, 1);
  grid.set_cell(3, 3, 1);
  grid.set_cell(1, 0, 1);

  grid.resize(2, 2);

  // Ensure that the picture is still "centered"
  REQUIRE(grid.cell(0, 1) == 1);
  REQUIRE(grid.cell(1, 0) == 1);
}
