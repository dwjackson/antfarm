/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "ants.hpp"
#include <cstdlib>

namespace Ants {

  Direction turn_clockwise(Direction dirn)
  {
    Direction next;
    switch (dirn) {
      case Direction::NORTH:
        next = Direction::EAST;
        break;
      case Direction::EAST:
        next = Direction::SOUTH;
        break;
      case Direction::SOUTH:
        next = Direction::WEST;
        break;
      case Direction::WEST:
        next = Direction::NORTH;
        break;
    }
    return next;
  }

  Direction turn_counterclockwise(Direction dirn)
  {
    Direction next;
    switch (dirn) {
      case Direction::NORTH:
        next = Direction::WEST;
        break;
      case Direction::EAST:
        next = Direction::NORTH;
        break;
      case Direction::SOUTH:
        next =Direction::EAST;
        break;
      case Direction::WEST:
        next = Direction::SOUTH;
        break;
    }
    return next;
  }  
  
  Ant::Ant(int row, int col, Direction dirn)
  {
    m_row = row;
    m_col = col;
    m_dirn = dirn;
  }

  int Ant::row() const
  {
    return m_row;
  }

  int Ant::col() const
  {
    return m_col;
  }

  Ant Ant::next(const Grids::Grid &grid, const char *rules) const
  {
    int row, col;
    Direction dirn;

    auto index = grid.cell(m_row, m_col);    
    char ch = rules[index];

    switch (ch) {
      case 'R':
        dirn = turn_clockwise(m_dirn);
        break;
      case 'L':
        dirn = turn_counterclockwise(m_dirn);
        break;
      default:
        std::abort();
    }

    row = m_row;
    col = m_col;
    switch (dirn) {
      case Direction::NORTH:
        row--;
        break;
      case Direction::EAST:
        col++;
        break;
      case Direction::SOUTH:
        row++;
        break;
      case Direction::WEST:
        col--;
        break;
    }
    
    return Ant(row, col, dirn);
  }

  void Ant::move(int row, int col)
  {
    m_row = row;
    m_col = col;
  }

}

