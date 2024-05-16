/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "app_state.hpp"
#include "palette.hpp"
extern "C" {
  #include "raylib.h"
}
#include "ants.hpp"
#include "ants.hpp"
#include <vector>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("cycle a cell where rules are smaller than palette", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK, PURPLE };
  auto palette = Palette::Palette(colours);
  auto state = AppState(100, 50, "LR", palette);

  state.cycle_colour(0, 0); // 0 -> 1
  state.cycle_colour(0, 0); // 1 -> 0
  state.cycle_colour(0, 0); // 0 -> 1

  auto index = state.grid().cell(0, 0);
  REQUIRE(index == 1);
}

TEST_CASE("cycle a cell where rules are same size as palette", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK, PURPLE };
  auto palette = Palette::Palette(colours);
  auto state = AppState(100, 50, "LRL", palette);

  state.cycle_colour(0, 0); // 0 -> 1
  state.cycle_colour(0, 0); // 1 -> 2

  auto index = state.grid().cell(0, 0);
  REQUIRE(index == 2);
}

TEST_CASE("count iterations", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK };
  auto palette = Palette::Palette(colours);
  auto state = AppState(100, 50, "RL", palette);

  REQUIRE(state.iterations() == 0);
  state.add_ant(Ants::Ant(10, 10, Ants::Direction::NORTH));
  state.tick();
  state.tick();
  REQUIRE(state.iterations() == 2);
}

TEST_CASE("tick", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK };
  auto palette = Palette::Palette(colours);
  auto state = AppState(100, 50, "RL", palette);
  state.add_ant(Ants::Ant(5, 5, Ants::Direction::NORTH));
  state.tick();
  REQUIRE(state.ants()[0].row() == 5);  
  REQUIRE(state.ants()[0].col() == 6);  
}

TEST_CASE("iteration count does not increase if there are no ants", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK };
  auto palette = Palette::Palette(colours);
  auto state = AppState(100, 50, "RL", palette);

  REQUIRE(state.iterations() == 0);
  state.tick();
  REQUIRE(state.iterations() == 0);
}

TEST_CASE("resizing the grid to be larger moves the ants", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK };
  auto palette = Palette::Palette(colours);
  auto state = AppState(2, 2, "RL", palette);
  state.add_ant(Ants::Ant(1, 1, Ants::Direction::NORTH));

  state.resize_grid(6, 8);

  const Ants::Ant *ant = &state.ants()[0];
  REQUIRE(ant->row() == 3);
  REQUIRE(ant->col() == 4);
}

TEST_CASE("resizing the grid to be smaller moves the ants", "[app_state]")
{
  std::vector<Color> colours =  { RAYWHITE, BLACK };
  auto palette = Palette::Palette(colours);
  auto state = AppState(6, 8, "RL", palette);
  state.add_ant(Ants::Ant(3, 4, Ants::Direction::NORTH));

  state.resize_grid(2, 2);

  const Ants::Ant *ant = &state.ants()[0];
  REQUIRE(ant->row() == 1);
  REQUIRE(ant->col() == 1);
}
