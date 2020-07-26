#include "MyBase.h"

MyBase::MyBase(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}

MyBase::MyBase(const SDL_Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

MyBase::MyBase(const MyBase& other) : r(other.r), g(other.g), b(other.b), a(other.a){}

void MyBase::setColorChannels(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	*this = MyBase(r, g, b, a);
}

void MyBase::setColorChannels(const MyBase& other) {
	*this = MyBase(other);
}

void MyBase::setColorChannels(const SDL_Color& color) {
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

