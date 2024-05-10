/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

extern "C" {
  #include "raylib.h"
}
#include "palette.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("next colour index", "[palette]")
{
  Color colours[] = { BLACK, WHITE, DARKPURPLE, PURPLE, VIOLET };
  auto colours_size = sizeof(colours) / sizeof(colours[0]);
  REQUIRE(colours_size == 5);

  auto palette = Palette(colours, colours_size);

  // Example rule is "LLRR"
  const int limit = 4;
  REQUIRE(palette.next(0, limit) == 1);
  REQUIRE(palette.next(1, limit) == 2);
  REQUIRE(palette.next(2, limit) == 3);
  REQUIRE(palette.next(3, limit) == 0);
}
