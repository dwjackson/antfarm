/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef SCENE_HPP
#define SCENE_HPP

#include "drawing.hpp"
#include "app_state.hpp"

class Scene {
  private:
    const int m_side;
    const int m_font_size;
  public:
    Scene(int side, int font_size);
    void draw(Drawing::Window &window, const AppState &state);
};

#endif /* SCENE_HPP */
