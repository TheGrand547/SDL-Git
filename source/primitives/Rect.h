#pragma once
#ifndef RECT_H
#define RECT_H
#include<cassert>
#include<iostream>
#include "../essential/util.h"
#include "../essential/log.h"
#include "Line.h"
#include "Point.h"
#include "Polygon.h"

typedef uint Uint;

class Rect: public Polygon {
	protected:
		Point topLeft, heightVector, widthVector;
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
		Rect& operator=(const Rect& that);
		Rect operator+(const Point& point) const;
		Rect operator-(const Point& point) const;
		Rect operator*(const double& value) const;
		
		bool isReal() const override;
		bool containsPoint(const Point& point) const override;
		bool doesLineCollide(const Line& ray) const override;
		bool isAxisAligned() const override;
		int numberOfCollisions(const Line& line) const override;
		int numLines() const override;
		int numPoints() const override;
		Point collideLine(const Line& ray) const override;
		Point getCenter() const override;
		std::vector<Line> getLines() const override;
		std::vector<Point> getPoints() const override;
		void draw(SDL_Renderer* renderer, Point offset) override;
		
		double getHeight() const;
		double getOriginDistance() const;
		double getWidth() const;
		Point getBottomLeft() const;
		Point getBottomRight() const;
		Point getTopLeft() const;
		Point getTopRight() const;
		SDL_Rect getSDLRect() const;
		void operator+=(const Point& point);
		void operator-=(const Point& point);
		void operator*=(const double& value);
		void setCenter(const Point& point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};

Rect operator+(const Point& point, const Rect& rect);
Rect operator-(const Point& point, const Rect& rect);
Rect operator*(const double& value, const Rect& rect);
#endif
