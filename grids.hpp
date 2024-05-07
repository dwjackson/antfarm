#ifndef GRIDS_HPP
#define GRIDS_HPP

namespace Grids {
  enum Colour {
    WHITE,
    BLACK
  };
  
  class Grid {
    private:   
      Colour **m_cells;
      int m_height;
      int m_width;
    public:
      Grid(int height, int width);
      ~Grid();
      int height() const;
      int width() const;
      Colour cell(int row, int col) const;
      void invert_cell(int row, int col);
  }; 
}

#endif /* GRIDS_HPP */
