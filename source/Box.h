#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "primatives/Point.h"
#include "Rect.h"	
#include "Texture.h"
#include "CollideBase.h"
#include "SuperTexture.h"

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
			/*
			boxRGBA(renderer, outerRect->getTopLeft(), outerRect->getBottomRight(), 0xFF, 0x00, 0x00, 0xFF);
			if (mTexture->isLoaded() == true) {
				mTexture->render(renderer);
			} else {
				loadTexture(renderer);
			}
			outerRect->draw(renderer);
			innerRect->draw(renderer);*/
			if (mTexture->isLoaded() == true) {
				mTexture->render(renderer);
			} else {
				loadTexture(renderer);
			}
		}
		
		Point collideLine(Line &ray) {
			return outerRect->collideLine(ray);
		}
		
		void fill(SDL_Renderer *renderer, Uint32 color = 0x000000FF) {
			mTexture->createBlank(renderer, innerRect->getWidth(), innerRect->getHeight(), color);
		}
		
		bool overlap(Rect &test) {
			return outerRect->overlap(test);
		}
};

bool collideRect(Rect rect, std::vector<Box*> vec) {
	bool result = false;
	for (int i = 0; i < (&vec)->size(); i++) {
		result = result || ((vec[i])->overlap(rect));
	}
	return result;
}

bool collideRect(Rect rect, std::vector<Box*>* vec) {
	bool result = false;
	for (int i = 0; i < vec->size(); i++) {
		result = result || (*vec)[i]->overlap(rect);
	}
	return result;
}

bool collideRect(Rect rect, std::vector<Box>* vec) {
	bool result = false;
	for (int i = 0; i < vec->size(); i++) {
		result = result || (*vec)[i].overlap(rect);
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

Point smallestDistanceFrom(std::vector<Box*>* boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < boxes->size(); i++) {
		stored = smallerDistance(origin, (*boxes)[i]->collideLine(ray), stored);
	}
	return stored;
}

Point smallestDistanceFrom(std::vector<Box>* boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < boxes->size(); i++) {
		stored = smallerDistance(origin, (*boxes)[i].collideLine(ray), stored);
	}
	return stored;
}


Point collideTestVectorToRay(std::vector<Box*> boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

Point collideTestVectorToRay(std::vector<Box*>* boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

Point collideTestVectorToRay(std::vector<Box>* boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}
