#pragma once
#include<math.h>
#include "Point.h"

class PointDelta : public Point {
	private:
		double magnitude;
	public:
		PointDelta();
		PointDelta(double xval, double yval, double magnitude);
		PointDelta(Point point, double magnitude);
		PointDelta(const PointDelta& that);
		~PointDelta();
		PointDelta& operator=(const PointDelta& that);
		PointDelta operator/(const double& num);
		PointDelta operator*(const double& num);
		PointDelta onlyX();
		PointDelta onlyY();
		PointDelta negate();
		bool operator>(const int& val);
		bool operator<(const int& val);
		double calcAngle(Point point);
		double getMagnitude();
		Point getXPoint();
		Point getYPoint();
		void reduceToBounds();
		void operator-=(Point delta);
		void operator+=(Point delta);
		void setMagnitude(double magnitude);
};
