#include "Rect.h"

Rect::Rect() : topLeft(0, 0), heightVector(0, 0), widthVector(0, 0) {}

Rect::Rect(Point topLeft, Line widthVector, Line heightVector) : topLeft(topLeft), 
			heightVector(heightVector.getVector()), widthVector(widthVector.getVector()) {
	// Point and two magnitude vectors
}

Rect::Rect(Point topLeft, Point widthVector, Point heightVector) : topLeft(topLeft), 
			heightVector(heightVector), widthVector(widthVector) {}

Rect::Rect(Line side1, Line side2) {
	// Two Lines that make up sides of a rectangle, and hopefully touch 
	// but I'm not going to think about testing for that at this point
	assert(side1.isParallel(side2) || side1.isOrthogonal(side2));
	if (side1.isOrthogonal(side2)) { // Ideal
		this->topLeft = side1.getOrigin();
		this->widthVector = side1.getVector();
		this->heightVector = side2.getVector();
	} else if (side1.isParallel(side2)) { // Not awful
		this->topLeft = side1.getOrigin();
		this->heightVector = side1.getVector();
		double distance1 = side1.getOrigin().distanceToPoint(side2.getOrigin());
		double distance2 = side1.getOrigin().distanceToPoint(side2.getEnd());
		if (distance1 > distance2) {
			this->widthVector = Line(side1.getOrigin(), side2.getEnd()).getVector();
		} else {
			this->widthVector = Line(side1.getOrigin(), side2.getOrigin()).getVector();
		}
	} else { // shit
		std::cout << "Undefined behavior" << std::endl;
		return;
	}
	// TODO: Make this not vomit inducing
	Point check[] = {side1.getOrigin(), side1.getEnd(), side2.getOrigin(), side2.getEnd()};
	while (true) {
		Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
		int ctr = 0;
		for (Point g: check) {
			bool f = false;
			for (Point p: ar) {
				if (g == p) {
					f = true;
					break;
				}
			}
			if (!f) {
				//this->widthVector *= -1;
				this->heightVector *= -1;
				break;
			} else {
				ctr++;
			}
		}
		if (ctr > 3) {
			break;
		}
	}
}

Rect::Rect(Point topLeft, Point bottomRight) {
	// Constructor for a standard, coordinate system orthogonal rectangle
	orderPoints(topLeft, bottomRight);
	this->topLeft = topLeft;
	heightVector = Point(0, bottomRight.y() - topLeft.y());
	widthVector = Point(bottomRight.x() - topLeft.x(), 0);
}

Rect::Rect(double x, double y, double width, double height) {
	*this = Rect(Point(x, y), width, height);
}

Rect::Rect(Point position, double width, double height) {
	*this = Rect(position, position + Point(width, height));
}

Rect::Rect(const Rect& that) : MyBase() {
	this->topLeft = that.topLeft;
	this->widthVector = that.widthVector;
	this->heightVector = that.heightVector;
}

Rect::~Rect() {}

void Rect::superDraw(SDL_Renderer* renderer, Point offset) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	this->setColorChannels(r, g, b, a);
	this->draw(renderer, offset);
}

void Rect::draw(SDL_Renderer* renderer, Point offset) {
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	short* x = new short[4];
	short* y = new short[4];
	for (int i = 0; i < 4; i++) {
		ar[i] -= offset;
		x[i] = ar[i].x();
		y[i] = ar[i].y();
	}
	polygonRGBA(renderer, x, y, 4, rChannel, bChannel, gChannel, aChannel);
	delete[] x;
	delete[] y;
}

double Rect::getOriginDistance() const {
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	double dist = 0;
	for (Point point: ar) {
		double temp = point.originDistance();
		if (temp > dist) {
			dist = temp;
		}
	}
	return dist;
}

bool Rect::doesLineCollide(const Line& ray) const {
	/* True - the Line DOES collide with this rect
	 * False - the Line DOES NOT collide with this rect */
	 
	// TODO: should REALLY have a vector or something for this...
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	Line temp[4];
	for (int i = 0; i < 4; i++) {
		temp[i] = Line(ar[i], ar[(i + 1) % 4]);
	}
	for (Line line: temp) {
		if (line.intersectionPoint(ray).isReal()) {
			return true;
		}
	}
	return false;
}

