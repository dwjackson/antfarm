/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef ANTS_HPP
#define ANTS_HPP

#include "grids.hpp"

#define ANT_STANDARD_RULE "RL"

namespace Ants {

  enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
  };

  class Ant {
    private:
      Direction m_dirn;
      int m_row;
      int m_col;
    public:
      Ant(int row, int col, Direction dirn);
      int row() const;
      int col() const;
      Ant next(const Grids::Grid &grid, const char *rules) const;
      void move(int row, int col);
  };

}

#endif /* ANTS_HPP */
