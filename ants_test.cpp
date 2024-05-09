#include "ants.hpp"
#include "grids.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Grids;

TEST_CASE("white square turns clockwise and moves forward", "[ant]")
{
  auto grid = Grids::Grid(5, 5);
  auto ant = Ants::Ant(2, 2, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid);

  REQUIRE(test_ant.row() == 2);
  REQUIRE(test_ant.col() == 3);
}

TEST_CASE("black square turns counterclockwise and moves forward", "[ant]")
{
  auto grid = Grids::Grid(5, 5);
  grid.invert_cell(2, 2);
  REQUIRE(grid.cell(2, 2) == Grids::CellColour::CELL_BLACK);

  auto ant = Ants::Ant(2, 2, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid);

  REQUIRE(test_ant.row() == 2);
  REQUIRE(test_ant.col() == 1);
}

TEST_CASE("moving off the grid stays causes ant to be stationary", "[ant]")
{
  auto grid = Grids::Grid(2, 2);
  auto ant = Ants::Ant(0, 1, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid);

  REQUIRE(test_ant.row() == 0);
  REQUIRE(test_ant.col() == 1);
}
