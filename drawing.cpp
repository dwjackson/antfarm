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
#include <memory>

namespace Drawing {

  Point::Point(int x, int y) : m_x(x), m_y(y)
  {
  }

  int Point::x() const
  {
    return m_x;
  }

  int Point::y() const
  {
    return m_y;
  }

  Window::Window(int width, int height, const char *title) : m_screen_width(width), m_screen_height(height)
  {
    InitWindow(width, height, title);
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

  Point Window::center(const Rectangle &rect)
  {
    int x = m_screen_width / 2 - rect.width() / 2;
    int y = m_screen_height / 2 - rect.height() / 2;
    return Point(x, y);
  }

  void Window::wait(double seconds)
  {
    WaitTime(seconds);
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

  void Context::rectangle(const Point &pos, const Rectangle &rect, Color colour)
  {
    DrawRectangle(pos.x(), pos.y(), rect.width(), rect.height(), colour);
  }

  Rectangle::Rectangle(int width, int height) : m_width(width), m_height(height)
  {
  }

  int Rectangle::width() const
  {
    return m_width;
  }

  int Rectangle::height() const
  {
    return m_height;
  }
} 
