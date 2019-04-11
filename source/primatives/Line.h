#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "Point.h"
#include "../MyBase.h"
#include "../random.h"
#include "../util.h"
typedef Uint8 uint8_t;
bool xBetweenAandB(float x, float a, float b);

class Line: public MyBase{
	/* Represents a line in the form, ax+by=c, bounded by the points A and B */
	private:
		float *ax, *by, *c;
		float *minX, *maxX, *minY, *maxY;
		Point *originPoint, *endingPoint;
	public:	
		Line() {
			ax = new float(0);
			by = new float(0);
			c = new float(0);
			originPoint = new Point();
			endingPoint = new Point();
			minX = new float(0);
			maxX = new float(0);
			minY = new float(0);
			maxY = new float(0);
		}

		Line(Point pointA, Point pointB, uint8_t r = 0x00, uint8_t g = 0x00, 
							uint8_t b = 0xFF, uint8_t a = 0xFF) {
			ax = new float(pointB.y() - pointA.y());
			by = new float(pointA.x() - pointB.x());
			c = new float((*ax * pointA.x()) + (*by * pointA.y()));
			originPoint = new Point(pointA);
			endingPoint = new Point(pointB);
			minX = new float(0.0f);
			maxX = new float(0.0f);
			minY = new float(0.0f);
			maxY = new float(0.0f);
			mMax(pointA.x(), pointB.x(), *minX, *maxX);
			mMax(pointA.y(), pointB.y(), *minY, *maxY);
			setColorChannels(r, g, b, a);
		}
		
		Line(Point *pointA, Point *pointB) {
			ax = new float(pointB->y() - pointA->y());
			by = new float(pointA->x() - pointB->x());
			c = new float((*ax * pointA->x()) + (*by * pointA->y()));
			originPoint = new Point(pointA);
			endingPoint = new Point(pointB);
			minX = new float(0.0f);
			maxX = new float(0.0f);
			minY = new float(0.0f);
			maxY = new float(0.0f);
			mMax(pointA->x(), pointB->x(), *minX, *maxX);
			mMax(pointA->y(), pointB->y(), *minY, *maxY);
		}
		
		~Line() {
			delete ax;
			delete by;
			delete c;
			delete originPoint;
			delete endingPoint;
			delete minX;
			delete minY;
			delete maxX;
			delete maxY;
		}
		
		Line(const Line &line) {
			ax = new float(*line.ax);
			by = new float(*line.by);
			c = new float(*line.c);
			originPoint = new Point(*line.originPoint);
			endingPoint = new Point(*line.endingPoint);
			minX = new float(0.0f);
			maxX = new float(0.0f);
			minY = new float(0.0f);
			maxY = new float(0.0f);
			mMax(originPoint->x(), endingPoint->x(), *minX, *maxX);
			mMax(originPoint->y(), endingPoint->y(), *minY, *maxY);
		}
		
		Line &operator=(const Line &that) {
			ax = new float(*that.ax);
			by = new float (*that.by);
			c = new float (*that.c);
			originPoint = new Point(*that.originPoint);
			endingPoint = new Point(*that.endingPoint);
			minX = new float(0.0f);
			maxX = new float(0.0f);
			minY = new float(0.0f);
			maxY = new float(0.0f);
			mMax(originPoint->x(), endingPoint->x(), *minX, *maxX);
			mMax(originPoint->y(), endingPoint->y(), *minY, *maxY);
			return *this;
		}
		
		
		bool isPointOnThisLine(Point point) {
			if (lValueInRange(point.x(), minX, maxX) && lValueInRange(point.y(), minY, maxY))
				return true;
			return false;
		}
		
		bool collidePoint(Point &point) {
			if (lValueInRange(point.x(), minX, maxX) && lValueInRange(point.y(), minY, maxY))  {
				return true;
			}
			return false;
		}
		
		bool collidePoint(Point *point) {
			if (lValueInRange(point->x(), minX, maxX) && lValueInRange(point->y(), minY, maxY)) {
				return true;
			}
			return false;
		}
		
		void operator+=(Point b) {
			*originPoint += b;
			*endingPoint += b;
			*ax = endingPoint->y() - originPoint->y();
			*by = originPoint->x() - endingPoint->x();
			*c = (*ax * originPoint->x()) + (*by * originPoint->y());
			*minX += b.x();
			*maxX += b.x();
			*minY += b.y();
			*maxY += b.y();
		}
		
		void operator-=(Point b) {
			*originPoint -= b;
			*endingPoint -= b;
			*ax = endingPoint->y() - originPoint->y();
			*by = originPoint->x() - endingPoint->x();
			*c = (*ax * originPoint->x()) + (*by * originPoint->y());
			*minX -= b.x();
			*maxX -= b.x();
			*minY -= b.y();
			*maxY -= b.y();
		}
		
		Line operator+(Point b) {
			return Line(*originPoint+b, *endingPoint+b);
		}
		
		Line operator-(Point b){
			return Line(*originPoint-b, *endingPoint-b);
		}
			
		float getAx() { 
			return *ax; 
		}
		
		float getBy() { 
			return *by; 
		}
		
		float getC() { 
			return *c; 
		}
		
		Point getOrigin() {
			return *originPoint;
		}
		
		Point getEnd() {
			return *endingPoint;
		}
		
		friend std::ostream &operator<<(std::ostream &output, const Line &line) {
			output << line.ax << "x + " << line.by << "y = " << line.c;
			return output;
		}
		
		void drawLine(SDL_Renderer* renderer) {
			aalineRGBA(renderer, originPoint, endingPoint, rChannel, gChannel, bChannel, aChannel);
		}		
		
		void drawLine(SDL_Renderer* renderer, Point offset) {
			aalineRGBA(renderer, originPoint, endingPoint, rChannel, gChannel, bChannel, aChannel, offset);
		}				
		
		void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {
			setColorChannels(red, green, blue, alpha);
		}
};

Point intersectionTest(Line line1, Line &line2) {
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

bool xBetweenAandB(float x, float a, float b) {
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
