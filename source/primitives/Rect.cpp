#include "Rect.h"

Rect::Rect() {
	this->xpos = 0;
	this->ypos = 0;
	this->width = 0;
	this->height = 0;
}

Rect::Rect(Point topLeft, Point bottomRight) {
	this->xpos = topLeft.x();
	this->ypos = topLeft.y();
	this->width = bottomRight.x() - topLeft.x();
	this->height = bottomRight.y() - topLeft.y();
}

Rect::Rect(float x, float y, int width, int height) {
	*this = Rect(Point(x, y), width, height);
}

Rect::Rect(Point position, int width, int height) {
	*this = Rect(position, position + Point(width, height));
}

Rect::Rect(const Rect& that) {
	this->xpos = that.xpos;
	this->ypos = that.ypos;
	this->width = that.width;
	this->height = that.height;
}

Rect::~Rect() {}

void Rect::superDraw(SDL_Renderer* renderer, Point offset) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	this->setColorChannels(r, g, b, a);
	this->draw(renderer, offset);
}

void Rect::draw(SDL_Renderer* renderer, Point offset) {
	rectangleRGBA(renderer, Point(this->xpos, this->ypos) - offset, Point(this->xpos + this->width, this->ypos + this->height) - offset, rChannel, bChannel, gChannel, aChannel);
}

bool Rect::doesLineCollide(Line& ray) {
	/* True - the Line DOES collide with this rect
	 * False - the Line DOES NOT collide with this rect */
	Point topleft = Point(this->xpos, this->ypos);
	Point topright = Point(this->xpos + this->width, this->ypos);
	Point bottomleft = Point(this->xpos, this->ypos + this->height);
	Point bottomright = Point(this->xpos + this->width, this->ypos + this->height);
	Line temp[] = {Line(topleft, topright), Line(topright, bottomright), Line(bottomright, bottomleft), Line(bottomleft, topleft)};
	Point tempPoint;
	for (int i = 0; i < Rect::arrayLength; i++) {
		tempPoint = temp[i].intersectionPoint(ray);
		if (tempPoint.isReal()) {
			return true;
		}
	}
	return false;
}

Point Rect::collideLine(Line& ray) {
	/* Returns the point where the line intersects the rect, if it doesn't intersect it returns a null point */
	Point intersect[] = {Point(), Point(), Point(), Point()};
	Point topleft = Point(this->xpos, this->ypos);
	Point topright = Point(this->xpos + this->width, this->ypos);
	Point bottomleft = Point(this->xpos, this->ypos + this->height);
	Point bottomright = Point(this->xpos + this->width, this->ypos + this->height);
	Line temp[] = {Line(topleft, topright), Line(topright, bottomright), Line(bottomright, bottomleft), Line(bottomleft, topleft)};
	Point tempPoint;
	int index = 0;
	for (int i = 0; i < Rect::arrayLength; i++) {
		tempPoint = temp[i].intersectionPoint(ray);
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
	MyBase::setColorChannels(r, g, b, a);
}

Point Rect::getTopLeft() const {
	return Point(this->xpos, this->ypos);
}

Point Rect::getTopRight() const {
	return Point(this->xpos + this->width, this->ypos);
}

Point Rect::getBottomLeft() const {
	return Point(this->xpos, this->ypos + this->height);
}

Point Rect::getBottomRight() const {
	return this->getTopLeft() + Point(this->width, this->height);
}

float Rect::getWidth() {
	return this->width;
}
float Rect::getHeight() {
	return this->height;
}

bool Rect::overlap(Rect& other) {
	bool xOver = valueInRange(this->xpos, other.xpos, other.xpos + other.width) || valueInRange(other.xpos, this->xpos, this->xpos + this->width);
	bool yOver = valueInRange(this->ypos, other.ypos, other.ypos + other.height) || valueInRange(other.ypos, this->ypos, this->ypos + this->height);
	return xOver && yOver;
}

SDL_Rect Rect::getSDLRect() {
	SDL_Rect tempRect = {int(this->xpos), int(this->ypos), int(this->width), int(this->height)};
	return tempRect;
}

Rect Rect::operator+(const Point& point) {
	return Rect(Point(this->xpos, this->ypos) + point, Point(this->xpos + this->width, this->ypos + this->height) + point);
}

Rect Rect::operator-(const Point& point) {
	return *this + point.negate();
}

void Rect::operator+=(Point point) {
	this->xpos += point.x();
	this->ypos += point.y();
}

void Rect::operator-=(Point point) {
	*this += point.negate();
}

Rect& Rect::operator=(const Rect& that) {
	this->xpos = that.xpos;
	this->ypos = that.ypos;
	this->width = that.width;
	this->height = that.height;
	return *this;
}

Point Rect::getCenter() {
	return Point(this->xpos, this->ypos) + (Point(this->width, this->height) / 2);
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
