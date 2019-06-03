#pragma once
#include<SDL2/SDL.h>
#include "primitives/Rect.h"
#include "BoundedRect.h"
#include "primitives/PointDelta.h"
#include "essential/constants.h"
#include<math.h>

class Dot: public MyBase {
	private:
		// TODO: Make this two files
		SDL_Renderer* renderer;
		BoundedPoint* offset;
		
		float angle;
		BoundedPoint position;
	public:
		Dot(Point startingCoordinate) {
			this->angle = 0;
			this->position = BoundedPoint(startingCoordinate, 0, 0, Screen::MAX_WIDTH - Player::PLAYER_X_DIMENSION, Screen::MAX_HEIGHT - Player::PLAYER_Y_DIMENSION);
		}
		
		~Dot() {
			this->renderer = NULL;
			this->offset = NULL;
		}
		
		void setRenderingValues(SDL_Renderer* renderer, BoundedPoint* offset) {
			this->renderer = renderer;
			this->offset = offset;
		}
		
		Point getCenter() {
			return this->position + Point(Player::PLAYER_X_DIMENSION / 2, Player::PLAYER_Y_DIMENSION / 2);
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
			this->position += delta;
			evalAngle(delta);
		}
		
		void operator-=(Point delta) {
			*this += delta.negate();
		}
		
		Point getPos() {
			return this->position;
		}
		
		Rect getRect() {
			return Rect(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
		}
		
		Line getRay() {
			Point temp = Point(this->getCenter());
			temp += Point(Player::PLAYER_RAY_CAST_LENGTH * cos(this->angle), Player::PLAYER_RAY_CAST_LENGTH * sin(this->angle));
			return Line(this->getCenter(), temp);
		}
		
		float getAngle() {
			return this->angle * 180 / M_PI;
		}
		
		void draw() {
			SDL_SetRenderDrawColor(this->renderer, rChannel, gChannel, bChannel, aChannel);
			SDL_Rect temp = (Rect(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION) - *this->offset).getSDLRect();
			temp.w = Player::PLAYER_X_DIMENSION;
			temp.h = Player::PLAYER_Y_DIMENSION;
			SDL_RenderFillRect(this->renderer, &temp);
		}
		
		void collideTest(PointDelta delta, CollideBaseGroup* boxes) {
			if (!delta.getNonZero()) {
				return;
			}
			float xDelta = 0;
			float yDelta = 0;
			for (int i = 1; i < 6; i++) {
				if (!xDelta) {
					if (collideRectTest(this->getRect() + delta.onlyX() / i, boxes)) {
						xDelta = delta.x() / i;
						*this->offset += delta.onlyX() / i;
					}
				}
				if (!yDelta) {
					if (collideRectTest(this->getRect() + delta.onlyY() / i, boxes)) {
						yDelta = delta.y() / i;
						*this->offset += delta.onlyY() / i;					
					}
				}
				if (xDelta && yDelta) {
					break;
				}
			}
			*this += PointDelta(xDelta, yDelta, delta.getMagnitude());
			if (this->getPos().x() < Screen::SCREEN_WIDTH / 2) {
				this->offset->xZero();
			}
			if (this->getPos().y() < Screen::SCREEN_HEIGHT / 2) {
				this->offset->yZero();
			}
			if (this->getPos().y() > Screen::MAX_Y_SCROLL_DISTANCE) {
				this->offset->maxY();
			}
			if (this->getPos().x() > Screen::MAX_X_SCROLL_DISTANCE) {
				this->offset->maxX();
			}
		} 
		
		void rayCast(CollideBaseGroup* boxes) {
			Point newPoint = collideTestVectorToRay(boxes, this->getRay());
			if (!newPoint.isNull()) {
				Line tempLine = Line(this->getCenter(), newPoint.copy());
				tempLine.setColorChannels(COLORS::CYAN);
				tempLine.drawLine(this->renderer, this->offset);
			}
		}
};
