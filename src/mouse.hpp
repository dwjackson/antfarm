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

namespace Mouse {
   bool is_left_button_pressed();
   int get_x();
   int get_y();
};

#endif /* MOUSE_HPP */
