/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

extern "C" {
  #include "raylib.h"
}

#include "ants.hpp"
#include "drawing.hpp"
#include "app_state.hpp"
#include "palette.hpp"
#include "timer.hpp"
#include "rules.hpp"
#include "scene.hpp"
#include "keyboard.hpp"
#include <cstdio>
#include <cstdlib>
#include <format>
#include <functional>

const int side = 10;
const int max_ants = 10;

const int screen_width = 1440;
const int screen_height = 900;
const int font_size = 20;

typedef void (*click_handler)(AppState &state, int x, int y);

struct key_handler {
  char key;
  std::function<void(AppState&)> handler;
};

static void add_ant(AppState &state, int x, int y);
static void cycle_colour(AppState &state, int x, int y);
static void toggle_fullscreen(AppState &state, Drawing::Window &window);

int main(int argc, char *argv[])
{
  const int height = screen_height / side - font_size / side;
  const int width = screen_width / side;
  
  Color colours[] = {
    RAYWHITE,
    BLACK,
    DARKPURPLE,
    VIOLET,
    PURPLE,
    DARKBLUE,
    BLUE,
    SKYBLUE,
    DARKGREEN,
    LIME,
    GREEN,
    MAROON,
    PINK,
    ORANGE,
    GOLD,
    YELLOW
  };
  int colours_count = sizeof(colours) / sizeof(colours[0]);
  Palette palette = Palette(colours, colours_count);

  // Set up the rule(s)
  const char *rules = ANT_STANDARD_RULE;
  if (argc > 1) {
    rules = argv[1];
  }
  if (!rules_validate(rules, palette)) {
    fprintf(stderr, "Invalid rules\n");
    std::abort();
  }

  auto title = std::format("Ant Farm ({})", rules);
  auto window = Drawing::Window(screen_width, screen_height, title.c_str());
  Timer timer;
  AppState state = AppState(height, width, rules, palette);
  Scene scene(side, font_size);

  // Key Handlers
  key_handler key_handlers[] = {
    { '1', [](AppState &state) { state.set_click_mode(ClickMode::CREATE_ANT); } },
    { '2', [](AppState &state) { state.set_click_mode(ClickMode::CYCLE_COLOUR); } },
    { '+', [](AppState &state) { state.speed_up(); } },
    { '-', [](AppState &state) { state.slow_down(); } },
    { ' ', [](AppState &state) { state.toggle_pause(); } },
    { 'c', [](AppState &state) { state.toggle_crosshairs(); } },
    { 'g', [](AppState &state) { state.toggle_grid(); } },
    { 'i', [](AppState &state) { state.toggle_show_iterations(); } },
    { 'r', [](AppState &state) { state.reset(); } },
    { 't', [](AppState &state) {
      if (!state.is_paused()) {
        state.toggle_pause();
      }
      state.tick();
    } }
  };
  int key_handler_count = sizeof(key_handlers) / sizeof(key_handlers[0]);

  timer.start();
  while (!window.should_close()) {
    scene.draw(window, state);

    // Add an ant if the user clicks somewhere
    click_handler handler;
    if (state.click_mode() == ClickMode::CREATE_ANT && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state.ants_count() < max_ants) {
      handler = add_ant;
    } else if (state.click_mode() == ClickMode::CYCLE_COLOUR && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      handler = cycle_colour;
    } else {
      handler = NULL;
    }
    if (handler) {
      handler(state, GetMouseX(), GetMouseY());
    }

    // Key Handlers
    for (int i = 0; i < key_handler_count; i++) {
      auto kh = &key_handlers[i];
      if (Keyboard::is_key_pressed(kh->key)) {
        kh->handler(state);
      }
    }

    // Toggle fullscreen if "F" is pressed
    if (IsKeyPressed(KEY_F)) {
      toggle_fullscreen(state, window);
    }

    double elapsed_time = timer.elapsed();
    if (!state.is_paused() && elapsed_time >= state.tick_seconds()) {
      state.tick();
      timer.restart();
    }
  }

  return 0;
}

static void add_ant(AppState &state, int x, int y)
{
  int row = y / side;
  int col = x / side;
  state.add_ant(Ants::Ant(row, col, Ants::Direction::NORTH));
}

static void cycle_colour(AppState &state, int x, int y)
{
  int row = y / side;
  int col = x / side;
  state.cycle_colour(row, col);
}

static void toggle_fullscreen(AppState &state, Drawing::Window &window)
{
  ToggleFullscreen();

  int height, width;
  if (IsWindowFullscreen()) {
    width = window.monitor_width();
    height = window.monitor_height();
  } else {
    height = screen_height;
    width = screen_width;
  }
  SetWindowSize(width, height);

  // Resize the grid
  height /= side;
  height -= font_size / side;
  width /= side;
  state.resize_grid(height, width);
}

