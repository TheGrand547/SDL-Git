#pragma once
#include "primatives/Point.h"
#include "primatives/Rect.h"
#include "PointDelta.h"

class BoundedRect : public Rect {
	public: 
		float *xMin, *yMin, *xMax, *yMax;
		BoundedRect(Point pointA, Point pointB, float xMin, float yMin, float xMax, float yMax) : Rect(pointA, pointB) {
			this->xMin = new float(xMin);
			this->xMax = new float(xMax);
			this->yMin = new float(yMin);
			this->yMax = new float(yMax);
		}
		
		BoundedRect(Rect rect, float xMin, float yMin, float xMax, float yMax) : Rect(rect) {
			this->xMin = new float(xMin);
			this->xMax = new float(xMax);
			this->yMin = new float(yMin);
			this->yMax = new float(yMax);
		}
		
		BoundedRect(BoundedRect &rect) : Rect(rect) {
			this->xMin = new float(*rect.xMin);
			this->xMax = new float(*rect.xMax);
			this->yMin = new float(*rect.yMin);
			this->yMax = new float(*rect.yMax);
		}
		
		~BoundedRect() {
			delete this->xMin;
			delete this->xMax;
			delete this->yMin;
			delete this->yMax;
		}
		
		Rect operator+(Point &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(*this->xMin)) || (int(this->bR.x() + delta.x()) > int(*this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(*this->yMin)) || (int(this->bR.y() + delta.y()) > int(*this->yMax))) {
				delta.yZero();
			}
			Rect newRect = Rect(this->tL + delta, this->bR + delta);
			return newRect;
		}
		
		Rect operator+(PointDelta &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(*this->xMin)) || (int(this->bR.x() + delta.x()) > int(*this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(*this->yMin)) || (int(this->bR.y() + delta.y()) > int(*this->yMax))) {
				delta.yZero();
			}
			Rect newRect = Rect(this->tL + delta, this->bR + delta);
			return newRect;
		}
		
		void operator+=(Point &point) {
			Point delta = Point(point);
			if ((int(this->tL.x() + delta.x()) < int(*this->xMin)) || (int(this->bR.x() + delta.x()) > int(*this->xMax))) {
				delta.xZero();
			}
			if ((int(this->tL.y() + delta.y()) < int(*this->yMin)) || (int(this->bR.y() + delta.y()) > int(*this->yMax))) {
				delta.yZero();
			}
			Rect::operator+=(delta);
		}
};
