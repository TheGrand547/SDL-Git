#pragma once
#include<SDL2/SDL.h>
#include "primitives/Rect.h"
#include "BoundedRect.h"
#include "PointDelta.h"
#include "essential/constants.h"
#include<math.h>

class Dot: public MyBase {
	private:
		float angle;
		BoundedRect *myRect; // Don't think this needs to be a pointer
	public:
		Dot(Point startingCoordinate) {
			angle = 0;
			myRect = new BoundedRect(startingCoordinate, startingCoordinate + Point(Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION), 
									0, 0, Screen::MAX_WIDTH, Screen::MAX_HEIGHT);
		}
		
		~Dot() {
			delete this->myRect;
		}
		
		Point getCenter() {
			return this->myRect->getCenter();
		}
		
		void evalAngle(Point delta) {
			this->angle = atan2(delta.y(), delta.x());
		}
		
		float calcAngle(Point point) {
			if(point.y() != 0 || point.x() != 0) {
				 return atan2(0-point.y(), point.x());
			 }
			return 0;
		}
		
		void operator+=(Point delta) {
			*myRect += delta;
			evalAngle(delta);
		}
		
		void operator-=(Point delta) {
			*this += delta.negate();
		}
		
		Point getPos() {
			return this->myRect->getTopLeft();
		}
		
		Rect getRect() {
			return *myRect;
		}
		
		Line getRay() {
			Point temp = Point(this->myRect->getCenter());
			temp += Point(Player::PLAYER_RAY_CAST_LENGTH * cos(this->angle), Player::PLAYER_RAY_CAST_LENGTH * sin(this->angle));
			return Line(this->myRect->getCenter(), temp);
		}
		
		float getAngle() {
			return this->angle * 180 / M_PI;
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
