/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "grids.hpp"
#include "geometry.hpp"

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

  // Where possible, copy the old grid onto the new one, centered
  auto resizer = Resizer(m_height, m_width, height, width);
  for (int i = 0; i < m_height; i++) {
    for (int j = 0; j < m_width; j++) {
      if (i >= 0 && i < height && j >= 0 && j < width) {
        auto dest = resizer.dest(i, j);
        auto src = resizer.src(i, j);
        cells[dest.y()][dest.x()] = m_cells[src.y()][src.x()];
      }
    }
  }

  // Destroy the old grid
  for (int i = 0; i < m_height; i++) {
    delete m_cells[i];
  }
  delete[] m_cells;
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

Grids::Resizer::Resizer(int height_prev, int width_prev, int height, int width)
{
  m_dest_row_offset = (height - height_prev) / 2;
  m_src_row_offset = 0;
  m_is_offset_negative = false;
  if (m_dest_row_offset < 0) {
    m_src_row_offset = m_dest_row_offset * -1;
    m_dest_row_offset = 0;
    m_is_offset_negative = true;
  }
  m_dest_col_offset = (width - width_prev) / 2;
  m_src_col_offset = 0;
  if (m_dest_col_offset < 0) {
    m_src_col_offset = m_dest_col_offset * -1;
    m_dest_col_offset = 0;
    m_is_offset_negative = true;
  }
}

Geometry::Point Grids::Resizer::src(int row, int col) const
{
  return Geometry::Point(m_src_col_offset + col, m_src_row_offset + row);  
}

Geometry::Point Grids::Resizer::dest(int row, int col) const
{
  return Geometry::Point(m_dest_col_offset + col, m_dest_row_offset + row);  
}

Geometry::Point Grids::Resizer::move(int row, int col) const
{
  auto col_offset = m_dest_col_offset;
  auto row_offset = m_dest_row_offset;
  if (m_is_offset_negative) {
    col_offset = m_src_col_offset * -1;
    row_offset = m_src_row_offset * -1;
  }
  return Geometry::Point(col + col_offset, row + row_offset);
}
