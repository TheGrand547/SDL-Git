#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "Point.h"
#include "../MyBase.h"
#include "../essential/random.h"
#include "../essential/util.h"
typedef Uint8 uint8_t;
bool xBetweenAandB(float x, float a, float b);

class Line: public MyBase{
	/* Represents a line in the form, ax+by=c, bounded by the points A and B */
	private:
		float minX, maxX, minY, maxY;
		Point originPoint, endingPoint;
	public:	
		Line(Point pointA = Point(), Point pointB = Point(), uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF);
		Line(Point* pointA, Point* pointB);
		~Line();
		Line(const Line &line);
		Line& operator=(const Line& that);
		bool isPointOnThisLine(Point point);
		bool collidePoint(Point& point);
		bool collidePoint(Point *point);
		void operator+=(Point b);
		void operator-=(Point b);
		Line operator+(Point b);
		Line operator-(Point b);
		float getAx() const;
		float getBy() const;
		float getC() const;
		Point getOrigin() const;
		Point getEnd() const;
		Point midPoint();
		friend std::ostream& operator<<(std::ostream& output, const Line &line);
		void drawLine(SDL_Renderer* renderer, Point offset = Point(0, 0));
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};

inline Point intersectionTest(Line line1, Line line2) {
	float delta = (line1.getAx() * line2.getBy()) - (line1.getBy() * line2.getAx());
	if (delta == 0) 
		return Point();
	float x = ((line1.getC() * line2.getBy()) - (line1.getBy() * line2.getC())) / delta;
	float y = ((line1.getAx() * line2.getC()) - (line1.getC() * line2.getAx())) / delta;
	Point newPoint = Point(x, y);
	if (line1.collidePoint(newPoint) && line2.collidePoint(newPoint)) {
		return newPoint;
	}
	return Point();
}

inline bool xBetweenAandB(float x, float a, float b) {
	float larger, smaller;
	if (a > b) {
		larger = a;
		smaller = b;
	} else {
		larger = b;
		smaller = a;
	}
	if (larger >= x && smaller <= x) {

		return true;
	}
	return false;
}
