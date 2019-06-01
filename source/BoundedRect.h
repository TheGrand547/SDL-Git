#pragma once
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/PointDelta.h"

/* TODO: Check if this class even needs to exsist */
class BoundedRect : public Rect {
	public: 
		float xMin, yMin, xMax, yMax;
		BoundedRect(Point pointA, Point pointB, float xMin, float yMin, float xMax, float yMax) : Rect(pointA, pointB) {
			this->xMin = xMin;
			this->xMax = xMax;
			this->yMin = yMin;
			this->yMax = yMax;
		}
		
		BoundedRect(Rect rect, float xMin, float yMin, float xMax, float yMax) : Rect(rect) {
			this->xMin = xMin;
			this->xMax = xMax;
			this->yMin = yMin;
			this->yMax = yMax;
		}
		
		BoundedRect(BoundedRect &rect) : Rect(rect) {
			this->xMin = rect.xMin;
			this->xMax = rect.xMax;
			this->yMin = rect.yMin;
			this->yMax = rect.yMax;
		}
		
		~BoundedRect() {}
	
		Rect operator+(Point &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(this->xMin)) || (int(this->bR.x() + delta.x()) > int(this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(this->yMin)) || (int(this->bR.y() + delta.y()) > int(this->yMax))) {
				delta.yZero();
			}
			Rect newRect = Rect(this->tL + delta, this->bR + delta);
			return newRect;
		}
		
		Rect operator+(PointDelta &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(this->xMin)) || (int(this->bR.x() + delta.x()) > int(this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(this->yMin)) || (int(this->bR.y() + delta.y()) > int(this->yMax))) {
				delta.yZero();
			}
			Rect newRect = Rect(this->tL + delta, this->bR + delta);
			return newRect;
		}
		
		void operator+=(Point &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(this->xMin)) || (int(this->bR.x() + delta.x()) > int(this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(this->yMin)) || (int(this->bR.y() + delta.y()) > int(this->yMax))) {
				delta.yZero();
			}
			Rect::operator+=(delta);
		}
};
