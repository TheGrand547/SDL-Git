#include "primatives/Point.h"

class BoundedPoint : public Point {
	private:
		float *xMin, *xMax;
		float *yMin, *yMax;
	public:
		BoundedPoint(float xpos, float ypos, float xMin, float xMax, float yMin, float yMax) : Point(xpos, ypos) {
			this->xMin = new float(xMin);
			this->xMax = new float(xMax);
			this->yMin = new float(yMin);
			this->yMax = new float(yMax);
		}
		
		~BoundedPoint() {
			delete this->xMin;
			delete this->xMax;
			delete this->yMin;
			delete this->yMax;
		}
		
		void reduce() {
			*this->xval = (*this->xval < *this->xMin) ? *this->xMin : *this->xval;
			*this->xval = (*this->xval > *this->xMax) ? *this->xMax : *this->xval;
			*this->yval = (*this->yval < *this->yMin) ? *this->yMin : *this->yval;
			*this->yval = (*this->yval > *this->yMax) ? *this->yMax : *this->yval;
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
