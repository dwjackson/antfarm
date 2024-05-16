/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef GRIDS_HPP
#define GRIDS_HPP

#include "geometry.hpp"

namespace Grids {
  
  class Grid {
    private:   
      int **m_cells;
      int m_height;
      int m_width;
    public:
      Grid(int height, int width);
      ~Grid();
      int height() const;
      int width() const;
      int cell(int row, int col) const;
      void set_cell(int row, int col, int value);
      bool is_out_of_bounds(int row, int col) const;
      void reset();
      void resize(int height, int width);
  }; 

  class Resizer {
    private:
      int m_dest_row_offset;
      int m_src_row_offset;
      int m_dest_col_offset;
      int m_src_col_offset;
      bool m_is_offset_negative;
    public:
      Resizer(const Resizer&) = delete;
      Resizer& operator=(const Resizer&) = delete;
      Resizer(int height_prev, int width_prev, int height, int width);
      Geometry::Point src(int row, int col) const;
      Geometry::Point dest(int row, int col) const;
      Geometry::Point move(int row, int col) const;
  };
}

#endif /* GRIDS_HPP */
