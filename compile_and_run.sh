#!/bin/bash
mkdir build 2> /dev/null
meson build && cd build && meson compile && ./source/Main

