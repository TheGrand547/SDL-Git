#include "SDL_Headers.h"

Renderer Renderer::operator+(const Point& point) const {
	return {this->offset + point, this->renderer};
}

Renderer Renderer::operator-(const Point& point) const {
	return *this + (-point);
}

void Renderer::operator+=(const Point& point) {
	this->offset += point;
}

void Renderer::operator-=(const Point& point) {
	*this += -point;
}

Renderer operator+(const Point& point, const Renderer& renderer) {
	return renderer + point;
}
Renderer operator-(const Point& point, const Renderer& renderer) {
	return {point - renderer.offset, renderer.renderer};
}
