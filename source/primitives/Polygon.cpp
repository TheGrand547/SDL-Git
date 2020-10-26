#include "Polygon.h"
#include "Rect.h"

#define OUT_OF_BOUNDS Point(-10547, -20547)

Polygon::~Polygon() {}

bool Polygon::operator==(const Polygon& other) const {
	// If they don't have the same amount of points they can't be the same
	if (this->numPoints() != other.numPoints()) return false;
	// Get the individual points
	std::vector<Point> myArray = this->getPoints();
	std::vector<Point> otherArray = other.getPoints();
	// Iterate through the points
	for (const Point& pointA: myArray) {
		bool flag = false;
		for (const Point& pointB: otherArray) {
			if (pointA == pointB) {
				flag = true;
				break;
			}
		}
		if (!flag) return false;
	}
	return true;
}

bool Polygon::containsPoint(const Point& point) const {
	return this->numberOfCollisions(Line(point, OUT_OF_BOUNDS)) & 1;
}

bool Polygon::doesLineCollide(const Line& ray) const {
	// True - the Line DOES collide with this polygon
	// False - the Line DOES NOT collide with this polygon
	for (Line line: this->getLines()) if (line.intersectionPoint(ray).isReal()) return true;
	return false;
}

bool Polygon::isAxisAligned() const {
	return false;
}

bool Polygon::overlap(const Polygon& that) const {
	// It will be more efficient to check fewer points in the later stages of the algorithm
	if (this->numPoints() > that.numPoints()) return that.overlap(*this);
	// Get the bounding rectangles of each polygon
	Rect me = this->getBoundingRect();
	Rect other = that.getBoundingRect();
	// Shorthand variables to store topleft coordinates of both bounding rectangles
	double myXPos = me.getTopLeft().x, myYPos = me.getTopLeft().y;
	double otXPos = other.getTopLeft().x, otYPos = other.getTopLeft().y;
	// Check if the bounding rectangles overlap
	bool xOver = valueInRange(myXPos, otXPos, otXPos + other.getWidth()) || valueInRange(otXPos, myXPos, myXPos + me.getWidth());
	bool yOver = valueInRange(myYPos, otYPos, otYPos + other.getHeight()) || valueInRange(otYPos, myYPos, myYPos + me.getHeight());
	// If the bounding rectangles don't overlap, then the polygons can't overlap
	if (!(xOver && yOver)) return false;
	// If the bounding rectangles DO overlap, and both polygons are THEIR OWN bounding rectangles, they must overlap
	if (this->isAxisAligned() && that.isAxisAligned()) return true;

	for (Line line: this->getLines()) {
		if (that.doesLineCollide(line)) return true;
	}
	// If the bounding rectanlges DO overlap, AND none of the lines overlap AND the polygons DO overlap, then at LEAST one point is inside of the other
	for (Point point: that.getPoints()) {
		// Even-odd rule, if the number of collisions with a polygon of a line is odd, then the starting point IS inside the polygon
		if (this->numberOfCollisions(Line(point, OUT_OF_BOUNDS)) & 1) return true;
	}
	for (Point point: this->getPoints()) {
		// Even-odd rule, if the number of collisions with a polygon of a line is odd, then the starting point IS inside the polygon
		if (that.numberOfCollisions(Line(point, OUT_OF_BOUNDS)) & 1) return true;
	}
	// Default case where the bounding rectangles overlap but no points are inside the other polygon
	return false;
}

int Polygon::numberOfCollisions(const Line& ray) const {
	int count = 0;
	for (Line line: this->getLines()) {
		if (line.intersectionPoint(ray).isReal()) {
			count++;
		}
	}
	return count;
}

Point Polygon::collideLine(const Line& ray) const {
	// Returns the point where the line intersects the rect, if it doesn't intersect it returns a null point
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

Rect Polygon::getBoundingRect() const {
	double minX(1 / 0.0), minY(1 / 0.0), maxX(-1 / 0.0), maxY(-1 / 0.0);
	for (const Point& point: this->getPoints()) {
		if (point.x > maxX) maxX = point.x;
		if (point.x < minX) minX = point.x;
		if (point.y > maxY) maxY = point.y;
		if (point.y < minY) minY = point.y;
	}
	return Rect(Point(minX, minY), Point(maxX, maxY));
}

void Polygon::draw(Renderer renderer) {
	this->draw(renderer.renderer, renderer.offset);
}

void Polygon::draw(SDL_Renderer* renderer, Point offset) {
	std::vector<Point> temp = this->getPoints();
	short* x = new short[this->numPoints()];
	short* y = new short[this->numPoints()];
	for (int i = 0; i < this->numPoints(); i++) {
		temp[i] -= offset;
		x[i] = temp[i].x;
		y[i] = temp[i].y;
	}
	polygonRGBA(renderer, x, y, temp.size(), this->r, this->g, this->b, this->a);
	delete[] x;
	delete[] y;
}

std::ostream& operator<<(std::ostream& output, const Polygon& poly) {
	for (Point point: poly.getPoints()) {
		output << point << " ";
	}
	return output;
}
