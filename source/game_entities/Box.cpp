#include "Box.h"
#include<typeinfo>

Box::Box() {}
		
Box::Box(Point position) {
	/* This hurts me phyiscally */
	this->rect = Rect(position, BOX::BOX_WIDTH - 1, BOX::BOX_HEIGHT - 1);
}

Box::~Box() {}

Box::Box(const Box& that) {
	rect = that.rect;
}

Box& Box::operator=(const Box& that) {
	this->rect = that.rect;
	return *this;
}

void Box::draw(SDL_Renderer* renderer, Point offset) {
	Box::drawBox(renderer, this->rect.getTopLeft(), offset);
}

Point Box::collideLine(Line& ray) {
	return this->rect.collideLine(ray);
}

bool Box::overlap(Rect& other) {
	return this->rect.overlap(other);
}


void Box::createBoxTexture(SDL_Renderer* renderer) {
	Box::mTexture.setClip(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	Box::mTexture.drawBox(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)), BOX::BOX_INNER_COLOR);
	Box::mTexture.loadFromFile(BOX::BOX_TEXTURE, renderer, BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT);
	setRenderColors(renderer, BOX::BOX_OUTER_BORDER_COLOR);
	Box::mTexture.drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)));
	setRenderColors(renderer, BOX::BOX_INNER_BORDER_COLOR);
	Box::mTexture.drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT)));
}

void Box::drawBox(SDL_Renderer* renderer, Point position, Point offset) {
	Box::mTexture.drawAt(renderer, position, offset);
}

bool Box::checkLineCollision(Line& ray) {
	return this->rect.checkLineCollision(ray);
}
