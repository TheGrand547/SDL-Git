#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primatives/Point.h"
#include "../primatives/Rect.h"
#include "../wrappers/Texture.h"
#include "../constants.h"

/* Background element of the map, notably the ground
 * Various types are supported based on the enum passed to it */
class BackElement {
	private:
		Texture *texture;
		Rect *myRect;
		Ground::Type type;
	public:
		BackElement(Rect rect, Ground::Type type = Ground::GRASS) {
			this->texture = new Texture();
			this->myRect = new Rect(rect);
			this->type = type;
		}
		
		BackElement(Point position, Ground::Type type = Ground::GRASS) {
			this->texture = new Texture();
			this->myRect = new Rect(position, Ground::DEFAULT_WIDTH, Ground::DEFAULT_HEIGHT);
			this->type = type;
		}
		
		~BackElement() {
			delete this->texture;
			delete this->myRect;
		}
		
		void loadTexture(SDL_Renderer* renderer) {
			this->texture->loadFromFile(Ground::filenames[this->type], renderer, this->myRect->getWidth(), this->myRect->getHeight());
			this->texture->setPos(this->myRect->getTopLeft());
			this->texture->setAlpha(0xF0);
		}
		
		void setTexture(Texture* texture) {
			this->texture = texture;
		}
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			this->texture->setPos(this->myRect->getTopLeft());
			this->texture->render(renderer, offset);
		}
		
		static Texture* createGroundTexture(SDL_Renderer* renderer, int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT, 
											Ground::Type type = Ground::GRASS) {
			Texture* temp = new Texture();
			temp->loadFromFile(Ground::filenames[type], renderer, width, height);
			return temp;
		}
};
