#pragma once
#ifndef VECTOR_H
#define VECTOR_H
#include "Point.h"
#include<math.h>

class Vector: public Point {
	public:
		Vector(double angle = 0);
		Vector(double x, double y);
		~Vector();
		double dot(const Vector other);
		double operator*(const Vector& other);
		Vector operator*(const double& num); 
		Vector operator/(const double& num);
		friend Vector operator*(const double& num, Vector& vec);
		double magnitude() const;
		double angleBetween(const Vector other);
};
#endif 
