#pragma once
#include<iostream>
#include "../essential/util.h"
#include "../PointDelta.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"

Point smallerDistance(Point distanceFrom, Point pointA, Point pointB);
class Rect: public MyBase{
	protected:
		static const int arrayLength = 4;
		Point tL, tR, bL, bR;
	public:
		Rect();
		Rect(Point topLeft, Point bottomRight);
		Rect(float x, float y, int width, int height);
		Rect(Point position, int width, int height);
		Rect(const Rect &that);
		~Rect();
		void superDraw(SDL_Renderer* renderer, Point offset);
		void draw(SDL_Renderer* renderer, Point offset);
		Point collideLine(Line &ray, Point offset = Point(0, 0));
		void setColorChannels(int r, int g, int b, int a);
		Point getTopLeft() const;
		Point getTopRight() const;
		Point getBottomLeft() const;
		Point getBottomRight() const;
		float getWidth();
		float getHeight();
		bool overlap(Rect &other);
		SDL_Rect getSDLRect();
		Rect operator+(const Point &point);
		Rect operator-(const Point &point);
		void operator+=(Point point);
		void operator-=(Point point);
		Rect &operator=(const Rect &that);
		Point getCenter();
};
