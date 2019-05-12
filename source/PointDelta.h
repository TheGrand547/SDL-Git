#pragma once
#include<math.h>
#include "primatives/Point.h"

class PointDelta : public Point {
	private:
		float *xmin, *ymin;
	public:
		PointDelta() {
			this->xmin = new float(0);
			this->ymin = new float(0);
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
			this->ymin = new float(*(that.ymin));
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
		
		PointDelta& operator=(const PointDelta &that) {
			*this->xval = *that.xval;
			*this->yval = *that.yval;
			*this->xmin = *that.xmin;
			*this->ymin = *that.ymin;
			return *this;
		}
		
		PointDelta operator/(const float &num) {
			return PointDelta((*this->xval) / num, (*this->yval) / num, *this->xmin, *this->ymin);
		}
		
		PointDelta operator*(const float &num) {
			return PointDelta((*this->xval) * num, (*this->yval) * num, (*this->xmin) * num, (*this->ymin) * num);
		}
		
		void setBounds(float xMax, float yMax) {
			*this->xmin = xMax;
			*this->ymin = yMax;
			this->reduceToBounds();
		}
		
		PointDelta onlyX() {
			return PointDelta(*this->xval, 0, *this->xmin, *this->ymin);
		}
		
		PointDelta onlyY() {
			return PointDelta(0, *this->yval, *this->xmin, *this->ymin);
		}
		
		Point getXPoint() {
			return Point(*this->xmin, 0);
		}
		
		Point getYPoint() {
			return Point(0, *this->ymin);
		}
		
		bool operator>(const int &val) {
			if (*this->xval > val || *this->yval > val) {
				return true;
			}
			return false;
		}
		
		bool operator<(const int &val) {
			if (*this->xval < val || *this->yval < val) {
				return true;
			}
			return false;
		}
};
