/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef RULES_HPP
#define RULES_HPP

#include "palette.hpp"

enum class RulesError {
  NONE,
  TOO_MANY_RULES,
  INVALID_CHARACTER
 };

RulesError rules_validate(const char *rules, const Palette::Palette &palette);
std::string rules_error_explain(RulesError error);

#endif /* RULES_HPP */
