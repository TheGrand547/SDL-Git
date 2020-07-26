#pragma once
#include<SDL2/SDL.h>

typedef uint8_t Uint8;

/* Really simple class to base any type of object that needs to have color channels defined. */ 
struct MyBase {
	Uint8 r, g, b, a;
	MyBase(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0xFF, Uint8 a = 0xFF);
	MyBase(const SDL_Color& color);
	MyBase(const MyBase& other);
	void setColorChannels(Uint8 r = 0x00, Uint8 g = 0x00, Uint8 b = 0xFF, Uint8 a = 0xFF);
	void setColorChannels(const MyBase& other);
	void setColorChannels(const SDL_Color& color);
};
