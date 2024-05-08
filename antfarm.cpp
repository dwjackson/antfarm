#include "grids.hpp"
#include "ants.hpp"
#include "drawing.hpp"
#include "raylib.h"

int main(void)
{
  const int screen_width = 800;
  const int screen_height = 480;

  const int side = 10;

  const int height = screen_height / side;
  const int width = screen_width / side;
  
  auto grid = Grids::Grid(height, width);
  auto ant = Ants::Ant(height / 2, width / 2, Ants::Direction::NORTH);
  auto window = Drawing::Window(screen_width, screen_height, "Ant Farm");

  while (!window.should_close()) {
    // Draw the grid
    {
      auto drawing = window.draw();
      drawing->clear_background();
      auto rect = Drawing::Rectangle(side, side);

      for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
          auto cell = grid.cell(i, j);
          auto pos = Drawing::Point(j * side, i * side);
          Color color;
          switch (cell) {
            case Grids::CellColour::CELL_WHITE:
              color = WHITE;
              break;
            case Grids::CellColour::CELL_BLACK:
              color = BLACK;
              break;
          }
          drawing->rectangle(pos, rect, color);
        }
      }
      
      auto pos = Drawing::Point(ant.col() * side, ant.row() * side);
      drawing->rectangle(pos, rect, RED);
    }

    // Update the ant state
    auto row = ant.row();
    auto col = ant.col();
    ant = ant.next(grid);
    grid.invert_cell(row, col);

    window.wait(0.1);
  }

  return 0;
}
