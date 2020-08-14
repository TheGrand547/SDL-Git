#include "Color.h"
#include<iostream>

Color::Color() {}

Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(const Uint32& color) {
	this->r = (color & 0xFF000000) >> 24;
	this->g = (color & 0x00FF0000) >> 16;
	this->b = (color & 0x0000FF00) >> 8;
	this->a = (color & 0x000000FF);
}

Color::Color(const SDL_Color& color) {
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

Color::Color(const Color& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;
}

void Color::setColorChannels(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::setColorChannels(const Uint32& color) {
	this->r = (color & 0xFF000000) >> 24;
	this->g = (color & 0x00FF0000) >> 16;
	this->b = (color & 0x0000FF00) >> 8;
	this->a = (color & 0x000000FF);
}

void Color::setColorChannels(const Color& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;
}

void Color::setColorChannels(const SDL_Color& color) {
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

std::ostream& operator<<(std::ostream& output, const Color& color) {
	output << "R: " << color.r << " G: " << color.g << " B: " << color.b << " A: " << color.a;
	return output;
}
