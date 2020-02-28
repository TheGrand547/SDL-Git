#include "Rect.h"

Rect::Rect() : topLeft(0, 0), heightVector(0, 0), widthVector(0, 0) {}

Rect::Rect(Point topLeft, Line widthVector, Line heightVector) : topLeft(topLeft), 
			heightVector(heightVector.getUnitVector()), widthVector(widthVector.getUnitVector()) {
	// Point and two magnitude vectors
}

Rect::Rect(Line side1, Line side2){
	// Two Lines that make up sides of a rectangle, and hopefully touch 
	// but I'm not going to think about testing for that at this point
	if (side1.isOrthogonal(side2)) { // Ideal
		this->topLeft = side1.getOrigin();
		this->widthVector = side1.getVector();
		this->heightVector = side2.getVector();
	} else if (side1.isParallel(side2)) { // Not awful
		this->topLeft = side1.getOrigin();
		this->heightVector = side1.getVector();
		float distance1 = side1.getOrigin().distanceToPoint(side2.getOrigin());
		float distance2 = side1.getOrigin().distanceToPoint(side2.getEnd());
		if (distance1 > distance2) {
			this->widthVector = Line(side1.getOrigin(), side2.getEnd()).getVector();
		} else {
			this->widthVector = Line(side1.getOrigin(), side2.getOrigin()).getVector();
		}
	} else { // shit
		std::cout << "Undefined behavior" << std::endl;
	}
}

Rect::Rect(Point topLeft, Point bottomRight) {
	// Constructor for a standard, coordinate system orthogonal rectangle
	orderPoints(topLeft, bottomRight);
	this->topLeft = topLeft;
	heightVector = Point(0, bottomRight.y() - topLeft.y());
	widthVector = Point(bottomRight.x() - topLeft.x(), 0);
}

Rect::Rect(float x, float y, float width, float height) {
	*this = Rect(Point(x, y), width, height);
}

Rect::Rect(Point position, float width, float height) {
	*this = Rect(position, position + Point(width, height));
}

Rect::Rect(const Rect& that) {
}

Rect::~Rect() {}

void Rect::superDraw(SDL_Renderer* renderer, Point offset) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	this->setColorChannels(r, g, b, a);
	this->draw(renderer, offset);
}

void Rect::draw(SDL_Renderer* renderer, Point offset) {
	/*
	rectangleRGBA(renderer, Point(this->xpos, this->ypos) - offset, 
					Point(this->xpos + this->width, this->ypos + this->height) - offset, 
					rChannel, bChannel, gChannel, aChannel);*/
}

bool Rect::doesLineCollide(const Line& ray) const {
	/* True - the Line DOES collide with this rect
	 * False - the Line DOES NOT collide with this rect */
	/*
	Point topleft = Point(this->xpos, this->ypos);
	Point topright = Point(this->xpos + this->width, this->ypos);
	Point bottomleft = Point(this->xpos, this->ypos + this->height);
	Point bottomright = Point(this->xpos + this->width, this->ypos + this->height);
	Line temp[] = {Line(topleft, topright), Line(topright, bottomright), Line(bottomright, bottomleft), Line(bottomleft, topleft)};
	for (Line line: temp) {
		if (line.intersectionPoint(ray).isReal()) {
			return true;
		}
	}*/
	return false;
}

Point Rect::collideLine(const Line& ray) const {
	/* Returns the point where the line intersects the rect, if it doesn't intersect it returns a null point */
	/*
	Point intersect[] = {Point(), Point(), Point(), Point()};
	Point topleft = Point(this->xpos, this->ypos);
	Point topright = Point(this->xpos + this->width, this->ypos);
	Point bottomleft = Point(this->xpos, this->ypos + this->height);
	Point bottomright = Point(this->xpos + this->width, this->ypos + this->height);
	Line temp[] = {Line(topleft, topright), Line(topright, bottomright), Line(bottomright, bottomleft), Line(bottomleft, topleft)};
	Point tempPoint;
	int index = 0;
	for (Line line: temp) {
		tempPoint = line.intersectionPoint(ray);
		if (tempPoint.isReal()) {
			intersect[index] = tempPoint;
			index++;
		}
	}
	// TODO: Tidy this up
	if (intersect[0].isReal() && intersect[1].isNull() && intersect[2].isNull()) {
		return intersect[0];
	} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isNull()) {
		return smallerDistance(ray.getOrigin(), intersect[0], intersect[1]);
	} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isReal()) {
		return smallerDistance(ray.getOrigin(),intersect[2], smallerDistance(ray.getOrigin(), intersect[0], intersect[1]));
	}
	return Point(); */
	return Point();
}

void Rect::setColorChannels(int r, int g, int b, int a) {
	MyBase::setColorChannels(r, g, b, a);
}

Point Rect::getTopLeft() const {
	return this->topLeft;
}

Point Rect::getTopRight() const {
	return this->topLeft + this->widthVector;
}

Point Rect::getBottomLeft() const {
	return this->topLeft + this->heightVector;
}

Point Rect::getBottomRight() const {
	return this->getBottomLeft() + this->widthVector;
}

float Rect::getWidth() const {
	return this->widthVector.getMagnitude();
}
float Rect::getHeight() const {
	return this->heightVector.getMagnitude();
}

bool Rect::overlap(const Rect& other) const {
	/*
	bool xOver = valueInRange(this->xpos, other.xpos, other.xpos + other.width) || valueInRange(other.xpos, this->xpos, this->xpos + this->width);
	bool yOver = valueInRange(this->ypos, other.ypos, other.ypos + other.height) || valueInRange(other.ypos, this->ypos, this->ypos + this->height);*/
	//return xOver && yOver;
	return false;
}

SDL_Rect Rect::getSDLRect() const {
	SDL_Rect tempRect = {int(this->topLeft.x()), int(this->topLeft.y()), 
						int(this->widthVector.getMagnitude()), int(this->heightVector.getMagnitude())};
	return tempRect;
}

Rect Rect::operator+(const Point& point) {
	return Rect(this->topLeft + point, this->widthVector, this->heightVector);
}

Rect Rect::operator-(const Point& point) {
	return *this + point.negate();
}

void Rect::operator+=(const Point& point) {
	this->topLeft += point;
}

void Rect::operator-=(const Point& point) {
	*this += point.negate();
}

Rect& Rect::operator=(const Rect& that) {
	this->topLeft = that.topLeft;
	this->widthVector = that.widthVector;
	this->heightVector = that.heightVector;
	return *this;
}

Point Rect::getCenter() const {
	return this->topLeft + (this->widthVector + this->heightVector) / 2;
}
