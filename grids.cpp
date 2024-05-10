/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "grids.hpp"

static int **create_cells(int height, int width);

Grids::Grid::Grid(int height, int width)
{
  m_height = height;
  m_width = width;  
  m_cells = create_cells(height, width);
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

int Grids::Grid::cell(int row, int col) const
{
  return m_cells[row][col];
}

void Grids::Grid::set_cell(int row, int col, int value)
{
  m_cells[row][col] = value;
}

bool Grids::Grid::is_out_of_bounds(int row, int col) const
{
  return row < 0 || row >= m_height || col < 0 || col >= m_width;
}

void Grids::Grid::reset()
{
  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {
      m_cells[i][j] = 0;
    }
  }
}

void Grids::Grid::resize(int height, int width)
{
  auto cells = create_cells(height, width);

  // Where possible, copy the old grid onto the new one
  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {
      if (i >= 0 && i < height && j >= 0 && j < width) {
        cells[i][j] = m_cells[i][j];
      }
    }
  }

  // Destroy the old grid
  for (int i = 0; i < m_height; i++) {
    delete m_cells[i];
  }
  delete m_cells;
  m_cells = nullptr;
  
  // Update the grid
  m_height = height;
  m_width = width;
  m_cells = cells;
}

static int **create_cells(int height, int width)
{
  int **cells = new int*[height]; 
  for (int i = 0; i < height; i++) {
    cells[i] = new int[width];
    for (int j = 0; j < width; j++) {
      cells[i][j] = 0;
    }
  }
  return cells;
}
