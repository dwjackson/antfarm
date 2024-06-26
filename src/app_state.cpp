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
#include <cstring>

#define CREATE_ANT_STR "Create Ant"
#define CHANGE_COLOUR_STR "Change Colour"

const double tick_min = 0.05;
const double tick_max = 1.00;
const double tick_delta = 0.1;

AppState::AppState(int height, int width, const char *rules, Palette::Palette palette) : m_grid(height, width), m_palette(palette)
{
  m_tick_seconds = tick_min;
  m_rules = rules;
  m_rules_len = strlen(rules);
  m_iterations = 0;
  m_show_iterations = false;
  m_show_crosshairs = false;
  m_show_grid = false;
  m_is_paused = false;
  m_show_frame_rate = false;
  m_is_all_hidden = false;
  set_click_mode(ClickMode::CREATE_ANT);
}

ClickMode AppState::click_mode() const
{
 return m_click_mode;
}

void AppState::set_click_mode(ClickMode mode)
{
  m_click_mode = mode;
  const char *click_control = m_click_mode == ClickMode::CREATE_ANT ? CREATE_ANT_STR : CHANGE_COLOUR_STR;
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

void AppState::tick()
{
  std::vector<std::vector<Ants::Ant>::size_type> to_remove;
  for (std::vector<Ants::Ant>::size_type i = 0; i < m_ants.size(); i++) {
    auto ant = &m_ants[i];

    // Compute the next ant
    auto next_ant = ant->next(m_grid, m_rules);

    // Compute the next cell colour
    auto row = ant->row();
    auto col = ant->col();
    auto index = m_grid.cell(row, col);
    auto next_index = m_palette.next(index, m_rules_len);

    // Change the colour of the cell
    m_grid.set_cell(row, col, next_index);

    // Move the ant
    if (m_grid.is_out_of_bounds(next_ant.row(), next_ant.col())) {
      to_remove.push_back(i);
    } else {
      m_ants[i] = next_ant;
    }
  }

  // Remove any ants that left the grid
  for (auto index : to_remove | std::views::reverse) {
    m_ants.erase(m_ants.begin() + index);
  }

  if (m_ants.size() > 0) {
    m_iterations++;
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
  m_iterations = 0;
}

Palette::Colour AppState::colour(int index) const
{
  return m_palette[index];
}

void AppState::cycle_colour(int row, int col)
{
  auto index = m_grid.cell(row, col);
  auto next_index = m_palette.next(index, m_rules_len);
  m_grid.set_cell(row, col, next_index);
}

int AppState::iterations() const
{
  return m_iterations;
}

void AppState::toggle_show_iterations()
{
  m_show_iterations = !m_show_iterations;
}

bool AppState::show_iterations() const
{
  return m_show_iterations;
}

void AppState::resize_grid(int height, int width)
{
  auto height_prev = m_grid.height();
  auto width_prev = m_grid.width();
  
  m_grid.resize(height, width);

  // Move the ants so that they move with the drawings
  auto resizer = Grids::Resizer(height_prev, width_prev, height, width);
  for (auto &ant : m_ants) {
    auto dest = resizer.move(ant.row(), ant.col());
    ant.move(dest.y(), dest.x());
  }

  // Cull any ants that have left the grid
  std::vector<std::vector<Ants::Ant>::size_type> to_remove;
  for (std::vector<Ants::Ant>::size_type i = 0; i < m_ants.size(); i++) {   
    auto ant = &m_ants[i];
    if (m_grid.is_out_of_bounds(ant->row(), ant->col())) {
      to_remove.push_back(i);
    }
  }
  for (auto index : to_remove | std::views::reverse) {
    m_ants.erase(m_ants.begin() + index);
  }
}

void AppState::toggle_crosshairs()
{
  m_show_crosshairs = !m_show_crosshairs;
}

bool AppState::is_crosshairs_visible() const
{
  return m_show_crosshairs;
}


void AppState::toggle_grid()
{
  m_show_grid = !m_show_grid;
}

bool AppState::is_grid_visible() const
{
  return m_show_grid;
}

void AppState::toggle_pause()
{
  m_is_paused = !m_is_paused; 
}

bool AppState::is_paused() const
{
  return m_is_paused;
}

void AppState::toggle_frame_rate_visible()
{
  m_show_frame_rate = !m_show_frame_rate;
}

bool AppState::is_frame_rate_visible() const
{
  return m_show_frame_rate;
}

void AppState::toggle_hide_all()
{
  m_is_all_hidden = !m_is_all_hidden;
}

bool AppState::is_all_hidden() const
{
  return m_is_all_hidden;
}
