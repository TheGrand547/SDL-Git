#include "Box.h"
#include<typeinfo>

Box::Box() {}
		
Box::Box(Point position) {
	this->rect = Rect(position, BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
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

Point Box::getTopLeft() {
	return this->rect.getTopLeft();
}

Point Box::getBottomRight() {
	return this->rect.getBottomRight();
}

void Box::createBoxTexture(SDL_Renderer* renderer) {
	Box::mTexture.setClip(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	Box::mTexture.drawBox(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)), BOX::BOX_INNER_COLOR);
	Box::mTexture.loadFromFile(BOX::BOX_TEXTURE, renderer, BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT);
	setRenderColors(renderer, BOX::BOX_OUTER_BORDER_COLOR);
	Box::mTexture.drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)));
	setRenderColors(renderer, BOX::BOX_INNER_BORDER_COLOR);
	Box::mTexture.drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT)));
	Box::mTexture.normalizeTexture(renderer);
}

void Box::drawBox(SDL_Renderer* renderer, Point position, Point offset) {
	Box::mTexture.drawAt(renderer, position, offset);
}

bool Box::doesLineCollide(Line& ray) {
	/* True - Line DOES collide with this Box
	 * False - Line DOES NOT collide with this Box */
	return this->rect.doesLineCollide(ray);
}
