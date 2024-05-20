/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "palette.hpp"
#include <vector>
#include <catch2/catch_test_macros.hpp>

#define BLACK Palette::Colour(0, 0, 0)
#define WHITE Palette::Colour(255, 255, 255)
#define DARKPURPLE Palette::Colour(112, 31, 126)
#define PURPLE Palette::Colour(200, 122, 255)
#define VIOLET Palette::Colour(135, 60, 190)

TEST_CASE("Color from hex code", "[drawing]")
{
  int hex = 0x5d2e8c;
  Palette::Colour color = Palette::color_from_hex(hex);

  REQUIRE(color.m_red == 93);
  REQUIRE(color.m_green == 46);
  REQUIRE(color.m_blue == 140);
}

TEST_CASE("next colour index", "[palette]")
{
  std::vector<Palette::Colour> colours = { BLACK, WHITE, DARKPURPLE, PURPLE, VIOLET };

  auto palette = Palette::Palette(colours);

  // Example rule is "LLRR"
  const int limit = 4;
  REQUIRE(palette.next(0, limit) == 1);
  REQUIRE(palette.next(1, limit) == 2);
  REQUIRE(palette.next(2, limit) == 3);
  REQUIRE(palette.next(3, limit) == 0);
}

TEST_CASE("parse a color", "[palette]")
{
  auto color = Palette::parse_color("purple 0x5d2e8c");
  REQUIRE(color.m_red == 93);
  REQUIRE(color.m_green == 46);
  REQUIRE(color.m_blue == 140);
}
