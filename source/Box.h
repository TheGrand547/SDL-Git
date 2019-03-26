#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "Point.h"
#include "Rect.h"	
#include "Texture.h"

typedef Uint32 uint32_t;
class Box : public MyBase{
	//Class for boxes
	private:
		const float outdent = .5;
		const int width = 100;
		const int height = 100;
		
		Point *inPointLeft, *inPointRight;
		Rect *outerRect, *innerRect;
		Texture *mTexture;
	public:
		Box(Point position) {
			//All boxes are of the same size
			outerRect = new Rect(position, this->width+1, this->height+1);
			inPointLeft = new Point(position);
			inPointRight = new Point(position.x() + this->width, position.y() + this->height * outdent);
			innerRect = new Rect(inPointLeft, inPointRight);
			innerRect->setColorChannels(0x30, 0x30, 0x30, 0xFF);
			outerRect->setColorChannels(0x00, 0x00, 0x00, 0xFF);
			mTexture = new Texture();
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
			mTexture = new Texture();
			mTexture->setPos(innerRect->getTopLeft());
		}
		
		Box &operator=(const Box &that) {
			outerRect = new Rect(*that.outerRect);
			inPointLeft = new Point(*that.inPointLeft);
			inPointRight = new Point(*that.inPointRight);
			
			innerRect = new Rect(inPointLeft, inPointRight);
			innerRect->setColorChannels(0x30, 0x30, 0x30, 0xFF);
			outerRect->setColorChannels(0x00, 0x00, 0x00, 0xFF);
			mTexture = new Texture();
			mTexture->setPos(innerRect->getTopLeft());
			return *this;
		}
			
				
		void loadTexture(SDL_Renderer *renderer, std::string path = "resources/missingTexture.jpg") {
			mTexture->loadFromFile(path.c_str(), renderer, innerRect->getWidth(), innerRect->getHeight());
			mTexture->setPos(innerRect->getTopLeft());
		}
			
		void draw(SDL_Renderer* renderer) {		
			boxRGBA(renderer, outerRect->getTopLeft(), outerRect->getBottomRight(), 0xFF, 0x00, 0x00, 0xFF);
			if (mTexture->isLoaded() == true) {
				mTexture->render(renderer);
			} else {
				loadTexture(renderer);
			}
			outerRect->draw(renderer);
			innerRect->draw(renderer);
		}
		
		Point collideLine(Line ray) {
			return outerRect->collideLine(ray);
		}
		
		void fill(SDL_Renderer *renderer, Uint32 color = 0x000000FF) {
			mTexture->createBlank(renderer, innerRect->getWidth(), innerRect->getHeight(), color);
		}
		
		bool overlap(Rect &test) {
			return outerRect->overlap(test);
		}
};

bool collideRect(Rect rect, std::vector<Box> &vec) {
	bool result = false;
	for (int i = 0; i < (&vec)->size(); i++) {
		result = result || ((&vec[i])->overlap(rect));
	}
	return result;
}

Point smallestDistanceFrom(std::vector<Box> &boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < (&boxes)->size(); i++) {
		stored = smallerDistance(origin, (&boxes[i])->collideLine(ray), stored);
	}
	return stored;
}


Point collideTestVectorToRay(std::vector<Box> &boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}
