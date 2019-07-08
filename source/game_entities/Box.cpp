#include "Box.h"
#include<typeinfo>

Box::Box() {}
		
Box::Box(Point position) {
	/* This hurts me phyiscally */
	this->myRect = Rect(position, BOX::BOX_WIDTH - 1, BOX::BOX_HEIGHT - 1);
	this->mTexture = NULL;
}

Box::~Box() {
	this->mTexture = NULL;
}

Box::Box(const Box& that) {
	myRect = that.myRect;
}

Box& Box::operator=(const Box& that) {
	this->myRect = that.myRect;
	return *this;
}

void Box::draw(SDL_Renderer* renderer, Point offset) {
	if (mTexture != NULL) {
		this->mTexture->setPos(this->myRect.getTopLeft());
		this->mTexture->render(renderer, offset);
	}
}

Point Box::collideLine(Line& ray) {
	return this->myRect.collideLine(ray);
}

bool Box::overlap(Rect& other) {
	return this->myRect.overlap(other);
}

void Box::setTexture(SuperTexture* texture) {
	this->mTexture = texture;
}

SuperTexture* Box::createBoxTexture(SDL_Renderer* renderer) {
	SuperTexture* texture = new SuperTexture();
	texture->setClip(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
	texture->drawBox(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)), BOX::BOX_INNER_COLOR);
	texture->loadFromFile("resources/missingTexture.jpg", renderer, BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT);
	setRenderColors(renderer, BOX::BOX_OUTER_BORDER_COLOR);
	texture->drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)));
	setRenderColors(renderer, BOX::BOX_INNER_BORDER_COLOR);
	texture->drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT)));
	return texture;
}

bool Box::checkLineCollision(Line& ray) {
	return this->myRect.checkLineCollision(ray);
}
