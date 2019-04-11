#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "primatives/Point.h"
#include "primatives/Rect.h"
#include "wrappers/Texture.h"

/* Enumeration to get rid of overhead on my end */
namespace Ground {
	enum Type {
		GRASS = 0
	};
}

/* Background element of the map, notably the ground
 * Various types are supported based on the enum passed to it */
class BackElement{
	private:
		/* TODO: Create a constants file */
		static const int DEFAULT_WIDTH = 100; 
		static const int DEFAULT_HEIGHT = 100;
		Texture *texture;
		Rect *myRect;
	public:
		BackElement(Rect rect, int type = Ground::GRASS) {
			this->texture = new Texture();
			this->myRect = new Rect(rect);
		}
		
		BackElement(Point position, int type = Ground::GRASS) {
			this->texture = new Texture();
			this->myRect = new Rect(position, DEFAULT_WIDTH, DEFAULT_HEIGHT);
		}
		
		~BackElement() {
			delete this->texture;
			delete this->myRect;
		}
		
		void loadTexture(SDL_Renderer* renderer, std::string path = "resources/grass.png") {
			this->texture->loadFromFile(path, renderer, this->myRect->getWidth(), this->myRect->getHeight());
			this->texture->setPos(this->myRect->getTopLeft());
			this->texture->setAlpha(0xF0);
		}
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			this->texture->render(renderer, offset);
		}
};
