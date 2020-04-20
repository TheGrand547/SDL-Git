#pragma once
#include "../essential/util.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"
#include<iostream>
#include<cassert>

#define CORNERS(ptr) Point corners ## ptr[4]; \
				ptr->getCorners(corners ## ptr);

class Rect: public MyBase {
	protected:
		Point topLeft, heightVector, widthVector;
		void getCorners(Point array[4]) const;
	public:
		Rect();
		Rect(Point topLeft, Line widthVector, Line heightVector);
		Rect(Point topLeft, Point widthVector, Point heightVector);
		Rect(Line side1, Line side2);
		Rect(Point position, double width, double height);
		Rect(Point topLeft, Point bottomRight);
		Rect(const Rect& that);
		Rect(double x, double y, double width, double height);
		~Rect();
		Rect getBoundingRect() const;
		Rect& operator=(const Rect& that);
		Rect operator+(const Point& point);
		Rect operator-(const Point& point);
		bool doesLineCollide(const Line& ray) const;
		bool operator==(const Rect& rect) const;
		bool overlap(const Rect& other) const;
		double getHeight() const;
		double getOriginDistance() const;
		double getWidth() const;
		int numberOfCollisions(const Line& line) const;
		Point collideLine(const Line& ray) const;
		Point getBottomLeft() const;
		Point getBottomRight() const;
		Point getCenter() const;
		Point getTopLeft() const;
		Point getTopRight() const;
		SDL_Rect getSDLRect() const;
		void draw(SDL_Renderer* renderer, Point offset);
		void operator+=(const Point& point);
		void operator-=(const Point& point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};
