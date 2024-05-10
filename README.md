<!--
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
-->

<!--
Copyright (c) 2024 David Jackson
-->

# Langton's Ant Farm

Langton's Ant Farm is a program that runs the cellular automaton
[Langton's Ant](https://en.wikipedia.org/wiki/Langton%27s_ant).

## Building & Running

Langton's Ant Farm depends upon:

* A C++20 compiler
* [Raylib version 5.0](https://www.raylib.com/)
* [CMake](https://cmake.org/) (build dependency only)

To build it, create a `build` directory and use CMake:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
````

## Usage

The controls of Langton's Ant Farm are as follows:

* Click on the screen to add an ant at that location
* Press `1` to make each click create a new ant (this is the default)
* Press `2` to make each click invert the colour of the clicked square
* Press `ESC` to quit
* Press `R` to reset (i.e. remove all ands and reset all grid cells to white)
* Press `SPACE` to stop/start the progression of time
* Press `T` to advance time by a single tick (this will also "stop time")
* Press `+` to speed up the time between ticks
* Press `-` to slow down the time between ticks

