#pragma once
#ifndef BACKGROUND_ELEMENT_H
#define BACKGROUND_ELEMENT_H
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/Texture.h"
#include "../essential/constants.h"
#include<memory>
#include<string>

/* Background element of the map, notably the ground */
class BackElement {
	protected:
		std::shared_ptr<Texture> texture;
		Rect structure;
		std::string type;
	public:
		BackElement(Rect rect, std::string type = "missingTexture.jpg");
		BackElement(Point position, std::string type = "missingTexture.jpg");
		BackElement(const BackElement& other);
		~BackElement();
		BackElement& operator=(BackElement& other);
		void setTexture(std::shared_ptr<Texture> texture);
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
		static std::shared_ptr<Texture> createGroundTexture(SDL_Renderer* renderer, std::string type = "missingTexture.jpg");
};
#endif
