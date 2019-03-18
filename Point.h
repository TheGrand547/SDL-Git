#include<math.h>
#pragma once

using namespace std;
class Point {
private:
    float *xval = NULL;
    float *yval = NULL;
public:
	Point(float xCoordinate=-1, float yCoordinate=-1) {
		xval = new float(xCoordinate);
		yval = new float(yCoordinate);
	}

	~Point() {
		delete this->xval;
		delete this->yval;
		
	}
	
	Point(const Point &point) {
		xval = new float;
		yval = new float;
		*xval = *point.xval;
		*yval = *point.yval;
	}
	Point(const Point *point) {
		xval = new float(*(point->xval));
		yval = new float(*(point->yval));
	}

	float x() const {
		return *xval;
	}
	
	float y() const {
		return *yval;
	}
	
	float originDistance() {return distanceToPoint(0,0);}

	Point operator-(const Point &point) {
		Point temp;
		*(temp.xval) = *(this->xval) - *(point.xval);
		*(temp.yval) = *(this->yval) - *(point.yval);
		return temp;
	}
	Point operator+(const Point &point) {
		Point temp;
		*(temp.xval) = *(this->xval) + *(point.xval);
		*(temp.yval) = *(this->yval) + *(point.yval);
		return temp;
		
	}

   	void operator-=(Point delta) {
        	*(this->xval) -= delta.x();
        	*(this->yval) -= delta.y();
    	}
	void operator+=(Point delta) {
        	*(this->xval) += delta.x();
        	*(this->yval) += delta.y();
	}
	
	Point &operator=(const Point &that) {
		*xval = that.x();
		*yval = that.y();
		return *this;
	}
	
	friend ostream &operator<<(ostream &output, const Point &point) {
		output << "(" << point.x() << ", " << point.y() << ")";
		return output;
	}

	float distanceToPoint(Point point) {
		float dx = *xval - point.x();
		float dy = *yval - point.y();
		return sqrt(dx*dx + dy*dy);
	}

	float distanceToPoint(float x, float y) {
		float dx = *xval - x;
		float dy = *yval - y;
		return sqrt(dx * dx + dy * dy);
	}

	bool isNull() {
		if (*xval == -1 && *yval == -1)
			return true;
		return false;
	}
	
	bool isReal() {
		return !isNull();
	}
	
	Point copy() const {
		return Point(*(this->xval),*(this->yval));
	}
};
