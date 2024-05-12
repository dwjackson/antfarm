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
#include <string>

RulesError rules_validate(const char *rules, const Palette::Palette &palette)
{
  size_t len = strlen(rules);
  if ((size_t) palette.size() < len) {
    return RulesError::TOO_MANY_RULES;
  }
  for (size_t i = 0; i < len; i++) {
    if (rules[i] != 'L' && rules[i] != 'R') {
      return RulesError::INVALID_CHARACTER;
    }
  }
  return RulesError::NONE;
}

std::string rules_error_explain(RulesError error)
{
  std::string explanation;
  switch (error) {
    case RulesError::NONE:
      explanation = "";
      break;
    case RulesError::TOO_MANY_RULES:
      explanation = "Too many rules for the palette size";
      break;
    case RulesError::INVALID_CHARACTER:
      explanation = "Invalid character in rule";
      break;
  }  
  return explanation;
}
