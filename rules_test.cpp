/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "palette.hpp"
#include "rules.hpp"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("too many rules for the number of colours", "[rules]")
{
  Color colours[] = { RAYWHITE, BLACK, PURPLE };
  auto colours_size = 3;
  auto palette = Palette(colours, colours_size);

  REQUIRE(rules_validate("LLRR", palette) == false);
}

TEST_CASE("only L and R are allowed characters", "[rules]")
{
  Color colours[] = { RAYWHITE, BLACK, PURPLE };
  auto colours_size = 3;
  auto palette = Palette(colours, colours_size);

  REQUIRE(rules_validate("LX9", palette) == false);
}
