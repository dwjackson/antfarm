/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Copyright (c) 2024 David Jackson
 */

#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
  private:
    double m_start_time;
    bool m_is_running;
  public:
    Timer();
    void start();
    void stop();
    void restart();
    double elapsed() const;
};

#endif /* TIMER_HPP */
