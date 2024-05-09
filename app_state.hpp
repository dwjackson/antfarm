/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef APP_STATE_HPP
#define APP_STATE_HPP

#include "grids.hpp"
#include "ants.hpp"
#include <vector>
#include <string>

enum class ClickMode {
  CREATE_ANT,
  INVERT_COLOUR
};

class AppState {
  private:
    ClickMode m_click_mode;
    double m_tick_seconds;
    Grids::Grid m_grid;
    std::vector<Ants::Ant> m_ants;
    std::string m_hud;
  public:
    AppState(int height, int width);
    ClickMode click_mode() const;
    void set_click_mode(ClickMode mode);
    int tick_seconds() const;
    const Grids::Grid &grid() const;
    Grids::Grid &grid_mut();
    void add_ant(Ants::Ant ant);
    void update_ants();
    int ants_count() const;
    const std::vector<Ants::Ant> &ants() const;
    const char *hud() const;
};


#endif /* APP_STATE_HPP */
