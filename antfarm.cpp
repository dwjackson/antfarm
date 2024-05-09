#include "grids.hpp"
#include "ants.hpp"
#include "drawing.hpp"
#include "raylib.h"
#include <vector>
#include <ranges>

const int side = 10;
const int max_ants = 10;

static void add_ant(std::vector<Ants::Ant> &ants, int x, int y);
static void draw_scene(Drawing::Window &window, const Grids::Grid &grid, const std::vector<Ants::Ant> &ants);

int main(void)
{
  const int screen_width = 1200;
  const int screen_height = 720;

  const int height = screen_height / side;
  const int width = screen_width / side;
  
  auto grid = Grids::Grid(height, width);
  std::vector<Ants::Ant> ants;
  auto window = Drawing::Window(screen_width, screen_height, "Ant Farm");

  bool is_paused = false;
  while (!window.should_close()) {
    draw_scene(window, grid, ants);

    // Add an ant if the user clicks somewhere
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ants.size() < max_ants) {
      add_ant(ants, GetMouseX(), GetMouseY());
    }

    // Pause if the user presses the spacebar
    if (IsKeyPressed(KEY_SPACE)) {
      is_paused = !is_paused;
    }

    // Update the ants state
    if (!is_paused) {
      std::vector<std::vector<Ants::Ant>::size_type> to_remove;
      for (std::vector<Ants::Ant>::size_type i = 0; i < ants.size(); i++) {
        auto ant = &ants[i];
        auto row = ant->row();
        auto col = ant->col();
        grid.invert_cell(row, col);
        auto next_ant = ant->next(grid);
        if (grid.is_out_of_bounds(next_ant.row(), next_ant.col())) {
          to_remove.push_back(i);
        } else {
          ants[i] = ant->next(grid);
        }
      }
      // Remove any ants that left the grid
      for (auto index : to_remove | std::views::reverse) {
        ants.erase(ants.begin() + index);
      }

      window.wait(0.05);
    }
  }

  return 0;
}

static void add_ant(std::vector<Ants::Ant> &ants, int x, int y)
{
  int row = y / side;
  int col = x / side;
  ants.push_back(Ants::Ant(row, col, Ants::Direction::NORTH));
}

static void draw_scene(Drawing::Window &window, const Grids::Grid &grid, const std::vector<Ants::Ant> &ants)
{
  auto drawing = window.draw();
  drawing->clear_background();
  auto rect = Drawing::Rectangle(side, side);

  for (int i = 0; i < grid.height(); i++) {
    for (int j = 0; j < grid.width(); j++) {
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

  for (auto ant : ants) {
    auto pos = Drawing::Point(ant.col() * side, ant.row() * side);
    drawing->rectangle(pos, rect, RED);
  }
}
