/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "scene.hpp"
#include "drawing.hpp"
#include "grids.hpp"
#include "app_state.hpp"
#include <format>

#define COLOUR_WHITE Palette::Colour(245, 245, 245)
#define COLOUR_RED Palette::Colour(255, 0, 0)
#define COLOUR_HUD Palette::Colour(200, 200, 200)
#define COLOUR_TEXT Palette::Colour(80, 80, 80)

static Geometry::Rectangle rectangle(int width, int height);
static Geometry::Point point(int x, int y);

Scene::Scene(int side, int font_size) : m_side(side), m_font_size(font_size)
{
}

void Scene::draw(Drawing::Window &window, const AppState &state)
{
  auto drawing = window.draw();
  drawing->clear_background();
  auto rect = rectangle(m_side, m_side);

  /* Draw the grid squares */
  for (int i = 0; i < state.grid().height(); i++) {
    for (int j = 0; j < state.grid().width(); j++) {
      auto colour_index = state.grid().cell(i, j);
      auto pos = point(j * m_side, i * m_side);
      auto colour = state.colour(colour_index);
      drawing->rectangle(pos, rect, colour);
    }
  }

  /* Draw the ants */
  for (auto ant : state.ants()) {
    auto pos = point(ant.col() * m_side, ant.row() * m_side);
    drawing->rectangle(pos, rect, COLOUR_RED);
  }

  if (state.is_all_hidden()) {
    // Do not draw any of the "HUD" elements
    return;
  }

  /* Draw the HUD */
  int height = window.screen_height();
  int width = window.screen_width();
  auto hud_pos = point(0, height - m_font_size);
  auto hud_rectangle = rectangle(width, m_font_size);
  drawing->rectangle(hud_pos, hud_rectangle, COLOUR_HUD);
  auto hud = state.hud();
  drawing->text(hud, hud_pos, m_font_size, COLOUR_TEXT);

  // Draw the crosshairs
  if (state.is_crosshairs_visible()) {
    const int dim = 50;
    auto dims = rectangle(dim, dim);
    auto center = dims.center_within(window.screen_width(), window.screen_height());

    // Horizontal Line
    drawing->line(point(center.x() - dim / 2, center.y()), point(center.x() + dim / 2, center.y()), COLOUR_HUD);

    // Vertical line
    drawing->line(point(center.x(), center.y() - dim / 2), point(center.x(), center.y() + dim / 2), COLOUR_HUD);
  }

  // Draw the grid overlay
  if (state.is_grid_visible()) {
    for (int i = m_side; i < hud_pos.y(); i += m_side) {
      drawing->line(point(0, i), point(width - 1, i), COLOUR_HUD);
    }
    for (int i = m_side; i < width; i += m_side) {
      drawing->line(point(i, 0), point(i, hud_pos.y()), COLOUR_HUD);
    }
  }

  // Draw iterations counter
  if (state.show_iterations())
  {
    auto iterations_pos = point(0, 0);
    auto iterations = std::format("Iterations: {}", state.iterations());
    const char *str = iterations.c_str();
    int width = window.measure_text(str, m_font_size);
    auto rect = rectangle(width, m_font_size);
    drawing->rectangle(iterations_pos, rect, COLOUR_WHITE);
    drawing->text(str, iterations_pos, m_font_size, COLOUR_TEXT);
  }

  // Draw the frame rate
  if (state.is_frame_rate_visible()) {
    auto fps = std::format("FPS: {}", window.fps());
    const char *str = fps.c_str();
    int fps_width = window.measure_text(str, m_font_size);
    auto fps_pos = point(window.screen_width() - fps_width, 0);
    auto rect = rectangle(width, m_font_size);
    drawing->rectangle(fps_pos, rect, COLOUR_WHITE);
    drawing->text(str, fps_pos, m_font_size, COLOUR_TEXT);
  }
}

static Geometry::Rectangle rectangle(int width, int height)
{
  return Geometry::Rectangle(width, height);
}

static Geometry::Point point(int x, int y)
{
  return Geometry::Point(x, y);
}
