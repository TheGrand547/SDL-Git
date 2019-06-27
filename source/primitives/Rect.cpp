#include "Rect.h"

Rect::Rect() {
	this->tL = Point();
	this->tR = Point();
	this->bL = Point();
	this->bR = Point();
}

Rect::Rect(Point topLeft, Point bottomRight) {
	this->tL = Point(topLeft);
	this->tR = Point(bottomRight.x(), topLeft.y());
	this->bL = Point(topLeft.x(), bottomRight.y());
	this->bR = Point(bottomRight);
}

Rect::Rect(float x, float y, int width, int height) {
	*this = Rect(Point(x, y), width, height);
}

Rect::Rect(Point position, int width, int height) {
	this->tL = Point(position);
	this->tR = Point(position.x() + width, position.y());
	this->bL = Point(position.x(), position.y() + height);
	this->bR = Point(position + Point(width, height));
}

Rect::Rect(const Rect &that) {
	tL = Point(that.tL);
	tR = Point(that.tR);
	bL = Point(that.bL);
	bR = Point(that.bR);
}

Rect::~Rect() {}

void Rect::superDraw(SDL_Renderer* renderer, Point offset) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	this->setColorChannels(r, g, b, a);
	this->draw(renderer, offset);
}

void Rect::draw(SDL_Renderer* renderer, Point offset) {
	rectangleRGBA(renderer, this->tL - offset, this->bR - offset, rChannel, bChannel, gChannel, aChannel);
}

Point Rect::collideLine(Line &ray) {
	/* No way for a single straight line to intersect a line in more than
	 * two points *except with the stupid inline ones that i'm changing
	 * the whole thing for */
	Point intersect[4] = {Point(), Point(), Point(), Point()};
	Line temp[] = {Line(this->tL, this->tR), Line(this->tR, this->bR), Line(this->bR, this->bL), Line(this->bL, this->tL)};
	Point tempPoint;
	int index = 0;
	for (int i = 0; i < arrayLength; i++) {
		tempPoint = intersectionTest(temp[i], ray);
		if (tempPoint.isReal()) {
			intersect[index] = tempPoint;
			index++;
		}
	}
	if (intersect[0].isReal() && intersect[1].isNull() && intersect[2].isNull()) {
		return intersect[0];
	} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isNull()) {
		return smallerDistance(ray.getOrigin(), intersect[0], intersect[1]);
	} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isReal()) {
		return smallerDistance(ray.getOrigin(),intersect[2], smallerDistance(ray.getOrigin(), intersect[0], intersect[1]));
	}
	return Point(); 
	
}

void Rect::setColorChannels(int r, int g, int b, int a) {
	_setColorChannels(r, g, b, a);
}

Point Rect::getTopLeft() const {
	return this->tL;
}

Point Rect::getTopRight() const {
	return this->tR;
}

Point Rect::getBottomLeft() const {
	return this->bL;
}

Point Rect::getBottomRight() const {
	return this->bR;
}

float Rect::getWidth() {
	return bR.x() - tL.x();
}
float Rect::getHeight() {
	return bR.y() - tL.y();
}

bool Rect::overlap(Rect &other) {
	bool xOver = valueInRange(this->tL.x(), other.tL.x(), other.tL.x() + other.getWidth()) || 
				 valueInRange(other.tL.x(), this->tL.x(), this->bR.x());
	bool yOver = valueInRange(this->tL.y(), other.tL.y(), other.tL.y() + other.getHeight()) || 
				 valueInRange(other.tL.y(), this->tL.y(), this->bR.y());
	return xOver && yOver;
}

SDL_Rect Rect::getSDLRect() {
	SDL_Rect tempRect;
	tempRect.x = tL.x();
	tempRect.y = tL.y();
	tempRect.w = getWidth();
	tempRect.h = getHeight();
	return tempRect;
}

Rect Rect::operator+(const Point &point) {
	return Rect(this->tL + point, this->bR + point);
}
Rect Rect::operator-(const Point &point) {
	return Rect(this->tL - point, this->bR - point);
}

void Rect::operator+=(Point point) {
	this->tL += point;
	this->bR += point;
	this->tR += point;
	this->bL += point;
}

void Rect::operator-=(Point point) {
	*this += point.negate();
}

Rect& Rect::operator=(const Rect &that) {
	tL = that.tL;
	tR = that.tR;
	bL = that.bL;
	bR = that.bR;
	return *this;
}

Point Rect::getCenter() {
	return this->tL + Point(this->getWidth() / 2, this->getHeight() / 2);
}

Point smallerDistance(Point distanceFrom, Point pointA, Point pointB) {
	if (pointA.isReal() && pointB.isNull()) {
		return pointA;
	}
	if (pointA.isNull() && pointB.isReal()) {
		return pointB;
	}
	if (pointA.isNull() && pointB.isNull()) {
		return Point();
	}
	if (distanceFrom.distanceToPoint(pointA) < distanceFrom.distanceToPoint(pointB)) {
		return pointA;
	} 
	if (distanceFrom.distanceToPoint(pointA) > distanceFrom.distanceToPoint(pointB)) {
		return pointB;
	}
	return Point();
}
