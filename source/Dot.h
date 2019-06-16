#pragma once
#include<SDL2/SDL.h>
#include "primitives/Point.h"
#include "primitives/Rect.h"
#include "primitives/PointDelta.h"
#include "game_entities/CollideBaseGroup.h"
#include "essential/constants.h"
#include "essential/MegaBase.h"
#include<math.h>

class Dot: public MyBase {
	private:
		// TODO: Make this two files
		float angle;
		BoundedPoint position;
	public:
		Dot(Point startingCoordinate) {
			this->angle = 0;
			this->position = BoundedPoint(startingCoordinate, 0, 0, Screen::MAX_WIDTH - Player::PLAYER_X_DIMENSION, Screen::MAX_HEIGHT - Player::PLAYER_Y_DIMENSION);
		}
		
		~Dot() {}
		
		
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
			SDL_SetRenderDrawColor(MegaBase::renderer, rChannel, gChannel, bChannel, aChannel);
			SDL_Rect temp = (Rect(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION) - MegaBase::offset).getSDLRect();
			temp.w = Player::PLAYER_X_DIMENSION;
			temp.h = Player::PLAYER_Y_DIMENSION;
			SDL_RenderFillRect(MegaBase::renderer, &temp);
			Rect p(this->position, Player::PLAYER_X_DIMENSION, Player::PLAYER_Y_DIMENSION);
			p.setColorChannels(0xFF,0x00,0x00,0xFF);
			p.draw(MegaBase::renderer, MegaBase::offset);
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
						*MegaBase::offset += delta.onlyX() / i;
					}
				}
				if (!yDelta) {
					if (collideRectTest(this->getRect() + delta.onlyY() / i, boxes)) {
						yDelta = delta.y() / i;
						*MegaBase::offset += delta.onlyY() / i;					
					}
				}
				if (xDelta && yDelta) {
					break;
				}
			}
			*this += PointDelta(xDelta, yDelta, delta.getMagnitude());
			// PUT THIS ELSEWHERE
			if (this->getPos().x() < Screen::SCREEN_WIDTH / 2) {
				MegaBase::offset->xZero();
			}
			if (this->getPos().y() < Screen::SCREEN_HEIGHT / 2) {
				MegaBase::offset->yZero();
			}
			if (this->getPos().y() > Screen::MAX_Y_SCROLL_DISTANCE) {
				MegaBase::offset->maxY();
			}
			if (this->getPos().x() > Screen::MAX_X_SCROLL_DISTANCE) {
				MegaBase::offset->maxX();
			}
		} 
		
		void rayCast(CollideBaseGroup* boxes) {
			Point newPoint = collideTestVectorToRay(boxes, this->getRay());
			if (!newPoint.isNull()) {
				Line tempLine = Line(this->getCenter(), newPoint.copy());
				tempLine.setColorChannels(COLORS::CYAN);
				tempLine.drawLine(MegaBase::renderer, MegaBase::offset);
			}
		}
};
