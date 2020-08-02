#!/bin/sh

if [ ! -f ./build/build.ninja ]; then
	meson build
fi

ninja -C ./build/ && ./build/source/Main


