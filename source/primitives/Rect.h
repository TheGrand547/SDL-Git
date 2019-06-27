#pragma once
#include<iostream>
#include "../essential/util.h"
#include "PointDelta.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"

Point smallerDistance(Point distanceFrom, Point pointA, Point pointB);
class Rect: public MyBase{
	protected:
		// TODO: Try and get rid of all stored values except tlx, tly, width, height
		static const int arrayLength = 4;
		Point tL, tR, bL, bR;
	public:
		Rect();
		Rect(Point position, int width, int height);
		Rect(Point topLeft, Point bottomRight);
		Rect(const Rect &that);
		Rect(float x, float y, int width, int height);
		~Rect();
		Rect &operator=(const Rect &that);
		Rect operator+(const Point &point);
		Rect operator-(const Point &point);
		Point collideLine(Line &ray);
		Point getBottomLeft() const;
		Point getBottomRight() const;
		Point getCenter();
		Point getTopLeft() const;
		Point getTopRight() const;
		SDL_Rect getSDLRect();
		bool overlap(Rect &other);
		float getHeight();
		float getWidth();
		void draw(SDL_Renderer* renderer, Point offset);
		void operator+=(Point point);
		void operator-=(Point point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};
