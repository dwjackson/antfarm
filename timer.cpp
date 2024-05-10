/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#include "timer.hpp"
#include "raylib.h"

Timer::Timer()
{
  m_is_running = false;
  m_start_time = 0.0;
}

void Timer::start()
{
  m_start_time = GetTime();
  m_is_running = true;
}

void Timer::stop()
{
  m_is_running = false;
  m_start_time = 0.0;
}

void Timer::restart()
{
  stop();
  start();
}

double Timer::elapsed() const
{
  if (!m_is_running) {
    return 0.0;
  }

  double now = GetTime();
  return now - m_start_time; 
}

