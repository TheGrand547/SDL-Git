#include "MyBase.h"
#include<iostream>

MyBase::MyBase() {}

MyBase::MyBase(Uint8 r, Uint8 g, Uint8 b, Uint8 a) : r(r), g(g), b(b), a(a) {}

MyBase::MyBase(const Uint32& color) {
	this->r = (color & 0xFF000000) >> 24;
	this->g = (color & 0x00FF0000) >> 16;
	this->b = (color & 0x0000FF00) >> 8;
	this->a = (color & 0x000000FF);
}

MyBase::MyBase(const SDL_Color& color) : r(color.r), g(color.g), b(color.b), a(color.a) {}

MyBase::MyBase(const MyBase& other) : r(other.r), g(other.g), b(other.b), a(other.a){}

void MyBase::setColorChannels(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void MyBase::setColorChannels(const Uint32& color) {
	this->r = (color & 0xFF000000) >> 24;
	this->g = (color & 0x00FF0000) >> 16;
	this->b = (color & 0x0000FF00) >> 8;
	this->a = (color & 0x000000FF);
}

void MyBase::setColorChannels(const MyBase& other) {
	this->r = other.r;
	this->g = other.g;
	this->b = other.b;
	this->a = other.a;
}

void MyBase::setColorChannels(const SDL_Color& color) {
	this->r = color.r;
	this->g = color.g;
	this->b = color.b;
	this->a = color.a;
}

