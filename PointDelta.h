#pragma once
#include "Point.h"
class PointDelta : public Point {
	private:
		float *xmin, *ymin;
	public:
		PointDelta(float xval, float yval, float xMin, float yMin) : Point(xval, yval) {
			this->xmin = new float(xMin);
			this->ymin = new float(yMin);
		}
		
		PointDelta(Point point, float xMin, float yMin) : Point(point)  {
			this->xmin = new float(xMin);
			this->ymin = new float(yMin);
		}
		
		PointDelta(const PointDelta &that) {
			this->xmin = new float(*(that.xmin));
			this->ymin = new float(*(that.xmin));
		}
		
		~PointDelta() {
			delete this->xmin;
			delete this->ymin;
		}
		
		void reduceToBounds() {
			if (*xval > *xmin) 
				*xval = *xmin;
			if (*xval < -*xmin)
				*xval = -*xmin;
			if (*yval > *ymin) 
				*yval = *ymin;
			if (*yval < -*ymin)
				*yval = -*ymin;
		}
		
		void operator-=(Point delta) {
			Point::operator-=(delta);
			reduceToBounds();
		}
		
		void operator+=(Point delta) {
			Point::operator+=(delta);
			reduceToBounds();
		}
};
