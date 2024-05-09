#include "ants.hpp"
#include "grids.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Grids;

TEST_CASE("", "[ant]")
{
  auto grid = Grids::Grid(5, 5);
  auto ant = Ants::Ant(2, 2, Ants::Direction::NORTH);
  auto test_ant = ant.next(grid);

  REQUIRE(test_ant.row() == 2);
  REQUIRE(test_ant.col() == 3);
}
