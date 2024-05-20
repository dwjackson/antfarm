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
#include <vector>
#include <catch2/catch_test_macros.hpp>

#define WHITE Palette::Colour(255, 255, 255)
#define BLACK Palette::Colour(0, 0, 0)
#define PURPLE Palette::Colour(255, 0, 255)

TEST_CASE("too many rules for the number of colours", "[rules]")
{
  std::vector<Palette::Colour> colours = { WHITE, BLACK, PURPLE };
  auto palette = Palette::Palette(colours);

  auto result = rules_validate("LLRR", palette);
  REQUIRE(result == RulesError::TOO_MANY_RULES);
  std::string explanation = rules_error_explain(result);
  REQUIRE(explanation == "Too many rules for the palette size");
}

TEST_CASE("only L and R are allowed characters", "[rules]")
{
  std::vector<Palette::Colour> colours = { WHITE, BLACK, PURPLE };
  auto palette = Palette::Palette(colours);

  auto result = rules_validate("LX9", palette);
  REQUIRE(result == RulesError::INVALID_CHARACTER);
  std::string explanation = rules_error_explain(result);
  REQUIRE(explanation == "Invalid character in rule");
}

TEST_CASE("valid rules", "[rules]")
{
  std::vector<Palette::Colour> colours = { WHITE, BLACK };
  auto palette = Palette::Palette(colours);

  REQUIRE(rules_validate("RL", palette) == RulesError::NONE);
}

TEST_CASE("valid rules with extra colours", "[rules]")
{
  std::vector<Palette::Colour> colours = { WHITE, BLACK, PURPLE };
  auto palette = Palette::Palette(colours);

  REQUIRE(rules_validate("RL", palette) == RulesError::NONE);
}
