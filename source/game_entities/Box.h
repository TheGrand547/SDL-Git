#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "../primatives/Point.h"
#include "../primatives/Rect.h"
#include "../wrappers/SuperTexture.h"	
#include "../wrappers/Texture.h"
#include "../BoundedPoint.h"
#include "../CollideBase.h"
#include "../constants.h"
#include "../util.h"

typedef Uint32 uint32_t;
class Box : public CollideBase{
	//Class for boxes
	private:
		Rect *myRect;
		SuperTexture *mTexture = NULL;
	public:
		Box() {
			myRect = new Rect();
		}
		
		Box(Point position) {
			myRect = new Rect(position, cBox::BOX_WIDTH, cBox::BOX_HEIGHT);
		}
		
		~Box() {
			delete this->myRect;
		}
		
		Box(const Box &that) {
			myRect = new Rect(*that.myRect);
		}
		
		Box &operator=(const Box &that) {
			myRect = new Rect(*that.myRect);
			return *this;
		}
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			if (mTexture != NULL) {
				this->mTexture->setPos(this->myRect->getTopLeft());
				this->mTexture->render(renderer, offset);
			}
		}
		
		Point collideLine(Line &ray, Point point = Point(0, 0)) {
			return this->myRect->collideLine(ray, point);
		}
		
		bool overlap(Rect &other, Point offset = Point(0, 0)) {
			return this->myRect->overlap(other, offset);
		}
		
		void setTexture(SuperTexture* texture) {
			this->mTexture = texture;
		}
		
		static SuperTexture* createBoxTexture(SDL_Renderer* renderer) {
			SuperTexture* texture = new SuperTexture();
			texture->setClip(cBox::BOX_WIDTH, cBox::BOX_HEIGHT);
			texture->drawBox(renderer, Rect(Point(0, 0), Point(cBox::BOX_WIDTH, cBox::BOX_HEIGHT)));
			texture->loadFromFile("resources/missingTexture.jpg", renderer, cBox::BOX_WIDTH, cBox::BOX_OUTDENT * cBox::BOX_HEIGHT);
			setRenderColors(renderer, cBox::BOX_OUTER_BORDER_COLOR);
			texture->drawRect(renderer, Rect(Point(0, 0), Point(cBox::BOX_WIDTH, cBox::BOX_HEIGHT)));
			setRenderColors(renderer, cBox::BOX_INNER_BORDER_COLOR);
			texture->drawRect(renderer, Rect(Point(0, 0), Point(cBox::BOX_WIDTH, cBox::BOX_OUTDENT * cBox::BOX_HEIGHT)));
			return texture;
		}
};

bool collideRect(Rect rect, std::vector<Box*> vec) {
	bool result = false;
	for (int i = 0; i < (&vec)->size(); i++) {
		result = result || ((vec[i])->overlap(rect));
	}
	return result;
}

bool collideRect(Rect rect, std::vector<Box*>* vec, Point offset = Point(0, 0)) {
	bool result = false;
	for (int i = 0; i < vec->size(); i++) {
		result = result || (*vec)[i]->overlap(rect, offset);
	}
	return result;
}

Point smallestDistanceFrom(std::vector<Box*> boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < (boxes).size(); i++) {
		stored = smallerDistance(origin, (boxes[i])->collideLine(ray), stored);
	}
	return stored;
}

Point smallestDistanceFrom(std::vector<Box*>* boxes, Point origin, Line ray, Point point) {
	Point stored;
	for (int i = 0; i < boxes->size(); i++) {
		stored = smallerDistance(origin, (*boxes)[i]->collideLine(ray, point), stored);
	}
	return stored;
}

Point collideTestVectorToRay(std::vector<Box*> boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

Point collideTestVectorToRay(std::vector<Box*>* boxes, Line ray, Point point = Point(0, 0)) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray, point);
}

bool collideRectPlusExtras(Rect rect, std::vector<Box*>* vec, Point dydx, BoundedPoint screen) {
	return !collideRect(rect+dydx, vec, Point(0,0));
}
