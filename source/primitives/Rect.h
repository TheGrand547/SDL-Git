#pragma once
#include<iostream>
#include "../essential/util.h"
#include "../MyBase.h"
#include "Point.h"
#include "Line.h"

class Rect: public MyBase {
	protected:
		Point topLeft, heightVector, widthVector;
	public:
		Rect();
		Rect(Point topLeft, Line widthVector, Line heightVector);
		Rect(Point topLeft, Point widthVector, Point heightVector);
		Rect(Line side1, Line side2);
		Rect(Point position, float width, float height);
		Rect(Point topLeft, Point bottomRight);
		Rect(const Rect& that);
		Rect(float x, float y, float width, float height);
		~Rect();
		Rect getBoundingRect() const;
		Rect& operator=(const Rect& that);
		Rect operator+(const Point& point);
		Rect operator-(const Point& point);
		bool doesLineCollide(const Line& ray) const;
		bool operator==(const Rect& rect) const;
		bool overlap(const Rect& other) const;
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
		void operator+=(const Point& point);
		void operator-=(const Point& point);
		void setColorChannels(int r, int g, int b, int a);
		void superDraw(SDL_Renderer* renderer, Point offset);
};
