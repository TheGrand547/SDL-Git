#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "primatives/Point.h"
#include "primatives/Rect.h"	
#include "wrappers/Texture.h"
#include "wrappers/SuperTexture.h"
#include "BoundedPoint.h"
#include "CollideBase.h"

typedef Uint32 uint32_t;
class Box : public CollideBase{
	//Class for boxes
	private:
		const float outdent = .5;
		const int width = 100;
		const int height = 100;
		
		Point *inPointLeft, *inPointRight;
		Rect *outerRect, *innerRect;
		SuperTexture *mTexture;
	public:
		Box() {
			outerRect = new Rect();
			inPointLeft = new Point();
			inPointRight = new Point();
			innerRect = new Rect();
			mTexture = new SuperTexture();
		}
		Box(Point position) {
			//All boxes are of the same size
			outerRect = new Rect(position, this->width, this->height);
			inPointLeft = new Point(position);
			inPointRight = new Point(position.x() + this->width, position.y() + (this->height * outdent));
			innerRect = new Rect(inPointLeft, inPointRight);
			innerRect->setColorChannels(0x30, 0x30, 0x30, 0xFF);
			outerRect->setColorChannels(0x00, 0x00, 0x00, 0xFF);
			mTexture = new SuperTexture(0xFF, 0x00, 0x00, 0xFF);
			mTexture->setPos(innerRect->getTopLeft());
		}
		
		~Box() {
			delete outerRect;
			delete innerRect;
			delete mTexture;
			delete inPointLeft;
			delete inPointRight;
		}
		
		Box(const Box &that) {
			outerRect = new Rect(*that.outerRect);
			inPointLeft = new Point(*that.inPointLeft);
			inPointRight = new Point(*that.inPointRight);
			
			innerRect = new Rect(inPointLeft, inPointRight);
			innerRect->setColorChannels(0x30, 0x30, 0x30, 0xFF);
			outerRect->setColorChannels(0x00, 0x00, 0x00, 0xFF);
			mTexture = new SuperTexture();
			mTexture->setPos(innerRect->getTopLeft());
		}
		
		Box &operator=(const Box &that) {
			outerRect = new Rect(*that.outerRect);
			inPointLeft = new Point(*that.inPointLeft);
			inPointRight = new Point(*that.inPointRight);
			
			innerRect = new Rect(inPointLeft, inPointRight);
			innerRect->setColorChannels(0x30, 0x30, 0x30, 0xFF);
			outerRect->setColorChannels(0x00, 0x00, 0x00, 0xFF);
			mTexture = new SuperTexture();
			mTexture->setPos(innerRect->getTopLeft());
			return *this;
		}
			
				
		void loadTexture(SDL_Renderer* renderer, std::string path = "resources/missingTexture.jpg") {
			mTexture->setClip(100, 100);
			mTexture->drawBox(renderer, outerRect);
			mTexture->loadFromFile(path.c_str(), renderer, innerRect->getWidth(), innerRect->getHeight());
			mTexture->setPos(innerRect->getTopLeft());
			mTexture->drawRect(renderer, outerRect);
			mTexture->drawRect(renderer, innerRect);
		}
		
		void draw(SDL_Renderer* renderer) {
			if (mTexture->isLoaded() == true) {
				mTexture->render(renderer);
			} else {
				loadTexture(renderer);
			}
		}
		
		void draw(SDL_Renderer* renderer, Point offset) {
			if (mTexture->isLoaded()) {
				mTexture->render(renderer, offset);
			} else {
				loadTexture(renderer);
			}
		}
		
		Point collideLine(Line &ray) {
			return outerRect->collideLine(ray);
		}
		
		Point collideLine(Line &ray, Point point) {
			return outerRect->collideLine(ray, point);
		}
		
		void fill(SDL_Renderer *renderer, Uint32 color = 0x000000FF) {
			mTexture->createBlank(renderer, innerRect->getWidth(), innerRect->getHeight(), color);
		}
		
		bool overlap(Rect &test) {
			return outerRect->overlap(test);
		}
		
		bool overlap(Rect &other, Point offset) {
			return outerRect->overlap(other, offset);
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
	return !collideRect(rect+dydx, vec, screen.negate()) && !collideRect(rect+dydx, vec, screen.negate()-dydx);
}
