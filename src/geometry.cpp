/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "geometry.hpp"

namespace Geometry {
  
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


  Point Rectangle::center_within(int width, int height)
  {
    int x = width / 2 - m_width - 2;
    int y = height / 2 - m_height / 2;
    return Point(x, y);
  }
}
