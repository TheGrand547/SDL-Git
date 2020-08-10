#pragma once
#include<SDL2/SDL.h>

typedef uint8_t Uint8;
typedef uint32_t Uint32;

/* Really simple class to base any type of object that needs to have color channels defined. */ 
struct MyBase {
	Uint8 r = 0x00, g = 0x00, b = 0x00, a = 0xFF;
	MyBase();
	MyBase(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	MyBase(const Uint32& color);
	MyBase(const SDL_Color& color);
	MyBase(const MyBase& other);
	void setColorChannels(const Uint32& color);
	void setColorChannels(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);
	void setColorChannels(const MyBase& other);
	void setColorChannels(const SDL_Color& color);
};
