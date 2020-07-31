#!/bin/bash
mkdir build 2> /dev/null
meson build && cd build
meson compile
cd ..
cp ./build/source/Main ./Main
./Main
