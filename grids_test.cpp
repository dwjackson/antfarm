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
