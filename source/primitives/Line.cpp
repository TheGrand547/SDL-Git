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

Line::Line(Point* pointA, Point* pointB) {
	this->originPoint = Point(pointA);
	this->endingPoint = Point(pointB);
	this->minX = 0.0f;
	this->maxX = 0.0f;
	this->minY = 0.0f;
	this->maxY = 0.0f;
	mMax(pointA->x(), pointB->x(), this->minX, this->maxX);
	mMax(pointA->y(), pointB->y(), this->minY, this->maxY);
}

Line::~Line() {}

Line::Line(const Line &line) {
	this->originPoint = Point(line.originPoint);
	this->endingPoint = Point(line.endingPoint);
	this->minX = 0.0f;
	this->maxX = 0.0f;
	this->minY = 0.0f;
	this->maxY = 0.0f;
	mMax(originPoint.x(), endingPoint.x(), this->minX, this->maxX);
	mMax(originPoint.y(), endingPoint.y(), this->minY, this->maxY);
}

Line& Line::operator=(const Line &that) {
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


bool Line::isPointOnThisLine(Point point) {
	if (thresholdValueInRange(point.x(), this->minX, this->maxX) && thresholdValueInRange(point.y(), this->minY, this->maxY)) {
		return true;
	}
	return false;
}

bool Line::collidePoint(Point& point) {
	if (thresholdValueInRange(point.x(), this->minX, this->maxX) && thresholdValueInRange(point.y(), this->minY, this->maxY))  {
		return true;
	}
	return false;
}

bool Line::collidePoint(Point* point) {
	return this->isPointOnThisLine(*point);
}

void Line::operator+=(Point b) {
	*this = Line(this->originPoint + b, this->endingPoint + b);
}

void Line::operator-=(Point b) {
	*this += b.negate();
}

Line Line::operator+(Point b) {
	return Line(this->originPoint + b, this->endingPoint + b);
}

Line Line::operator-(Point b){
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

Point Line::getOrigin() const {
	return this->originPoint;
}

Point Line::getEnd() const {
	return this->endingPoint;
}

Point Line::midPoint() {
	return Point(this->originPoint.x() + this->endingPoint.x(), this->originPoint.y() + this->endingPoint.y()) / 2;
}

std::ostream& operator<<(std::ostream &output, const Line &line) {
	output << line.getOrigin() << " -> " << line.getEnd();
	return output;
}

void Line::drawLine(SDL_Renderer* renderer) {
	aalineRGBA(renderer, this->originPoint, this->endingPoint, rChannel, gChannel, bChannel, aChannel);
}		

void Line::drawLine(SDL_Renderer* renderer, Point offset) {
	aalineRGBA(renderer, this->originPoint - offset, this->endingPoint - offset, rChannel, gChannel, bChannel, aChannel);
}				

void Line::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	setColorChannels(red, green, blue, alpha);
}
