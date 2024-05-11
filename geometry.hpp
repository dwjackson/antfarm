/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

namespace Geometry {
  
  class Point {
    private:
      const int m_x;
      const int m_y;
    public:
      Point(int x, int y);
      int x() const;
      int y() const;
  };

  class Rectangle {
    private:
      const int m_width;
      const int m_height;
    public:
      Rectangle(int width, int height);
      int width() const;
      int height() const;
      Point center_within(int width, int height);
  };

}

#endif /* GEOMETRY_HPP */
