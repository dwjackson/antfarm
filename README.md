<!--
This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.
-->

<!--
Copyright (c) 2024 David Jackson
-->

# AntFarm

AntFarm is a program that runs the cellular automaton
[Langton's Ant](https://en.wikipedia.org/wiki/Langton%27s_ant).

## Building & Running

AntFarm depends upon:

* A C++20 compiler
* [Raylib version 5.0](https://www.raylib.com/)
* [CMake](https://cmake.org/) (build dependency only)
* [Catch2](https://github.com/catchorg/Catch2) (test dependency only)

To build it, create a `build` directory and use CMake:

```sh
$ mkdir build
$ cd build
$ cmake ..
$ make
````

To run the unit tests, in the build directory:

```sh
$ make test
```

## Usage

```sh
$ antfarm [RULES]
```

The format of `[RULES]` is a string of `L` and `R` characters--e.g. `LLRR`.

To run AntFarm with the default ruleset (Langton's Ant) run the executable
without arguments.

Some interesting rules to try:

* `RL` (the basic Langton's Ant rule)
* `LLRR`
* `RLR`
* `LRRRRRLLR`
* `LLRRRLRLRLLR`
* `RRLLLRLLLRRR`

## Controls

The controls of AntFarm are as follows:

* Click on the screen to add an ant at that location
* Press `1` to make each click create a new ant (this is the default)
* Press `2` to make each click invert the colour of the clicked square
* Press `ESC` to quit
* Press `I` to toggle iterations being show on screen
* Press `R` to reset (i.e. remove all ants and reset all grid cells to white)
* Press `SPACE` to stop/start the progression of time
* Press `T` to advance time by a single tick (this will also "stop time")
* Press `+` to speed up the time between ticks
* Press `-` to slow down the time between ticks

