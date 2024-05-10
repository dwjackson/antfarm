/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "rules.hpp"
#include "palette.hpp"
#include <cstring>
#include <cstdlib>

bool rules_validate(const char *rules, const Palette &palette)
{
  size_t len = strlen(rules);
  if ((size_t) palette.size() <= len) {
    return false;
  }
  for (size_t i = 0; i < len; i++) {
    if (rules[i] != 'L' && rules[i] != 'R') {
      return false;
    }
  }
  return true;
}
