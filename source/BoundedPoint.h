#pragma once
#include "primatives/Point.h"

class BoundedPoint : public Point {
	private:
		float *xMin, *xMax;
		float *yMin, *yMax;
	public:
		BoundedPoint() : Point() {
			this->xMin = new float(0);
			this->xMax = new float(0);
			this->yMin = new float(0);
			this->yMax = new float(0);
		}
		BoundedPoint(float xpos, float ypos, float xMin, float yMin, float xMax, float yMax) : Point(xpos, ypos) {
			this->xMin = new float(xMin);
			this->xMax = new float(xMax);
			this->yMin = new float(yMin);
			this->yMax = new float(yMax);
		}
		
		BoundedPoint(Point pos, float xMin, float yMin, float xMax, float yMax) : Point(pos) {
			this->xMin = new float(xMin);
			this->xMax = new float(xMax);
			this->yMin = new float(yMin);
			this->yMax = new float(yMax);
		}
		
		BoundedPoint(const BoundedPoint &other) : Point(*other.xval,*other.yval){
			this->xMin = new float(*other.xMin);
			this->xMax = new float(*other.xMax);
			this->yMin = new float(*other.yMin);
			this->yMax = new float(*other.yMax);
		}
		
		BoundedPoint &operator=(BoundedPoint &other){
			this->xval = new float(*other.xval);
			this->yval = new float(*other.yval);
			this->xMin = new float(*other.xMin);
			this->xMax = new float(*other.xMax);
			this->yMin = new float(*other.yMin);
			this->yMax = new float(*other.yMax);
			return *this;
		}
		
		~BoundedPoint() {	
			delete this->xMin;
			delete this->xMax;
			delete this->yMin;
			delete this->yMax;
		}
		
		void reduce() {
			*this->xval = (*this->xval <= *this->xMin) ? *this->xMin : *this->xval;
			*this->xval = (*this->xval >= *this->xMax) ? *this->xMax : *this->xval;
			*this->yval = (*this->yval <= *this->yMin) ? *this->yMin : *this->yval;
			*this->yval = (*this->yval >= *this->yMax) ? *this->yMax : *this->yval;
		}
		
		void operator+=(Point delta) {
			Point::operator+=(delta);
			reduce();
		}
		
		void operator-=(Point delta) {
			Point::operator-=(delta);
			reduce();
		}
	
};
