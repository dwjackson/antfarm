/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef DRAWING_HPP
#define DRAWING_HPP

#include "geometry.hpp"
#include "palette.hpp"
#include <memory>

namespace Drawing {

  class Context {
    public:
      Context();
      ~Context();
      void clear_background();
      void rectangle(const Geometry::Point &pos, const Geometry::Rectangle &rect, Palette::Colour colour);
      void text(const char *text, Geometry::Point &pos, int font_size, Palette::Colour colour);
      void line(const Geometry::Point &start, const Geometry::Point &end, Palette::Colour colour);
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
      Geometry::Point center(const Geometry::Rectangle &rect);
      int monitor_width() const;
      int monitor_height() const;
      int screen_width() const;
      int screen_height() const;
      int measure_text(const char *text, int font_size) const;
      int fps() const;
      bool is_full_screen() const;
      void toggle_full_screen();
      void set_size(int width, int height);
  };

}

#endif /* DRAWING_HPP */
