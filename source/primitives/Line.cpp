#include "Line.h"

Line::Line(Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	this->originPoint = Point(pointA);
	this->endingPoint = Point(pointB);
	this->minX = 0.0f;
	this->maxX = 0.0f;
	this->minY = 0.0f;
	this->maxY = 0.0f;
	mMax(pointA.x(), pointB.x(), this->minX, this->maxX);
	mMax(pointA.y(), pointB.y(), this->minY, this->maxY);
	setColorChannels(r, g, b, a);
}

Line::~Line() {}

Line::Line(const Line& line) {
	this->originPoint = Point(line.originPoint);
	this->endingPoint = Point(line.endingPoint);
	this->minX = 0.0f;
	this->maxX = 0.0f;
	this->minY = 0.0f;
	this->maxY = 0.0f;
	mMax(originPoint.x(), endingPoint.x(), this->minX, this->maxX);
	mMax(originPoint.y(), endingPoint.y(), this->minY, this->maxY);
}

Line& Line::operator=(const Line& that) {
	this->originPoint = that.originPoint;
	this->endingPoint = that.endingPoint;
	this->minX = 0.0f;
	this->maxX = 0.0f;
	this->minY = 0.0f;
	this->maxY = 0.0f;
	mMax(this->originPoint.x(), this->endingPoint.x(), this->minX, this->maxX);
	mMax(this->originPoint.y(), this->endingPoint.y(), this->minY, this->maxY);
	return *this;
}

bool Line::isCollinear(const Line other) const {
	/* True -> This line is on the same plane
	 * False -> This line is not on the same plane
	 */
	if (this->isParallel(other)) {
		return std::abs(other.getC() / other.getBy() - this->getC() / this->getBy()) < 0.00001;
	}
	return false;
}

bool Line::isParallel(const Line other) const {
	/* True -> This line IS parallel to other
	 * False -> This line IS NOT parallel to other */
	 
	Point myVector = this->getUnitVector();
	Point otherVector = other.getUnitVector();
	return myVector == otherVector;
	//return std::abs((other.getAx() / other.getBy()) - (this->getAx() / this->getBy())) < 0.0001;
}

bool Line::isPointOnThisLine(const Point point) const {
	if (valueInRange(point.x(), this->minX, this->maxX) && valueInRange(point.y(), this->minY, this->maxY)) {
		return true;
	}
	return false;
}

bool Line::collidePoint(const Point point) const {
	return valueInRange(point.x(), this->minX, this->maxX) && valueInRange(point.y(), this->minY, this->maxY);
}

void Line::operator+=(const Point b) {
	*this = Line(this->originPoint + b, this->endingPoint + b);
}

void Line::operator-=(const Point b) {
	*this += b.negate();
}

Line Line::operator+(const Point b) const {
	return Line(this->originPoint + b, this->endingPoint + b);
}

Line Line::operator-(const Point b) const {
	return Line(this->originPoint - b, this->endingPoint - b);
}
	
float Line::getAx() const { 
	return float(this->endingPoint.y() - this->originPoint.y());
}

float Line::getBy() const { 
	return float(this->originPoint.x() - this->endingPoint.x());
}

float Line::getC() const { 
	return float((this->getAx() * this->originPoint.x()) + (this->getBy() * this->originPoint.y()));
}

Point Line::getEnd() const {
	return this->endingPoint;
}

Point Line::getOrigin() const {
	return this->originPoint;
}

Point Line::getUnitVector() const {
	return (this->endingPoint - this->originPoint).getUnitVector();
}

Point Line::midPoint() const {
	return Point(this->originPoint.x() + this->endingPoint.x(), this->originPoint.y() + this->endingPoint.y()) / 2;
}

std::ostream& operator<<(std::ostream &output, const Line &line) {
	output << line.getOrigin() << " -> " << line.getEnd();
	return output;
}

void Line::drawLine(SDL_Renderer* renderer, Point offset) {
	aalineRGBA(renderer, this->originPoint - offset, this->endingPoint - offset, rChannel, gChannel, bChannel, aChannel);
}				

void Line::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	setColorChannels(red, green, blue, alpha);
}

Point Line::intersectionPoint(const Line other) const {
	float delta = (this->getAx() * other.getBy()) - (this->getBy() * other.getAx());
	if (delta == 0) {
		return Point();
	}
	float x = ((this->getC() * other.getBy()) - (this->getBy() * other.getC())) / delta;
	float y = ((this->getAx() * other.getC()) - (this->getC() * other.getAx())) / delta;
	Point newPoint = Point(x, y);
	if (this->collidePoint(newPoint) && other.collidePoint(newPoint)) {
		return newPoint;
	}
	return Point();
}
