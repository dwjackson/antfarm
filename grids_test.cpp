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
  REQUIRE(grid.cell(0, 0) == CellColour::CELL_WHITE);
  grid.invert_cell(0, 0);
  REQUIRE(grid.cell(0, 0) == CellColour::CELL_BLACK);
}

TEST_CASE("out of bounds", "[grid]")
{
  auto grid = Grid(2, 2);
  REQUIRE(grid.is_out_of_bounds(3, 3) == true);
}
