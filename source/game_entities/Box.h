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
class Box : public CollideBase {
	private:
		Rect rect;
		static SuperTexture mTexture;
	public:
		Box();
		Box(Point position);
		~Box();
		Box(const Box& that);
		Box& operator=(const Box& that);
		bool overlap(Rect& other) override;
		bool doesLineCollide(Line& ray) override;
		Point collideLine(Line& ray) override;
		Point getTopLeft() override;
		Point getBottomRight() override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		static void drawBox(SDL_Renderer* renderer, Point position, Point offset = Point(0, 0));
		static void createBoxTexture(SDL_Renderer* renderer);
};
