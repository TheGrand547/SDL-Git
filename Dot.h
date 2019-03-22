#pragma once
#include<SDL2/SDL.h>
#include "Rect.h"

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
		
		void operator-=(Point delta) {
			*myRect += delta;
			evalAngle(delta);
		}
		
		void operator+=(Point delta) {
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
			Point temp = Point(this->myRect->getTopLeft());
			temp += Point(4000*cos(*angle), 4000*sin(PI+*angle));
			return Line(this->myRect->getTopLeft(), temp);
		}
		
		float getAngle() {
			return *(this->angle) * 180/PI;
		}
		
		void draw(SDL_Renderer *renderer) {
			SDL_SetRenderDrawColor(renderer, rChannel, gChannel, 
									bChannel, aChannel);
			SDL_Rect temp = this->myRect->getSDLRect();
			SDL_RenderFillRect(renderer, &temp);
		}
};
