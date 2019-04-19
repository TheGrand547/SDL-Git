#pragma once
#include<SDL2/SDL.h>
#include<vector>
#include "BackgroundElement.h"
#include "../wrappers/Texture.h"
#include "../constants.h"

class BackgroundMesh {
	private: 
		Texture* texture;
	public:
		BackgroundMesh(std::vector<BackElement*>* &ground, SDL_Renderer* renderer, int width = Screen::MAX_WIDTH, int height = Screen::MAX_HEIGHT) {
			this->texture = new Texture();
			this->texture->createBlank(renderer, width, height);
			Texture* groundTexture = BackElement::createGroundTexture(renderer);
			SDL_SetRenderTarget(renderer, this->texture->getTexture());
			for (BackElement* floor: *ground) {
				floor->setTexture(groundTexture);
				floor->draw(renderer);
				delete floor;
			}
			SDL_SetRenderTarget(renderer, NULL);
			delete groundTexture;
			ground->clear();
		}
		
		~BackgroundMesh() {
			delete this->texture;
		}
		
		void render(SDL_Renderer* renderer, Point offset = Point(0, 0)) {
			this->texture->render(renderer, offset);
		}
};
