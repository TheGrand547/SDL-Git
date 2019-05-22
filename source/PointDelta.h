#pragma once
#include<math.h>
#include "primitives/Point.h"

class PointDelta : public Point {
	private:
		float magnitude;
	public:
		PointDelta();
		PointDelta(float xval, float yval, float magnitude);
		PointDelta(Point point, float magnitude);
		PointDelta(const PointDelta &that);
		~PointDelta();
		PointDelta& operator=(const PointDelta &that);
		PointDelta operator/(const float &num);
		PointDelta operator*(const float &num);
		PointDelta onlyX();
		PointDelta onlyY();
		PointDelta negate();
		bool operator>(const int &val);
		bool operator<(const int &val);
		float calcAngle(Point point);
		float getMagnitude();
		Point getXPoint();
		Point getYPoint();
		void reduceToBounds();
		void operator-=(Point delta);
		void operator+=(Point delta);
		void setMagnitude(float magnitude);
};
