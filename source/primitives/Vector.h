#ifndef VECTOR_H
#define VECTOR_H
#include "Point.h"
#include<math.h>

class Vector: public Point {
	public:
		Vector(float angle = 0);
		Vector(float x, float y);
		~Vector();
		float dot(const Vector other);
		float operator*(const Vector& other);
		Vector operator*(const double& num); 
		Vector operator/(const double& num);
		friend Vector operator*(const double& num, Vector& vec);
		float magnitude() const;
		float angleBetween(const Vector other);
};
#endif 
