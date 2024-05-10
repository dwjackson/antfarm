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

extern "C" {
  #include "raylib.h"
}

class Palette {
  private:
    const Color *m_colours;
    const int m_size;
  public:
    Palette(Color *colours, int size);
    Color operator [](int index) const;
    int next(int index, int limit) const;
    int size() const;
};

#endif /* PALETTE_HPP */
