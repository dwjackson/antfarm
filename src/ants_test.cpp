/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "ants.hpp"
#include "grids.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Grids;

TEST_CASE("white square turns clockwise and moves forward", "[ant]")
{
  auto grid = Grids::Grid(5, 5);
  auto ant = Ants::Ant(2, 2, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid, ANT_STANDARD_RULE);

  REQUIRE(test_ant.row() == 2);
  REQUIRE(test_ant.col() == 3);
}

TEST_CASE("black square turns counterclockwise and moves forward", "[ant]")
{
  auto grid = Grids::Grid(5, 5);
  grid.set_cell(2, 2, 1);
  REQUIRE(grid.cell(2, 2) == 1);

  auto ant = Ants::Ant(2, 2, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid, ANT_STANDARD_RULE);

  REQUIRE(test_ant.row() == 2);
  REQUIRE(test_ant.col() == 1);
}

TEST_CASE("moving off the grid", "[ant]")
{
  auto grid = Grids::Grid(2, 2);
  auto ant = Ants::Ant(0, 1, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid, ANT_STANDARD_RULE);

  REQUIRE(test_ant.row() == 0);
  REQUIRE(test_ant.col() == 2);
}