int Rect::numberOfCollisions(const Line& ray) const {
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	Line temp[4];
	int count = 0;
	for (int i = 0; i < 4; i++) {
		temp[i] = Line(ar[i], ar[(i + 1) % 4]);
	}
	for (Line line: temp) {
		if (line.intersectionPoint(ray).isReal()) {
			count++;
		}
	}
	return count;
}

Point Rect::collideLine(const Line& ray) const {
	/* Returns the point where the line intersects the rect, if it doesn't intersect it returns a null point */
	Point intersection, tempPoint;
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	Line temp[4];
	for (int i = 0; i < 4; i++) {
		temp[i] = Line(ar[i], ar[(i + 1) % 4]);
	}
	for (Line line: temp) {
		tempPoint = line.intersectionPoint(ray);
		if (tempPoint.isReal()) {
			if (intersection.isNull() || tempPoint.distanceToPoint(ray.getOrigin()) < intersection.distanceToPoint(ray.getOrigin())) {
				intersection = tempPoint;
			}
		}
	}
	return intersection;
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

double Rect::getWidth() const {
	return this->widthVector.getMagnitude();
}
double Rect::getHeight() const {
	return this->heightVector.getMagnitude();
}

bool Rect::overlap(const Rect& other) const {
	// TODO: Rename these variables something sensible
	bool value = false;
	Rect bound = this->getBoundingRect();
	Rect otherBound = other.getBoundingRect();
	double myX = bound.getTopLeft().x();
	double myY = bound.getTopLeft().y();
	double otherX = otherBound.getTopLeft().x();
	double otherY = otherBound.getTopLeft().y();
	bool xOver = valueInRange(myX, otherX, otherX + otherBound.getWidth()) || valueInRange(otherX, myX, myX + bound.getWidth());
	bool yOver = valueInRange(myY, otherY, otherY + otherBound.getHeight()) || valueInRange(otherY, myY, myY + bound.getHeight());
	if (xOver && yOver) {
		if (bound == *this && other == otherBound) { // If both are right aligned
			value = true;
		} else { // HAHHA
			Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
			int ctr = 0;
			for (int i = 0; i < 4 && !ctr; i++) {
				ctr += other.numberOfCollisions(Line(ar[i], ar[(i + 1) % 4]));
				ctr += other.numberOfCollisions(Line(this->getCenter(), ar[i]));
			}
			if (ctr) {
				value = true;
			}
		}
	}
	return value;
}

bool Rect::operator==(const Rect& other) const {
	Point ar[] = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	Point ar2[] = {other.getTopLeft(), other.getTopRight(), other.getBottomRight(), other.getBottomLeft()};
	for (const Point& pointA: ar) {
		bool flag = false;
		for (const Point& pointB: ar2) {
			if (pointA == pointB) {
				flag = true;
				break;
			}
		}
		if (!flag) {
			return false;
		}
	}
	return true;
}

SDL_Rect Rect::getSDLRect() const {
	SDL_Rect tempRect = {int(this->topLeft.x()), int(this->topLeft.y()), 
						int(this->widthVector.getMagnitude()), int(this->heightVector.getMagnitude())};
	return tempRect;
}

Rect Rect::getBoundingRect() const {
	assert(this->topLeft.isReal());
	double minX(1 / 0.0), minY(1 / 0.0), maxX(-1 / 0.0), maxY(-1 / 0.0);
	CORNERS(this);
	/*
	Point corners[4];// = {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
	this->getCorners(ar);*/
	for (const Point& point: cornersthis) {
		if (point.x() > maxX) maxX = point.x();
		if (point.x() < minX) minX = point.x();
		if (point.y() > maxY) maxY = point.y();
		if (point.y() < minY) minY = point.y();
	}
	return Rect(Point(minX, minY), Point(maxX, maxY));
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
	return (this->topLeft + this->getBottomRight()) / 2;
}

void Rect::getCorners(Point array[4]) const {
	array[0] = this->getTopLeft();
	array[1] = this->getTopRight();
	array[2] = this->getBottomRight();
	array[3] = this->getBottomLeft();
}
