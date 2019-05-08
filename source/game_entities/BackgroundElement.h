#pragma once
#include<iostream>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primatives/Point.h"
#include "../primatives/Rect.h"
#include "../wrappers/Texture.h"
#include "../essential/constants.h"

/* Background element of the map, notably the ground
 * Various types are supported based on the enum passed to it */
class BackElement {
	private:
		Texture *texture;
		Point *position;
		Ground::Type type;
	public:
		BackElement(Rect rect, Ground::Type type = Ground::GRASS) {
			this->position = new Point(rect.getTopLeft());
			this->type = type;
			this->texture = NULL;
		}
		
		BackElement(Point position, Ground::Type type = Ground::GRASS) {
			this->position = new Point(position);
			this->type = type;
			this->texture = NULL;
		}
		
		~BackElement() {
			delete this->position;
		}
		
		void setTexture(Texture* texture) {
			this->texture = texture;
		}
		
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			if (this->texture != NULL) {
				this->texture->setPos(this->position);
				this->texture->render(renderer, offset);
			}
		}
		
		static Texture* createGroundTexture(SDL_Renderer* renderer, Ground::Type type = Ground::GRASS, int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT) {
			Texture* temp = new Texture();
			temp->loadFromFile(Ground::filenames[type], renderer, width, height);
			return temp;
		}
		
		static void createGroundTexture(SDL_Renderer* renderer, Texture* texture, Ground::Type type = Ground::GRASS, int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT) {
			texture->loadFromFile(Ground::filenames[type], renderer, width, height);
		}
		
		static void setGroundTextures(std::vector<BackElement*>* vec, Texture* texture) {
			for (BackElement* back: *vec) {
				back->setTexture(texture);
			}
		}
};
