#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2_image/SDL_image.h>
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/Texture.h"
#include "../essential/constants.h"

/* Background element of the map, notably the ground
 * Various types are supported based on the enum passed to it */
class BackElement { // TODO: Come back and fix this
	private:
		Texture* texture;
		Point position;
		Ground::Type type;
	public:
		BackElement();
		BackElement(Rect rect, Ground::Type type = Ground::GRASS);
		BackElement(Point position, Ground::Type type = Ground::GRASS);
		BackElement(const BackElement& other);
		~BackElement();
		BackElement& operator=(BackElement& other);
		void setTexture(Texture* texture);
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0));
		static Texture* createGroundTexture(SDL_Renderer* renderer, Ground::Type type = Ground::GRASS, int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT);
		static void createGroundTexture(SDL_Renderer* renderer, Texture* texture, Ground::Type type = Ground::GRASS, int width = Ground::DEFAULT_WIDTH, int height = Ground::DEFAULT_HEIGHT);
};
