#include "grids.hpp"

Grids::Grid::Grid(int height, int width)
{
  m_height = height;
  m_width = width;
  
  m_cells = new CellColour*[height];
  for (int i = 0; i < height; i++) {
    m_cells[i] = new CellColour[width];
    for (int j = 0; j < width; j++) {
      m_cells[i][j] = CellColour::CELL_WHITE;
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

Grids::CellColour Grids::Grid::cell(int row, int col) const
{
  return m_cells[row][col];
}

void Grids::Grid::invert_cell(int row, int col)
{
  switch (m_cells[row][col]) {
    case CellColour::CELL_WHITE:
      m_cells[row][col] = CellColour::CELL_BLACK;
      break;
    case CellColour::CELL_BLACK:
      m_cells[row][col] = CellColour::CELL_WHITE;
      break;
  }  
}
