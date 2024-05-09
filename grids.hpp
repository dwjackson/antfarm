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

namespace Grids {
  enum CellColour {
    CELL_WHITE,
    CELL_BLACK
  };
  
  class Grid {
    private:   
      CellColour **m_cells;
      int m_height;
      int m_width;
    public:
      Grid(int height, int width);
      ~Grid();
      int height() const;
      int width() const;
      CellColour cell(int row, int col) const;
      void invert_cell(int row, int col);
      bool is_out_of_bounds(int row, int col);
  }; 
}

#endif /* GRIDS_HPP */
