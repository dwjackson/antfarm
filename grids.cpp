#include "grids.hpp"

Grids::Grid::Grid(int height, int width)
{
  m_height = height;
  m_width = width;
  
  m_cells = new Colour*[height];
  for (int i = 0; i < height; i++) {
    m_cells[i] = new Colour[width];
    for (int j = 0; j < width; j++) {
      m_cells[i][j] = Colour::WHITE;
    }
  }
}

Grids::Grid::~Grid()
{
  for (int i = 0; i < m_height; i++) {
    delete[] m_cells[i];
  }
  delete[] m_cells;
}

int Grids::Grid::height() const
{
  return m_height;
}

int Grids::Grid::width() const
{
  return m_width;
}

Grids::Colour Grids::Grid::cell(int row, int col) const
{
  return m_cells[row][col];
}

void Grids::Grid::invert_cell(int row, int col)
{
  switch (m_cells[row][col]) {
    case Colour::WHITE:
      m_cells[row][col] = Colour::BLACK;
      break;
    case Colour::BLACK:
      m_cells[row][col] = Colour::WHITE;
      break;
  }  
}
