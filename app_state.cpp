/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "app_state.hpp"
#include <vector>
#include <ranges>
#include <string>
#include <format>

#define CREATE_ANT_STR "Create Ant"
#define INVERT_CELL_STR "Invert Cell"

const double tick_min = 0.05;
const double tick_max = 1.00;
const double tick_delta = 0.1;

AppState::AppState(int height, int width) : m_grid(height, width)
{
  m_tick_seconds = tick_min;
  set_click_mode(ClickMode::CREATE_ANT);
}

ClickMode AppState::click_mode() const
{
 return m_click_mode;
}

void AppState::set_click_mode(ClickMode mode)
{
  m_click_mode = mode;
  const char *click_control = m_click_mode == ClickMode::CREATE_ANT ? CREATE_ANT_STR : INVERT_CELL_STR;
  m_hud = std::format("[CLICK] {} [SPACE] Pause [ESC] Quit [1,2] Change Mode [T] Step Time [+,-] Speed/Slow Time [R] Reset", click_control);
}

double AppState::tick_seconds() const
{
  return m_tick_seconds;
}

const Grids::Grid &AppState::grid() const
{
  return m_grid;
}

Grids::Grid &AppState::grid_mut()
{
  return m_grid;
}

void AppState::add_ant(Ants::Ant ant)
{
  m_ants.push_back(ant);
}

void AppState::update_ants()
{
  std::vector<std::vector<Ants::Ant>::size_type> to_remove;
  for (std::vector<Ants::Ant>::size_type i = 0; i < m_ants.size(); i++) {
    auto ant = &m_ants[i];
    auto row = ant->row();
    auto col = ant->col();
    m_grid.invert_cell(row, col);
    auto next_ant = ant->next(m_grid);
    if (m_grid.is_out_of_bounds(next_ant.row(), next_ant.col())) {
      to_remove.push_back(i);
    } else {
      m_ants[i] = ant->next(m_grid);
    }
  }
  // Remove any ants that left the grid
  for (auto index : to_remove | std::views::reverse) {
    m_ants.erase(m_ants.begin() + index);
  }    
}

int AppState::ants_count() const
{
  return m_ants.size();
}

const std::vector<Ants::Ant> &AppState::ants() const
{
  return m_ants;
}

const char *AppState::hud() const
{
  return m_hud.c_str();
}

void AppState::speed_up()
{
  if (m_tick_seconds - tick_delta <= tick_min) {
    m_tick_seconds = tick_min;
  } else {
    m_tick_seconds -= tick_delta;
  }
}

void AppState::slow_down()
{
  if (m_tick_seconds + tick_delta >= tick_max) {
    m_tick_seconds = tick_max;
  } else {
    m_tick_seconds += tick_delta;
  }
}

void AppState::reset()
{
  m_ants.clear();
  m_grid.reset();
}
