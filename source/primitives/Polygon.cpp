#include "Polygon.h"
#include "Rect.h"

Rect Polygon::getBoundingRect() const {
	double minX(1 / 0.0), minY(1 / 0.0), maxX(-1 / 0.0), maxY(-1 / 0.0);
	for (const Point& point: this->getPoints()) {
		if (point.x() > maxX) maxX = point.x();
		if (point.x() < minX) minX = point.x();
		if (point.y() > maxY) maxY = point.y();
		if (point.y() < minY) minY = point.y();
	}
	return Rect(Point(minX, minY), Point(maxX, maxY));
}
