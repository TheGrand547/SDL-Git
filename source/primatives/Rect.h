#pragma once
#include<iostream>
#include "util.h"
#include "../MyBase.h"
#include "../primatives/Point.h"
#include "../primatives/Line.h"
#include "../PointDelta.h"
Point smallerDistance(Point distanceFrom, Point pointA, Point pointB);
bool valueInRange(int value, int min, int max);


class Rect: public MyBase{
	protected:
		static const int arrayLength = 4;
		Line* lines[arrayLength];
		Point *tL, *tR, *bL, *bR;
	public:
		Rect() {
			this->tL = NULL;
			this->tR = NULL;
			this->bL = NULL;
			this->bR = NULL;
			this->lines[0] = NULL;
			this->lines[1] = NULL;
			this->lines[2] = NULL;
			this->lines[3] = NULL;
		}
		
		Rect(Point topLeft, Point bottomRight) {
			Point *topRight = new Point(bottomRight.x(), topLeft.y());
			Point *bottomLeft = new Point(topLeft.x(), bottomRight.y());
			this->tL = new Point(topLeft);
			this->tR = new Point(*topRight);
			this->bL = new Point(*bottomLeft);
			this->bR = new Point(bottomRight);
			lines[0] =  new Line(topLeft, *topRight); //Top
			lines[1] = new Line(*bottomLeft, bottomRight); //Bottom
			lines[2] = new Line(topLeft, *bottomLeft); //Left
			lines[3] = new Line(*topRight, bottomRight); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
			delete topRight;
			delete bottomLeft;
		}
		
		Rect(float x, float y, int width, int height) {
			*this = Rect(Point(x, y), width, height);
		}
		
		Rect(Point position, int width, int height) {
			Point *topRight = new Point(position.x() + width, position.y());
			Point *bottomLeft = new Point(position.x(), position.y() + height);
			this->tL = new Point(position);
			this->tR = new Point(*topRight);
			this->bL = new Point(*bottomLeft);
			this->bR = new Point(position + Point(width, height));
			lines[0] =  new Line(position, *topRight); //Top
			lines[1] = new Line(*bottomLeft, *bR); //Bottom
			lines[2] = new Line(position, *bottomLeft); //Left
			lines[3] = new Line(*topRight, *bR); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
			delete topRight;
			delete bottomLeft;
		}
		
		~Rect() {
 			for (Line* line: this->lines) {
				delete line;
			}
			delete this->tL;
			delete this->tR;
			delete this->bL;
			delete this->bR;
		}
		
		void draw(SDL_Renderer* renderer, Point offset) {
			rectangleRGBA(renderer, *tL - offset, *bR - offset, rChannel, bChannel, gChannel, aChannel);
		}
		
