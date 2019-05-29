#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<vector>
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/SuperTexture.h"	
#include "../wrappers/Texture.h"
#include "../BoundedPoint.h"
#include "../essential/util.h"
#include "base/CollideBase.h"
#include "CollideBaseGroup.h"

typedef Uint32 uint32_t;
class Box : public CollideBase{
	private:
		Rect myRect;
		SuperTexture *mTexture;
	public:
		Box() {}
		
		Box(Point position) {
			/* This hurts me phyiscally */
			myRect = Rect(position, BOX::BOX_WIDTH - 1, BOX::BOX_HEIGHT - 1);
		}
		
		~Box() {
			this->mTexture = NULL;
		}
		
		Box(const Box &that) {
			myRect = that.myRect;
		}
		
		Box &operator=(const Box &that) {
			myRect = that.myRect;
			return *this;
		}
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			if (mTexture != NULL) {
				this->mTexture->setPos(this->myRect.getTopLeft());
				this->mTexture->render(renderer, offset);
			}
		}
		
		Point collideLine(Line &ray) {
			return this->myRect.collideLine(ray);
		}
		
		bool overlap(Rect &other) {
			return this->myRect.overlap(other);
		}
		
		void setTexture(SuperTexture* texture) {
			this->mTexture = texture;
		}
		
		static SuperTexture* createBoxTexture(SDL_Renderer* renderer) {
			SuperTexture* texture = new SuperTexture();
			texture->setClip(BOX::BOX_WIDTH, BOX::BOX_HEIGHT);
			texture->drawBox(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)), BOX::BOX_INNER_COLOR);
			texture->loadFromFile("resources/missingTexture.jpg", renderer, BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT);
			setRenderColors(renderer, BOX::BOX_OUTER_BORDER_COLOR);
			texture->drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_HEIGHT)));
			setRenderColors(renderer, BOX::BOX_INNER_BORDER_COLOR);
			texture->drawRect(renderer, Rect(Point(0, 0), Point(BOX::BOX_WIDTH, BOX::BOX_OUTDENT * BOX::BOX_HEIGHT)));
			return texture;
		}
		
		static void setTexture(std::vector<Box*>* vec, SuperTexture* texture) {
			for (Box* box: *vec) {
				box->setTexture(texture);
			}
		}
};

bool collideRect(Rect rect, CollideBaseGroup* boxes) {
	bool result = false;
	for (int i = 0; i < boxes->size(); i++) {
		result = result || (*boxes)[i]->overlap(rect);
		if (result)
			break;
	}
	return result;
}

Point smallestDistanceFrom(CollideBaseGroup* boxes, Point origin, Line ray) {
	Point stored;
	for (int i = 0; i < boxes->size(); i++) {
		stored = smallerDistance(origin, (*boxes)[i]->collideLine(ray), stored);
	}
	return stored;
}

Point collideTestVectorToRay(CollideBaseGroup* boxes, Line ray) {
	return smallestDistanceFrom(boxes, ray.getOrigin(), ray);
}

bool collideRectTest(Rect rect, CollideBaseGroup* vec) {
	return !collideRect(rect, vec);
}
