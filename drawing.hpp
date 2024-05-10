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
#include <memory>

namespace Drawing {

  class Rectangle {
    private:
      const int m_width;
      const int m_height;
    public:
      Rectangle(int width, int height);
      int width() const;
      int height() const;
  };

  class Point {
    private:
      const int m_x;
      const int m_y;
    public:
      Point(int x, int y);
      int x() const;
      int y() const;
  };

  class Context {
    public:
      Context();
      ~Context();
      void clear_background();
      void rectangle(const Point &pos, const Rectangle &rect, Color colour);
      void text(const char *text, Point &pos, int font_size, Color colour);
  };

  class Window {
    private:
      const int m_screen_width;
      const int m_screen_height;
      int m_monitor_height;
      int m_monitor_width;
    public:
      Window(int width, int height, const char *title);
      ~Window();
      std::unique_ptr<Context> draw();
      bool should_close();
      Point center(const Rectangle &rect);
      int monitor_width() const;
      int monitor_height() const;
  };

}
