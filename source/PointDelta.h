#pragma once
#include<math.h>
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
		
		PointDelta(const PointDelta &that) : Point(&that){
			this->xmin = new float(*(that.xmin));
			this->ymin = new float(*(that.xmin));
		}
		
		~PointDelta() {
			delete this->xmin;
			delete this->ymin;
		}
		float calcAngle(Point point) {
			if(point.y() != 0 || point.x() != 0)
				 return atan2(0-point.y(), point.x());
			return 0;
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
		
		float getMaxMagnitude() {
			return sqrt(pow((*xmin+*ymin)/2, 2));
		}
		
		float getXMin() {
			return *(this->xmin);
		}
		
		float getYMin() {
			return *(this->ymin);
		}
		
		void operator-=(Point delta) {
			/*
			if (delta.getMagnitude() > this->getMaxMagnitude()) {
				float tempFloat = calcAngle(delta);
				delta = Point(this->getXMin() * cos(tempFloat), -this->getYMin() * sin(tempFloat));
			}*/
			Point::operator-=(delta);
			reduceToBounds();
		}
		
		void operator+=(Point delta) {
			/*/
			if (delta.getMagnitude() > this->getMaxMagnitude()) {
				float tempFloat = calcAngle(delta);
				delta = Point(this->getXMin() * cos(tempFloat), -this->getYMin() * sin(tempFloat));
			}*/
			Point::operator+=(delta);
			reduceToBounds();
		}
		
		PointDelta operator/(const float &num) {
			return PointDelta((*this->xval)/num, (*this->yval)/num, *this->xmin, *this->ymin);
		}
};
