#pragma once
#include<SDL2/SDL.h>
#include "primatives/Rect.h"
#include "BoundedRect.h"
#include "PointDelta.h"
#include "essential/constants.h"

#define PI 3.14159265

class Dot: public MyBase {
	private:
		float *angle;
		BoundedRect *myRect;
	public:
		Dot(Point startingCoordinate) {
			angle = new float(0);
			myRect = new BoundedRect(startingCoordinate, startingCoordinate + Point(Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION), 
									0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT);
		}
		
		~Dot() {
			delete this->angle;
			delete this->myRect;
		}
		
		Point getCenter() {
			return this->myRect->getCenter();
		}
		
		void evalAngle(Point delta) {
			if(int(delta.y()) != 0 || int(delta.x()) != 0) {
				*(this->angle) = atan2(0-delta.y(), delta.x());
			}
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
				temp = Point(delta.getXMin() * cos(tempFloat), -delta.getYMin() * sin(tempFloat));
			}
			*myRect -= temp;
			evalAngle(temp);
		}
		
		void operator+=(PointDelta delta) {
			Point temp = Point(delta);
			if (delta.getMagnitude() > delta.getMaxMagnitude()) {
				float tempFloat = calcAngle(delta);
				temp = Point(delta.getXMin() * cos(tempFloat), -delta.getYMin() * sin(tempFloat));
			}
			*myRect += temp;
			evalAngle(temp);
		}
		
		Point getPos() {
			return *this->myRect->getTopLeft();
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
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			setColorChannels(0x00, 0x00, 0xFF, 0xFF);
			SDL_SetRenderDrawColor(renderer, rChannel, gChannel, bChannel, aChannel);
			SDL_Rect temp = (BoundedRect(*this->myRect) + offset).getSDLRect();
			temp.w = Player::PLAYER_X_DIMENSION;
			temp.h = Player::PLAYER_Y_DIMENSION;
			SDL_RenderFillRect(renderer, &temp);
		}
};
