#pragma once
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
class BackElement { // TODO: Fix the over reliance on Ground::filenames
	protected:
		std::shared_ptr<Texture> texture;
		Point position;
		std::string type;
	public:
		BackElement();
		BackElement(Rect rect, std::string type = Ground::filenames[Ground::GRASS]);
		BackElement(Point position, std::string type = Ground::filenames[Ground::GRASS]);
		BackElement(const BackElement& other);
		~BackElement();
		BackElement& operator=(BackElement& other);
		void setTexture(std::shared_ptr<Texture> texture);
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
		static std::shared_ptr<Texture> createGroundTexture(SDL_Renderer* renderer, std::string type = "missingTexture.jpg", int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT);
		static void createGroundTexture(SDL_Renderer* renderer, std::shared_ptr<Texture> texture, std::string type = Ground::filenames[Ground::GRASS], int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT);
};
