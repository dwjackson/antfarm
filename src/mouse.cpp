
/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef MOUSE_HPP
#define MOUSE_HPP

extern "C" {
  #include "raylib.h"
}

namespace Mouse {
   bool is_left_button_pressed()
   {
     return IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
   }

   int get_x()
   {
     return GetMouseX();
   }

   int get_y()
   {
     return GetMouseY();
   }
};

#endif /* MOUSE_HPP */
