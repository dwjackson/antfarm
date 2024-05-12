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

extern "C" {
  #include "raylib.h"
}

namespace Palette {  

  class Palette {
    private:
      const std::vector<Color> m_colours;
    public:
      Palette(std::vector<Color> colours);
      Color operator [](int index) const;
      int next(int index, int limit) const;
      int size() const;
  };

  Color color_from_hex(unsigned int hex);
  Color parse_color(std::string input);
  Palette parse_palette(std::string file_name);
  Palette default_palette(void);
}

#endif /* PALETTE_HPP */
