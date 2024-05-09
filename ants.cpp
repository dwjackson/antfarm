#include "ants.hpp"

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

