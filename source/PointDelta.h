#pragma once
#include<math.h>
#include "primatives/Point.h"
class PointDelta : public Point {
	private:
		float *xmin, *ymin;
	public:
		PointDelta() {
			this->xmin = NULL;
			this->ymin = NULL;
		}
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
			if (this->getMagnitude() > this->getMaxMagnitude()) {
				float tempFloat = calcAngle(*this);
				*this->xval = this->getXMin() * cos(tempFloat);
				*this->yval = -this->getYMin() * sin(tempFloat);
			}
		}
		
		float getMaxMagnitude() {
			return sqrt((pow(*xmin, 2) + pow(*ymin, 2)));
		}
		
		float getXMin() {
			return *(this->xmin);
		}
		
		float getYMin() {
			return *(this->ymin);
		}
		
		void operator-=(Point delta) {
			Point::operator-=(delta);
			reduceToBounds();
		}
		
		void operator+=(Point delta) {
			Point::operator+=(delta);
			reduceToBounds();
		}
		
		PointDelta operator/(const float &num) {
			return PointDelta((*this->xval)/num, (*this->yval)/num, *this->xmin, *this->ymin);
		}
};
