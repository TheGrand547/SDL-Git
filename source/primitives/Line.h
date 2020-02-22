#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "Point.h"
#include "../MyBase.h"
#include "../essential/random.h"
#include "../essential/util.h"

typedef Uint8 uint8_t;

class Line: public MyBase {
	/* Represents a line in the form, ax+by=c, bounded by the points A and B */
	private:
		float minX, maxX, minY, maxY;
		Point originPoint, endingPoint;
	public:	
		Line(Point pointA = Point(), Point pointB = Point(), uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF);
		~Line();
		Line(const Line &line);
		Line& operator=(const Line& that);
		bool isPointOnThisLine(Point point) const;
		bool collidePoint(const Point point) const;
		void operator+=(const Point b);
		void operator-=(const Point b);
		Line operator+(const Point b) const;
		Line operator-(const Point b) const;
		float getAx() const;
		float getBy() const;
		float getC() const;
		Point getOrigin() const;
		Point getEnd() const;
		Point midPoint() const;
		Point intersectionPoint(const Line other) const;
		friend std::ostream& operator<<(std::ostream& output, const Line &line);
		void drawLine(SDL_Renderer* renderer, Point offset = Point(0, 0));
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
};
