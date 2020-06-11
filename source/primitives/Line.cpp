#include "Line.h"

Line::Line(Point pointA, Point pointB, uint8_t r, uint8_t g, uint8_t b, uint8_t a) : originPoint(pointA), endingPoint(pointB) {
	if (pointA.isNull()) {
		this->originPoint = Point(0, 0);
	}
	if (pointB.isNull()) {
		this->endingPoint = Point(0, 0);
	}
	setColorChannels(r, g, b, a);
}

Line::~Line() {}

Line::Line(const Line& line) : originPoint(line.originPoint), endingPoint(line.endingPoint) {
	orderPoints(this->originPoint, this->endingPoint);
}

Line& Line::operator=(const Line& that) {
	this->originPoint = that.originPoint;
	this->endingPoint = that.endingPoint;
	orderPoints(this->originPoint, this->endingPoint);
	return *this;
}

bool Line::isCollinear(const Line& other) const {
	/* True -> This line IS on the same unbounded line
	 * False -> This line IS NOT on the same unbounded line
	 */
	if (this->isParallel(other)) {
		return std::abs(other.getC() * this->getBy() - this->getC() * other.getBy()) < 0.00001;
	}
	return false;
}

bool Line::isParallel(const Line& other) const {
	/* True -> This line IS parallel to other
	 * False -> This line IS NOT parallel to other */
	return std::abs((other.getAx() * this->getBy()) - (this->getAx() * other.getBy())) < 0.0001;
}

bool Line::isOrthogonal(const Line& other) const {
	return std::abs(this->getVector() * other.getVector()) < 0.0001;
}

bool Line::isPointOnThisLine(const Point& point) const {
	double minX, maxX, minY, maxY;
	mMax(this->originPoint.x, this->endingPoint.x, minX, maxX);
	mMax(this->originPoint.y, this->endingPoint.y, minY, maxY);
	return valueInRange(point.x, minX, maxX) && valueInRange(point.y, minY, maxY);
}

bool Line::collidePoint(const Point& point) const {
	return this->isPointOnThisLine(point);
}

void Line::operator+=(const Point& b) {
	*this = Line(this->originPoint + b, this->endingPoint + b);
}

void Line::operator-=(const Point& b) {
	*this += b.negate();
}

Line Line::operator+(const Point& b) const {
	return Line(this->originPoint + b, this->endingPoint + b);
}

Line Line::operator-(const Point& b) const {
	return Line(this->originPoint - b, this->endingPoint - b);
}
	
double Line::getAx() const { 
	return double(this->endingPoint.y - this->originPoint.y);
}

double Line::getBy() const { 
	return double(this->originPoint.x - this->endingPoint.x);
}

double Line::getC() const { 
	return double((this->getAx() * this->originPoint.x + (this->getBy() * this->originPoint.y)));
}

Point Line::getEnd() const {
	return this->endingPoint;
}

Point Line::getOrigin() const {
	return this->originPoint;
}

Point Line::getUnitVector() const {
	return this->getVector().getUnitVector();
}

Point Line::getVector() const {
	return this->endingPoint - this->originPoint;
}

Point Line::midPoint() const {
	return (this->endingPoint + this->originPoint) / 2;
}

std::ostream& operator<<(std::ostream& output, const Line& line) {
	output << line.getOrigin() << " -> " << line.getEnd();
	return output;
}

void Line::drawLine(SDL_Renderer* renderer, Point offset) {
	aalineRGBA(renderer, this->originPoint - offset, this->endingPoint - offset, rChannel, gChannel, bChannel, aChannel);
}				

void Line::setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
	setColorChannels(red, green, blue, alpha);
}

Point Line::intersectionPoint(const Line& other) const {
	double delta = (this->getAx() * other.getBy()) - (this->getBy() * other.getAx());
	if (delta == 0) {
		return Point();
	}
	double x = ((this->getC() * other.getBy()) - (this->getBy() * other.getC())) / delta;
	double y = ((this->getAx() * other.getC()) - (this->getC() * other.getAx())) / delta;
	Point newPoint = Point(x, y);
	if (this->collidePoint(newPoint) && other.collidePoint(newPoint)) {
		return newPoint;
	}
	return Point();
}

Line Line::operator*(const double& delta) const {
	return Line(this->getOrigin(), this->getOrigin() + this->getVector() * delta);
}

Line Line::operator/(const double& delta) const {
	return Line(this->getOrigin(), this->getVector() / delta);
}

Line operator*(const double& delta, const Line& line) {
	return line * delta;
}

Line operator/(const double& delta, const Line& line) {
	assert(delta != 0);
	return line / delta;
}

bool Line::shareNoPoints(const Line& other) const {
	return this->originPoint != other.originPoint && this->originPoint != other.endingPoint &&
			this->endingPoint != other.originPoint && this->endingPoint != other.endingPoint;
}
