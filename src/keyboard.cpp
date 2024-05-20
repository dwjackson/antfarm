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
#include "keyboard.hpp"
#include <cctype>
#include <cstdlib>
#include <cstdio>

static int get_raylib_key(char key);
static bool requires_shift(int key);

bool Keyboard::is_key_pressed(char key)
{
  auto raylib_key = get_raylib_key(tolower(key));
  
  if (requires_shift(key)) {
    auto isShiftPressed = IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT);
    return isShiftPressed && IsKeyPressed(raylib_key);
  }

  return IsKeyPressed(raylib_key);
}

static int get_raylib_key(char key)
{
  // Note: We assume ASCII or UTF-8
  switch (key) {
    case ' ':
      return KEY_SPACE;
    case '1':
    case '!':
      return KEY_ONE;
    case '2':
    case '@':
      return KEY_TWO;
    case '3':
    case '#':
      return KEY_THREE;
    case '4':
    case '$':
      return KEY_FOUR;
    case '5':
    case '%':
      return KEY_FIVE;
    case '6':
    case '^':
      return KEY_SIX;
    case '7':
    case '&':
      return KEY_SEVEN;
    case '8':
    case '*':
      return KEY_EIGHT;
    case '9':
    case '(':
      return KEY_NINE;
    case '0':
    case ')':
      return KEY_ZERO;
    case 'c':
      return KEY_C;
    case 'f':
      return KEY_F;
    case 'g':
      return KEY_G;
    case 'h':
      return KEY_H;
    case 'i':
      return KEY_I;
    case 'm':
      return KEY_M;
    case 'r':
      return KEY_R;
    case 't':
      return KEY_T;
    case '=':
    case '+':
      return KEY_EQUAL;
    case '-':
    case '_':
      return KEY_MINUS;
    default:
      fprintf(stderr, "Unrecognized key: '%c'\n", key);
      std::abort();
  }
}

static bool requires_shift(int key)
{
  if (isupper(key)) {
    return true;
  }
  switch(key) {
    case '~':
    case '!':
    case '@':
    case '#':
    case '$':
    case '%':
    case '^':
    case '&':
    case '*':
    case '(':
    case ')':
    case '+':
    case '{':
    case '}':
    case '|':
    case ':':
    case '"':
    case '<':
    case '>':
    case '?':
      return true;
    default:
      return false;
  }
}
