/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

extern "C" {
  #include "raylib.h"
}

#include "drawing.hpp"
#include "geometry.hpp"
#include <memory>

static Color color(const Palette::Colour *colour);

namespace Drawing {

  Window::Window(int width, int height, const char *title) : m_screen_width(width), m_screen_height(height)
  {
    InitWindow(width, height, title);
    int monitor = GetCurrentMonitor();
    m_monitor_height = GetMonitorHeight(monitor);
    m_monitor_width = GetMonitorWidth(monitor);
    SetTargetFPS(60);
  }

  Window::~Window()
  {
    CloseWindow();
  }

  std::unique_ptr<Context> Window::draw()
  {
    return std::unique_ptr<Context>(new Context());
  }

  bool Window::should_close()
  {
    return WindowShouldClose();
  }

  Geometry::Point Window::center(const Geometry::Rectangle &rect)
  {
    int x = m_screen_width / 2 - rect.width() / 2;
    int y = m_screen_height / 2 - rect.height() / 2;
    return Geometry::Point(x, y);
  }

  int Window::monitor_height() const
  {
    return m_monitor_height;
  }

  int Window::monitor_width() const
  {
    return m_monitor_width;
  }

  int Window::screen_width() const
  {
    return GetRenderWidth();
  }

  int Window::screen_height() const
  {
    return GetRenderHeight();
  }

  int Window::measure_text(const char *text, int font_size) const
  {
    return MeasureText(text, font_size);
  }

  int Window::fps() const
  {
    return GetFPS();
  }

  bool Window::is_full_screen() const
  {
    return IsWindowFullscreen();
  }

  void Window::toggle_full_screen()
  {
    ToggleFullscreen();
  }

  void Window::set_size(int width, int height)
  {
    SetWindowSize(width, height);
  }

  Context::Context()
  {
    BeginDrawing();
  }

  Context::~Context()
  {
    EndDrawing();
  }

  void Context::clear_background()
  {
    ClearBackground(RAYWHITE);
  }

  void Context::rectangle(const Geometry::Point &pos, const Geometry::Rectangle &rect, Palette::Colour colour)
  {
    DrawRectangle(pos.x(), pos.y(), rect.width(), rect.height(), color(&colour));
  }

  void Context::text(const char *text, Geometry::Point &pos, int font_size, Palette::Colour colour)
  {
    DrawText(text, pos.x(), pos.y(), font_size, color(&colour));
  }

  void Context::line(const Geometry::Point &start, const Geometry::Point &end, Palette::Colour colour)
  {
    DrawLine(start.x(), start.y(), end.x(), end.y(), color(&colour));
  }
} 

static Color color(const Palette::Colour *colour)
{
  return { colour->m_red, colour->m_green, colour->m_blue, 255 };  
}
