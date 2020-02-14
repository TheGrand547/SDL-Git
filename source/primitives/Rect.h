#pragma once
#include<iostream>
#include "../essential/util.h"
#include "PointDelta.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"

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
		Rect& operator=(const Rect& that);
		Rect operator+(const Point& point);
		Rect operator-(const Point& point);
		bool overlap(const Rect& other) const;
		bool doesLineCollide(const Line& ray) const;
		float getHeight() const;
		float getWidth() const;
		Point collideLine(const Line& ray) const;
		Point getBottomLeft() const;
		Point getBottomRight() const;
		Point getCenter() const;
		Point getTopLeft() const;
		Point getTopRight() const;
		SDL_Rect getSDLRect() const;
		void draw(SDL_Renderer* renderer, Point offset);
		void operator+=(const Point point);
		void operator-=(const Point point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};
