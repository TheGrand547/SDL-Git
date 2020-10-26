#pragma once
#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <SDL.h>

typedef uint8_t Uint8;
typedef uint32_t Uint32;

struct Color : public SDL_Color {
	Color();
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	Color(const Uint32& color);
	Color(const SDL_Color& color);
	Color(const Color& other);
	
	bool keyCompare(const SDL_Color& color);
	
	void setColorChannels(const Uint32& color);
	void setColorChannels(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a = 0xFF);
	void setColorChannels(const Color& other);
	void setColorChannels(const SDL_Color& color);
	
	friend std::ostream& operator<<(std::ostream& output, const Color& color);
};
#endif