		Point collideLine(Line &ray, Point offset = Point(0, 0)) {
			/* No way for a single straight line to intersect a line in more than
			 * two points *except with the stupid inline ones that i'm changing
			 * the whole thing for */
			Point intersect[4] = {Point(), Point(), Point(), Point()};
			Point tempPoint;
			int index = 0;
			for (int i = 0; i < arrayLength; i++) {
				tempPoint = intersectionTest(*(lines[i]), ray);
				if (tempPoint.isReal()) {
					intersect[index] = tempPoint;
					index++;
				}
			}
			if (intersect[0].isReal() && intersect[1].isNull() && intersect[2].isNull()) {
				return intersect[0];
			} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isNull()) {
				return smallerDistance(ray.getOrigin(), intersect[0], intersect[1]);
			} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isReal()) {
				return smallerDistance(ray.getOrigin(),intersect[2], smallerDistance(ray.getOrigin(), intersect[0], intersect[1]));
			}
			return Point(); 
			
		}
		
		void setColorChannels(int r, int g, int b, int a) {
			_setColorChannels(r, g, b, a);
		}
		
		Point* getTopLeft() const {
			return this->tL;
		}
		
		Point* getTopRight() const {
			return this->tR;
		}
		
		Point* getBottomLeft() const {
			return this->bL;
		}
		
		Point* getBottomRight() const {
			return this->bR;
		}
		
		float getWidth() {
			return bR->x() - tL->x();
		}
		float getHeight() {
			return bR->y() - tL->y();
		}
		
		bool overlap(Rect &other) {
			bool xOver = valueInRange(this->tL->x(), other.tL->x(), other.tL->x()+other.getWidth()) || 
						 valueInRange(other.tL->x(), this->tL->x(), this->bR->x());
			bool yOver = valueInRange(this->tL->y(), other.tL->y(), other.tL->y()+other.getHeight()) || 
						 valueInRange(other.tL->y(), this->tL->y(), this->bR->y());
			return xOver && yOver;
		}
		
		SDL_Rect getSDLRect() {
			SDL_Rect tempRect;
			tempRect.x = tL->x();
			tempRect.y = tL->y();
			tempRect.w = getWidth();
			tempRect.h = getHeight();
			return tempRect;
		}
		
		Rect operator+(const Point &point) {
			return Rect(this->tL->copy() + point, this->bR->copy() + point);
		}
		Rect operator-(const Point &point) {
			return Rect(this->tL->copy() - point, this->bR->copy() - point);
		}
		
		void operator+=(Point &point) {
			*(this->tL) += point;
			*(this->bR) += point;
			*(this->tR) += point;
			*(this->bL) += point;
			for (Line *line: lines) {
				*line += point;
			}
		}
		
		void operator-=(Point &point) {
			*(this->tL) -= point;
			*(this->bR) -= point;
			*(this->tR) -= point;
			*(this->bL) -= point;
			for (Line *line: lines) {
				*line -= point;
			}
		}
		
		void operator+=(PointDelta &point) {
			*(this->tL) += point;
			*(this->bR) += point;
			*(this->tR) += point;
			*(this->bL) += point;
			for (Line *line: lines) {
				*line += point;
			}
		}
		
		void operator-=(PointDelta &point) {
			*(this->tL) -= point;
			*(this->bR) -= point;
			*(this->tR) -= point;
			*(this->bL) -= point;
			for (Line *line: lines) {
				*line -= point;
			}
		}
		
		Rect &operator=(const Rect &that) {
			Point topRight = Point(that.bR->x(), that.tL->y());
			Point bottomLeft = Point(that.tL->x(), that.bR->y());
			tL = new Point(*that.tL);
			tR = new Point(*that.tR);
			bL = new Point(*that.bL);
			bR = new Point(*that.bR);
			lines[0] =  new Line(tL, tR); //Top
			lines[1] = new Line(bL, bR); //Bottom
			lines[2] = new Line(tL, bL); //Left
			lines[3] = new Line(tR, bR); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
			return *this;
		}
		
		Rect(const Rect &that) {
			Point topRight = Point(that.bR->x(), that.tL->y());
			Point bottomLeft = Point(that.tL->x(), that.bR->y());
			tL = new Point(*that.tL);
			tR = new Point(*that.tR);
			bL = new Point(*that.bL);
			bR = new Point(*that.bR);
			lines[0] = new Line(tL, tR); //Top
			lines[1] = new Line(bL, bR); //Bottom
			lines[2] = new Line(tL, bL); //Left
			lines[3] = new Line(tR, bR); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
		}
		
		Point getCenter() {
			return *(this->tL) + Point(this->getWidth()/2, this->getHeight()/2);
		}
};


Point smallerDistance(Point distanceFrom, Point pointA, Point pointB) {
	if (pointA.isReal() && pointB.isNull()) {
		return pointA;
	}
	if (pointA.isNull() && pointB.isReal()) {
		return pointB;
	}
	if (pointA.isNull() && pointB.isNull()) {
		return Point();
	}
	if (distanceFrom.distanceToPoint(pointA) < distanceFrom.distanceToPoint(pointB)) {
		return pointA;
	} 
	if (distanceFrom.distanceToPoint(pointA) > distanceFrom.distanceToPoint(pointB)) {
		return pointB;
	}
	return Point();
}
