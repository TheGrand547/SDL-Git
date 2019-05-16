#pragma once
#include<math.h>
#include "primatives/Point.h"

class PointDelta : public Point {
	private:
		float xmin, ymin;
	public:
		PointDelta();
		PointDelta(float xval, float yval, float xMin, float yMin);
		PointDelta(Point point, float xMin, float yMin);
		PointDelta(const PointDelta &that);
		~PointDelta();
		PointDelta& operator=(const PointDelta &that);
		PointDelta operator/(const float &num);
		PointDelta operator*(const float &num);
		PointDelta onlyX();
		PointDelta onlyY();
		bool operator>(const int &val);
		bool operator<(const int &val);
		float calcAngle(Point point);
		float getMaxMagnitude();
		float getXMin();
		float getYMin();
		Point getXPoint();
		Point getYPoint();
		void reduceToBounds();
		void operator-=(Point delta);
		void operator+=(Point delta);
		void setBounds(float xMax, float yMax);
};
