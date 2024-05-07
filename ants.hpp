#ifndef ANTS_HPP
#define ANTS_HPP

#include "grids.hpp"

namespace Ants {
  enum Direction {
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
      Ant next(const Grids::Grid &grid) const;
  };
}

#endif /* ANTS_HPP */
