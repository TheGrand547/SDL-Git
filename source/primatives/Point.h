#ifndef POINT_H
#define POINT_H
#include<math.h>
#include<iostream>
class Point {
	protected:
		float *xval = NULL;
		float *yval = NULL;
	public:
		Point(float xCoordinate=-1, float yCoordinate=-1);
		Point(const Point &point);
		Point(const Point *point);
		~Point();
		Point operator-(const Point &point);
		Point operator+(const Point &point);
		Point &operator=(const Point &that);
		Point copy() const;
		friend std::ostream &operator<<(std::ostream &output, const Point &point);
		float x() const;
		float y() const;
		float getMagnitude();
		float originDistance();
		float distanceToPoint(Point point);
		float distanceToPoint(float x, float y);
		bool isNull();
		bool isReal();
		bool getNonZero();
		void operator-=(Point delta);
		void operator+=(Point delta);
		void xZero();
		void yZero();
};
#endif
