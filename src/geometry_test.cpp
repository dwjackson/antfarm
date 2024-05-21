
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "geometry.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace Geometry;

TEST_CASE("centering a rectangle", "[geomtetry]")
{
  auto rect = Rectangle(40, 30);
  auto center = rect.center_within(100, 100);
  REQUIRE(center.x() == 30);
  REQUIRE(center.y() == 35);
}

