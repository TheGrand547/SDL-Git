#include "Rect.h"

#define OUT_OF_BOUNDS Point(-10547, -20547)

// ------------------------------------------------
// ---------------- Constructors ------------------
// ------------------------------------------------

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
		LOG("Undefined behavior in Rect Initialization");
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
	heightVector = Point(0, bottomRight.y - topLeft.y);
	widthVector = Point(bottomRight.x - topLeft.x, 0);
}

Rect::Rect(double x, double y, double width, double height) {
	*this = Rect(Point(x, y), width, height);
}

Rect::Rect(Point position, double width, double height) {
	*this = Rect(position, position + Point(width, height));
}

Rect::Rect(const Rect& that) {
	this->topLeft = that.topLeft;
	this->widthVector = that.widthVector;
	this->heightVector = that.heightVector;
}

Rect::~Rect() {}

// ------------------------------------------------
// ------------- Interface Methods ----------------
// ------------------------------------------------

bool Rect::containsPoint(const Point& point) const {
	return this->numberOfCollisions(Line(point, OUT_OF_BOUNDS)) & 1;
}

bool Rect::doesLineCollide(const Line& ray) const {
	/* True - the Line DOES collide with this rect
	 * False - the Line DOES NOT collide with this rect */
	for (Line line: this->getLines()) {
		if (line.intersectionPoint(ray).isReal()) return true;
	}
	return false;
}

bool Rect::isAxisAligned() const { // Fuck off axis powers
	return (this->heightVector.x == 0 && this->widthVector.y == 0) || (this->heightVector.y == 0 && this->widthVector.x == 0);
}

int Rect::numberOfCollisions(const Line& ray) const {
	int count = 0;
	for (Line line: this->getLines()) {
		if (line.intersectionPoint(ray).isReal()) {
			count++;
		}
	}
	return count;
}

int Rect::numLines() const {
	return 4;
}

int Rect::numPoints() const {
	return 4;
}

Point Rect::collideLine(const Line& ray) const {
	/* Returns the point where the line intersects the rect, if it doesn't intersect it returns a null point */
	Point intersection, tempPoint;
	for (Line line: this->getLines()) {
		tempPoint = line.intersectionPoint(ray);
		if (tempPoint.isReal()) {
			if (intersection.isNull() || tempPoint.distanceToPoint(ray.getOrigin()) < intersection.distanceToPoint(ray.getOrigin())) {
				intersection = tempPoint;
			}
		}
	}
	return intersection;
}

std::vector<Line> Rect::getLines() const {
	std::vector<Line> returnValue;
	std::vector<Point> points = this->getPoints();
	for (int i = 0; i < 4; i++) {
		returnValue.push_back(Line(points[i], points[(i + 1) % 4]));
	}
	return returnValue;
}

std::vector<Point> Rect::getPoints() const {
	return {this->getTopLeft(), this->getTopRight(), this->getBottomRight(), this->getBottomLeft()};
}

// ------------------------------------------------
// ------------ Specialized Methods ---------------
// ------------------------------------------------

void Rect::superDraw(SDL_Renderer* renderer, Point offset) {
	uint8_t r, g, b, a;
	SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
	this->setColorChannels(r, g, b, a);
	this->draw(renderer, offset);
}

void Rect::draw(SDL_Renderer* renderer, Point offset) {
	std::vector<Point> temp = this->getPoints();
	short* x = new short[temp.size()];
	short* y = new short[temp.size()];
	for (Uint i = 0; i < temp.size(); i++) {
		temp[i] -= offset;
		x[i] = temp[i].x;
		y[i] = temp[i].y;
	}
	polygonRGBA(renderer, x, y, temp.size(), this->rChannel, this->bChannel, this->gChannel, this->aChannel);
	delete[] x;
	delete[] y;
}

double Rect::getOriginDistance() const {
	double dist = 0;
	for (Point point: this->getPoints()) {
		double temp = point.originDistance();
		if (temp > dist) {
			dist = temp;
		}
	}
	return dist;
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

SDL_Rect Rect::getSDLRect() const {
	SDL_Rect tempRect = {int(this->topLeft.x), int(this->topLeft.y), 
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
