#pragma once
#include<iostream>
#include "../essential/util.h"
#include "PointDelta.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"

Point smallerDistance(Point distanceFrom, Point pointA, Point pointB);
class Rect: public MyBase {
	protected:
		static const int arrayLength = 4;
		float xpos, ypos, width, height;
	public:
		Rect();
		Rect(Point position, int width, int height);
		Rect(Point topLeft, Point bottomRight);
		Rect(const Rect& that);
		Rect(float x, float y, int width, int height);
		~Rect();
		Rect& operator=(const Rect &that);
		Rect operator+(const Point &point);
		Rect operator-(const Point &point);
		bool overlap(Rect& other);
		bool doesLineCollide(Line& ray);
		float getHeight();
		float getWidth();
		Point collideLine(Line& ray);
		Point getBottomLeft() const;
		Point getBottomRight() const;
		Point getCenter();
		Point getTopLeft() const;
		Point getTopRight() const;
		SDL_Rect getSDLRect();
		void draw(SDL_Renderer* renderer, Point offset);
		void operator+=(Point point);
		void operator-=(Point point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};
