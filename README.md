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
* [CMake](https://cmake.org/) (build only)
* [Catch2](https://github.com/catchorg/Catch2) (test only)

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

To run Antfarm for a basic Langton's Ant:

```sh
$ antfarm
````

To supply your own rules, using the default palette:

```sh
$ antfarm [RULES]
```

To supply both your own rules and your own palette:

```sh
$ sh antfarm [PALETTE_FILE_NAME] [RULES]
````

The format of `[RULES]` is a string of `L` and `R` characters--e.g. `LLRR`.

To run AntFarm with the default rule set (Langton's Ant) run the executable
without arguments.

Some interesting rules to try:

* `RL` (the basic Langton's Ant rule)
* `LLRR`
* `RLR`
* `LRRRRRLLR`
* `LLRRRLRLRLLR`
* `RRLLLRLLLRRR`

The palette file is a line-based configuration file. Its format, in
[EBNF](https://en.wikipedia.org/wiki/Extended_Backus%E2%80%93Naur_form)
form is:

```txt
colour = colour name, colour hex ;
colour hex = "0x", hex value ;
hex value = { hex digit } ;
hex digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" | "a" |
            "b" | "c" | "d" | "e" | "f" ;
````

For example:

```txt
white 0xffffff
black 0x000000
````

## Controls

The controls of AntFarm are as follows:

* Click on the screen to add an ant at that location
* Press `1` to make each click create a new ant (this is the default)
* Press `2` to make each click invert the colour of the clicked square
* Press `ESC` to quit
* Press `C` to toggle crosshairs in the center of the screen
* Press `F` to toggle fullscreen mode
* Press `G` to toggle grid
* Press `H` to toggle hiding all "HUD" elements
* Press `I` to toggle iterations being show on screen
* Press `M` to show the current frame rate
* Press `R` to reset (i.e. remove all ants and reset all grid cells to white)
* Press `SPACE` to stop/start the progression of time
* Press `T` to advance time by a single tick (this will also "stop time")
* Press `+` to speed up the time between ticks
* Press `-` to slow down the time between ticks

