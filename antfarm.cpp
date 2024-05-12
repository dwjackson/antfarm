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
#include <cstdio>
#include <cstdlib>
#include <format>

const int side = 10;
const int max_ants = 10;

const int screen_width = 1440;
const int screen_height = 900;
const int font_size = 20;

typedef void (*click_handler)(AppState &state, int x, int y);

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

  bool is_paused = false;
  timer.start();
  while (!window.should_close()) {
    scene.draw(window, state);

    // Change the click mode
    if (IsKeyPressed(KEY_ONE)) {
      state.set_click_mode(ClickMode::CREATE_ANT);
    } else if (IsKeyPressed(KEY_TWO)) {
      state.set_click_mode(ClickMode::INVERT_COLOUR);
    }

    // Add an ant if the user clicks somewhere
    click_handler handler;
    if (state.click_mode() == ClickMode::CREATE_ANT && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && state.ants_count() < max_ants) {
      handler = add_ant;
    } else if (state.click_mode() == ClickMode::INVERT_COLOUR && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      handler = cycle_colour;
    } else {
      handler = NULL;
    }
    if (handler) {
      handler(state, GetMouseX(), GetMouseY());
    }

    // Speed up or slow down time
    bool is_plus_pressed = (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) && IsKeyPressed(KEY_EQUAL);
    if (is_plus_pressed) {
      state.speed_up();
    } else if (IsKeyPressed(KEY_MINUS)) {
      state.slow_down();
    }

    // Pause if the user presses the spacebar
    if (IsKeyPressed(KEY_SPACE)) {
      is_paused = !is_paused;
    }

    // Move time forward by a single tick if "T" is pressed
    if (IsKeyPressed(KEY_T)) {
      if (!is_paused) {
        is_paused = true;
      }
      state.tick();
    }

    // Reset the state if "R" is pressed
    if (IsKeyPressed(KEY_R)) {
      state.reset();
    }

    // Print iterations if "I" is pressed
    if (IsKeyPressed(KEY_I)) {
      state.toggle_show_iterations();
    }

    // Toggle fullscreen if "F" is pressed
    if (IsKeyPressed(KEY_F)) {
      toggle_fullscreen(state, window);
    }

    // Toggle the crosshairs if "C" is pressed
    if (IsKeyPressed(KEY_C)) {
      state.toggle_crosshairs();
    }

    // Toggle the grid if "G" prssed
    if (IsKeyPressed(KEY_G)) {
      state.toggle_grid();
    }

    double elapsed_time = timer.elapsed();
    if (!is_paused && elapsed_time >= state.tick_seconds()) {
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

