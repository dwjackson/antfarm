#include "grids.hpp"
#include "ants.hpp"
#include <iostream>

int main(void)
{
  const int height = 10;
  const int width = 40;
  const int iterations = 10;
  
  auto grid = Grids::Grid(height, width);
  auto ant = Ants::Ant(height / 2, width / 2, Ants::Direction::NORTH);

  // DEBUG
  std::cout << "Height: " << grid.height() << std::endl;
  std::cout << "Width: " << grid.width() << std::endl;
  for (int i = 0; i < iterations; i++) {
    for (int j = 0; j < grid.height(); j++) {
      for (int k = 0; k < grid.width(); k++) {
        auto cell = grid.cell(j, k);
        char ch;
        switch (cell) {
          case Grids::Colour::WHITE:
            ch = '.';
            break;
          case Grids::Colour::BLACK:
            ch = '#';
            break;
        }
        if (ant.row() == j && ant.col() == k) {
          ch = 'A';
        }
        std::cout << ch;
      }
      std::cout << std::endl;
    }

    auto row = ant.row();
    auto col = ant.col();
    ant = ant.next(grid);
    grid.invert_cell(row, col);
  }
  return 0;
}
