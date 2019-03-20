#pragma once
#include "MyBase.h"
#include "Point.h"
#include "Line.h"
Point smallerDistance(Point distanceFrom, Point pointA, Point pointB);
bool valueInRange(int value, int min, int max);


class Rect: public MyBase{
	private:
		static const int arrayLength = 4;
		Line *lines[arrayLength];
		Point *tL, *tR, *bL, *bR;
	public:
		Rect() {}
		Rect(Point topLeft, Point bottomRight) {
			Point *topRight = new Point(bottomRight.x(), topLeft.y());
			Point *bottomLeft = new Point(topLeft.x(), bottomRight.y());
			tL = new Point(topLeft);
			tR = new Point(*topRight);
			bL = new Point(*bottomLeft);
			bR = new Point(bottomRight);
			lines[0] =  new Line(topLeft, *topRight); //Top
			lines[1] = new Line(*bottomLeft, bottomRight); //Bottom
			lines[2] = new Line(topLeft, *bottomLeft); //Left
			lines[3] = new Line(*topRight, bottomRight); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
			delete topRight;
			delete bottomLeft;
		}
		
		Rect(Point position, int width, int height) {
			Point *topRight = new Point(position.x() + width, position.y());
			Point *bottomLeft = new Point(position.x(), position.y() + height);
			tL = new Point(position);
			tR = new Point(*topRight);
			bL = new Point(*bottomLeft);
			bR = new Point(position + Point(width, height));
			lines[0] =  new Line(position, *topRight); //Top
			lines[1] = new Line(*bottomLeft, *bR); //Bottom
			lines[2] = new Line(position, *bottomLeft); //Left
			lines[3] = new Line(*topRight, *bR); //Right
			_setColorChannels(0x00, 0x00, 0x00, 0xFF);
			delete topRight;
			delete bottomLeft;
		}
		
		~Rect() {
			for (Line *line: lines) {
				delete line;
			}
			delete tL;
			delete tR;
			delete bL;
			delete bR;
		}
		
		void draw(SDL_Renderer* renderer) {
			rectangleRGBA(renderer, *tL, *bR, 
							rChannel, bChannel, gChannel, aChannel);
		}
		
		Point collideLine(Line ray) {
			//No way for a single straight line to intersect a line in more than
			//two points *except with the stupid inline ones that i'm changing
			//the whole thing for
			Point intersect[3] = {Point(-1,-1), Point(-1,-1), Point(-1,-1)};
			Point tempPoint;
			int index = 0;
			for (int i = 0; i < arrayLength; i++) {
				tempPoint = intersectionTest(*lines[i], ray);
				if (tempPoint.isReal()) {
					intersect[index] = tempPoint;
					index++;
				}
			}
			if (intersect[0].isReal() && intersect[1].isNull() && intersect[2].isNull()) {
				return intersect[0];
			} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isNull()) {
				return smallerDistance(ray.getOrigin(), intersect[0], 
										intersect[1]);
			} else if(intersect[0].isReal() && intersect[1].isReal() && intersect[2].isReal()) {
				return smallerDistance(ray.getOrigin(),intersect[2], smallerDistance(ray.getOrigin(), intersect[0], 
										intersect[1]));
			}
			return intersect[0]; //If index 0-2 are null, 1 with always be null
			
		}
		
		void setColorChannels(int r, int g, int b, int a) {
			_setColorChannels(r,g,b,a);
		}
		
		Point* getTopLeft() const {
			return tL;
		}
		
		Point* getTopRight() const {
			return tR;
		}
		
		Point* getBottomLeft() const {
			return bL;
		}
		
		Point* getBottomRight() const {
			return bR;
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
			Rect newRect = Rect(*(this->tL) + point, *(this->bR) + point);
			return newRect;
		}
		void operator+=(Point point) {
			*(this->tL) += point;
			*(this->bR) += point;
			*(this->tR) += point;
			*(this->bL) += point;
			for (Line *line: lines) {
				*line += point;
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
};


Point smallerDistance(Point distanceFrom, Point pointA, Point pointB) {
	if (pointA.isReal() && pointB.isNull()) 
		return pointA;
	if (pointA.isNull() && pointB.isNull())
		return Point();
	if (distanceFrom.distanceToPoint(pointA) <= distanceFrom.distanceToPoint(pointB))
		return pointA;
	return pointB;
}

