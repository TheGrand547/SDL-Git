#pragma once
#include "primatives/Rect.h"

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
		
		~BoundedRect() {
			delete this->xMin;
			delete this->xMax;
			delete this->yMin;
			delete this->yMax;
		}
		
		void operator+=(Point delta) {
			if (this->tL->x() + delta.x() < *this->xMin || this->bR->x() + delta.x() > *this->xMax) {
				delta.xZero();
			}
			if (this->tL->y() + delta.y() < *this->yMin || this->bR->y() + delta.y() > *this->yMax) {
				delta.yZero();
			}
			Rect::operator+=(delta);
		}
		
		void operator-=(Point delta) {
			this->operator+=(delta.negate());
		}
};
