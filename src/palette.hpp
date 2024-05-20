/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef PALETTE_HPP
#define PALETTE_HPP

#include <string>
#include <vector>

typedef unsigned char byte;

namespace Palette {  

  class Colour {
    public:
      const byte m_red;
      const byte m_green;
      const byte m_blue;

      Colour(byte r, byte g, byte b) : m_red(r), m_green(g), m_blue(b)
      {
      }
  };

  class Palette {
    private:
      const std::vector<Colour> m_colours;
    public:
      Palette(std::vector<Colour> colours);
      Colour operator [](int index) const;
      int next(int index, int limit) const;
      int size() const;
  };

  Colour color_from_hex(unsigned int hex);
  Colour parse_color(std::string input);
  Palette parse_palette(std::string file_name);
}

#endif /* PALETTE_HPP */
