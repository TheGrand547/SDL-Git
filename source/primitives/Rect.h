#pragma once
#include<cassert>
#include<iostream>
#include "../essential/util.h"
#include "../MyBase.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"

#define CORNERS(ptr, name) Point name[4]; \
				(ptr)->getCorners(name);

class Rect: public Polygon, public MyBase {
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
		Rect getBoundingRect() const override;
		Rect& operator=(const Rect& that);
		Rect operator+(const Point& point);
		Rect operator-(const Point& point);
		bool containsPoint(const Point& point) const override;
		bool doesLineCollide(const Line& ray) const override;
		bool operator==(const Polygon& other) const override;
		bool operator==(const Rect& rect) const;
		bool overlap(const Polygon& other) const override;
		double getHeight() const;
		double getOriginDistance() const;
		double getWidth() const;
		int numberOfCollisions(const Line& line) const override;
		Point collideLine(const Line& ray) const override;
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
