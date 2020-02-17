#include "Box.h"

Box::Box() {
	this->flags |= SOLID | DRAW | BLOCKS_VISIBILTY;
}
		
Box::Box(Point position) {
	this->rect = Rect(position, BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	this->flags |= SOLID | DRAW | BLOCKS_VISIBILTY;
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

Point Box::collideLine(const Line& ray) const{
	return this->rect.collideLine(ray);
}

bool Box::overlap(const Rect other) const {
	return this->rect.overlap(other);
}

Point Box::getTopLeft() const {
	return this->rect.getTopLeft();
}

Point Box::getBottomRight() const {
	return this->rect.getBottomRight();
}

Point Box::getPosition() const {
	return this->getTopLeft();
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
	Box::mTexture.bilateralFilter(12.0, 16.0, 7);
}

void Box::drawBox(SDL_Renderer* renderer, Point position, Point offset) {
	Box::mTexture.drawAt(renderer, position, offset);
}

bool Box::doesLineCollide(const Line& ray) const {
	/* True - Line DOES collide with this Box
	 * False - Line DOES NOT collide with this Box */
	return this->rect.doesLineCollide(ray);
}

Rect Box::getRect() const {
	return this->rect;
}

bool Box::overlap(const std::shared_ptr<ThingBase>& other) const {
	return this->overlap(other->getRect());
}

float Box::originDistance() const {
	return this->rect.getBottomRight().distanceToPoint(Point(0, 0));
}

void Box::update() {}
