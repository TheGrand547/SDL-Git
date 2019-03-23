#pragma once
#include<SDL2/SDL.h>
#include "Rect.h"
#include "PointDelta.h"

#define PI 3.14159265

class Dot: public MyBase {
	private:
		float *angle;
		Point *position;
		Rect *myRect;
	public:
		Dot(Point startingCoordinate) {
			angle = new float(0);
			position = new Point(startingCoordinate);
			myRect = new Rect(startingCoordinate, startingCoordinate + Point(10,10));
		}
		
		~Dot() {
			delete angle;
			delete position;
			delete myRect;
		}
		
		void evalAngle(Point delta) {
			if(delta.y() != 0 || delta.x() != 0)
				*(this->angle) = atan2(0-delta.y(), delta.x());
		}
		
		float calcAngle(Point point) {
			if(point.y() != 0 || point.x() != 0)
				 return atan2(0-point.y(), point.x());
			return 0;
		}
		
		void operator-=(PointDelta delta) {
			Point temp = Point(delta);
			if (delta.getMagnitude() > delta.getMaxMagnitude()) {
				float tempFloat = calcAngle(delta);
				temp = Point(delta.getXMin() * cos(tempFloat), -delta.getXMin() * sin(tempFloat));
			}
			*myRect -= temp;
			evalAngle(temp);
		}
		
		void operator+=(PointDelta delta) {
			Point temp = Point(delta);
			if (delta.getMagnitude() > delta.getMaxMagnitude()) {
				float tempFloat = calcAngle(delta);
				temp = Point(delta.getXMin() * cos(tempFloat), -delta.getXMin() * sin(tempFloat));
			}
			*myRect += delta;
			evalAngle(delta);
		}
		
		Point getPos() {
			return myRect->getTopLeft();
		}
		
		Rect getRect() {
			return *myRect;
		}
		
		Line getRay() {
			Point temp = Point(this->myRect->getCenter());
			temp += Point(300*cos(*angle), 300*sin(PI+*angle));
			return Line(this->myRect->getCenter(), temp);
		}
		
		float getAngle() {
			return *(this->angle) * 180/PI;
		}
		
		void draw(SDL_Renderer *renderer) {
			setColorChannels(0x00, 0xFF, 0x00, 0xFF);
			SDL_SetRenderDrawColor(renderer, rChannel, gChannel, 
									bChannel, aChannel);
			SDL_Rect temp = this->myRect->getSDLRect();
			SDL_RenderFillRect(renderer, &temp);
		}
};
