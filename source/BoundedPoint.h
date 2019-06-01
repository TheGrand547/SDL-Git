#pragma once
#include "primitives/Point.h"

class BoundedPoint : public Point {
	private:
		float xMin, xMax;
		float yMin, yMax;
	public:
		BoundedPoint() : Point() {
			this->xMin = 0;
			this->xMax = 0;
			this->yMin = 0;
			this->yMax = 0;
		}
		
		BoundedPoint(float xMax, float yMax) : Point(0, 0) {
			this->xMin = 0;
			this->xMax = xMax;
			this->yMin = 0;
			this->yMax = yMax;
		} 
		
		BoundedPoint(float xpos, float ypos, float xMin, float yMin, float xMax, float yMax) : Point(xpos, ypos) {
			this->xMin = xMin;
			this->xMax = xMax;
			this->yMin = yMin;
			this->yMax = yMax;
		}
		
		BoundedPoint(Point pos, float xMin, float yMin, float xMax, float yMax) : Point(pos) {
			this->xMin = xMin;
			this->xMax = xMax;
			this->yMin = yMin;
			this->yMax = yMax;
		}
		
		BoundedPoint(const BoundedPoint &other) : Point(other.xval, other.yval){
			this->xMin = other.xMin;
			this->xMax = other.xMax;
			this->yMin = other.yMin;
			this->yMax = other.yMax;
		}
		
		BoundedPoint &operator=(BoundedPoint other){
			this->xval = other.xval;
			this->yval = other.yval;
			this->xMin = other.xMin;
			this->xMax = other.xMax;
			this->yMin = other.yMin;
			this->yMax = other.yMax;
			return *this;
		}
		
		~BoundedPoint() {}
		
		void reduce() {
			this->xval = (this->xval <= this->xMin) ? this->xMin : this->xval;
			this->xval = (this->xval >= this->xMax) ? this->xMax : this->xval;
			this->yval = (this->yval <= this->yMin) ? this->yMin : this->yval;
			this->yval = (this->yval >= this->yMax) ? this->yMax : this->yval;
		}
		
		void operator+=(Point delta) {
			Point::operator+=(delta);
			reduce();
		}
		
		void operator-=(Point delta) {
			Point::operator-=(delta);
			reduce();
		}
		
		void zeroX() {
			this->xval = 0;
		}
		
		void zeroY() {
			this->yval = 0;
		}
		
		void maxX() {
			this->xval = this->xMax;
		}
		
		void maxY() {
			this->yval = this->yMax;
		}
		
};
