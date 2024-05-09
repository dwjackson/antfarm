#include "ants.hpp"

namespace Ants {

  Direction turn_clockwise(Direction dirn)
  {
    switch (dirn) {
      case Direction::NORTH:
        return Direction::EAST;
      case Direction::EAST:
        return Direction::SOUTH;
      case Direction::SOUTH:
        return Direction::WEST;
      case Direction::WEST:
        return Direction::NORTH;
    }
  }

  Direction turn_counterclockwise(Direction dirn)
  {
    switch (dirn) {
      case Direction::NORTH:
        return Direction::WEST;
      case Direction::EAST:
        return Direction::NORTH;
      case Direction::SOUTH:
        return Direction::EAST;
      case Direction::WEST:
        return Direction::SOUTH;
    }
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

  Ant Ant::next(const Grids::Grid &grid) const
  {
    int row, col;
    Direction dirn;

    auto cell = grid.cell(m_row, m_col);    
    switch (cell) {
      case Grids::CellColour::CELL_WHITE:
        dirn = turn_clockwise(m_dirn);
        break;
      case Grids::CellColour::CELL_BLACK:
        dirn = turn_counterclockwise(m_dirn);
        break;
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
}

