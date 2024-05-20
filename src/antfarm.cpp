/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "ants.hpp"
#include "drawing.hpp"
#include "app_state.hpp"
#include "palette.hpp"
#include "timer.hpp"
#include "rules.hpp"
#include "scene.hpp"
#include "keyboard.hpp"
#include "config.hpp"
#include "mouse.hpp"
#include <cstdio>
#include <cstdlib>
#include <format>
#include <functional>
#include <string>

typedef void (*click_handler)(AppState &state, int x, int y);

struct key_handler {
  char key;
  std::function<void(AppState&)> handler;
};

static void add_ant(AppState &state, int x, int y);
static void cycle_colour(AppState &state, int x, int y);
static void toggle_fullscreen(AppState &state, Drawing::Window &window);
static Palette::Palette default_palette(void);
static Palette::Colour rgb(byte r, byte g, byte b);

int main(int argc, char *argv[])
{
  const int height = SCREEN_HEIGHT / SIDE - FONT_SIZE / SIDE;
  const int width = SCREEN_WIDTH / SIDE;

  // Parse the colour palette
  auto palette = argc < 3 ?
                           default_palette()
                           :
                           Palette::parse_palette(std::string(argv[1]));
  if (palette.size() == 0) {
    fprintf(stderr, "ERROR: Empty palette\n");
    return EXIT_FAILURE;
  }

  // Set up the rule(s)
  const char *rules;
  if (argc == 2) {
    rules = argv[1];
  } else if (argc > 2) {
    rules = argv[2];
  } else {
    rules = ANT_STANDARD_RULE;
  }
  auto validation_result = rules_validate(rules, palette);
  if (validation_result != RulesError::NONE) {
    std::string explanation = rules_error_explain(validation_result);
    fprintf(stderr, "%s\n", explanation.c_str());
    return EXIT_FAILURE;
  }

  auto title = std::format("Ant Farm ({})", rules);
  auto window = Drawing::Window(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str());
  Timer timer;
  AppState state = AppState(height, width, rules, palette);
  Scene scene(SIDE, FONT_SIZE);

  // Key Handlers
  key_handler key_handlers[] = {
    { '1', [](AppState &state) { state.set_click_mode(ClickMode::CREATE_ANT); } },
    { '2', [](AppState &state) { state.set_click_mode(ClickMode::CYCLE_COLOUR); } },
    { '+', [](AppState &state) { state.speed_up(); } },
    { '-', [](AppState &state) { state.slow_down(); } },
    { ' ', [](AppState &state) { state.toggle_pause(); } },
    { 'c', [](AppState &state) { state.toggle_crosshairs(); } },
    { 'g', [](AppState &state) { state.toggle_grid(); } },
    { 'h', [](AppState &state) { state.toggle_hide_all(); } },
    { 'i', [](AppState &state) { state.toggle_show_iterations(); } },
    { 'm', [](AppState &state) { state.toggle_frame_rate_visible(); }},
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
    if (state.click_mode() == ClickMode::CREATE_ANT && Mouse::is_left_button_pressed() && state.ants_count() < MAX_ANTS) {
      handler = add_ant;
    } else if (state.click_mode() == ClickMode::CYCLE_COLOUR && Mouse::is_left_button_pressed()) {
      handler = cycle_colour;
    } else {
      handler = NULL;
    }
    if (handler) {
      handler(state, Mouse::get_x(), Mouse::get_y());
    }

    // Key Handlers
    for (int i = 0; i < key_handler_count; i++) {
      auto kh = &key_handlers[i];
      if (Keyboard::is_key_pressed(kh->key)) {
        kh->handler(state);
      }
    }

    // Toggle fullscreen if "F" is pressed
    if (Keyboard::is_key_pressed('f')) {
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
  int row = y / SIDE;
  int col = x / SIDE;
  state.add_ant(Ants::Ant(row, col, Ants::Direction::NORTH));
}

static void cycle_colour(AppState &state, int x, int y)
{
  int row = y / SIDE;
  int col = x / SIDE;
  state.cycle_colour(row, col);
}

static void toggle_fullscreen(AppState &state, Drawing::Window &window)
{
  window.toggle_full_screen();

  int height, width;
  if (window.is_full_screen()) {
    width = window.monitor_width();
    height = window.monitor_height();
  } else {
    height = SCREEN_HEIGHT;
    width = SCREEN_WIDTH;
  }
  window.set_size(width, height);

  // Resize the grid
  height /= SIDE;
  height -= FONT_SIZE / SIDE;
  width /= SIDE;
  state.resize_grid(height, width);
}

static Palette::Palette default_palette(void)
{
  std::vector<Palette::Colour> colours = {
    rgb(245, 245, 245),
    rgb(0, 0, 0),
    rgb(112, 31, 126),
    rgb(135, 60, 190),
    rgb(200, 122, 255),
    rgb(0, 82, 172),
    rgb(0, 121, 241),
    rgb(102, 191, 255),
    rgb(0, 117, 44),
    rgb(0, 158, 47),
    rgb(0, 228, 48),
    rgb(190, 33, 55),
    rgb(255, 109, 194),
    rgb(255, 161, 0),
    rgb(255, 203, 0),
    rgb(253, 249, 0)
  };
  return Palette::Palette(colours);
}

static Palette::Colour rgb(byte r, byte g, byte b)
{
  return Palette::Colour(r, g, b);
}
