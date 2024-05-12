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
#include "palette.hpp"
#include <vector>
#include <string>

enum class ClickMode {
  CREATE_ANT,
  CYCLE_COLOUR
};

class AppState {
  private:
    ClickMode m_click_mode;
    double m_tick_seconds;
    Grids::Grid m_grid;
    std::vector<Ants::Ant> m_ants;
    std::string m_hud;
    const char *m_rules;
    int m_rules_len;
    Palette m_palette;
    int m_iterations;
    bool m_show_iterations;
    bool m_show_crosshairs;
    bool m_show_grid;
    bool m_is_paused;
  public:
    AppState(int height, int width, const char *rules, Palette palette);
    ClickMode click_mode() const;
    void set_click_mode(ClickMode mode);
    double tick_seconds() const;
    const Grids::Grid &grid() const;
    Grids::Grid &grid_mut();
    void add_ant(Ants::Ant ant);
    void tick();
    int ants_count() const;
    const std::vector<Ants::Ant> &ants() const;
    const char *hud() const;
    void speed_up();
    void slow_down();
    void reset();
    Color colour(int index) const;
    void cycle_colour(int row, int col);
    int iterations() const;
    void toggle_show_iterations();
    bool show_iterations() const;
    void resize_grid(int height, int width);
    void toggle_crosshairs();
    bool is_crosshairs_visible() const;
    void toggle_grid();
    bool is_grid_visible() const;
    void toggle_pause();
    bool is_paused() const;
};

#endif /* APP_STATE_HPP */
