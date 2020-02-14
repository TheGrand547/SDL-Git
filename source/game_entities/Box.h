#pragma once
#include<SDL2/SDL.h>
#include<vector>
#include "../BoundedPoint.h"
#include "../essential/constants.h"
#include "../essential/util.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/SuperTexture.h"	
#include "../wrappers/Texture.h"
#include "base/CollideBase.h"
#include "CollideBaseGroup.h"
typedef uint32_t Uint32;

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
		bool overlap(const Rect other) const override;
		bool overlap(const std::shared_ptr<ThingBase>& other) const override;
		bool doesLineCollide(const Line& ray) const override;
		float originDistance() const override;
		Point collideLine(const Line& ray) const override;
		Point getTopLeft() const override;
		Point getBottomRight() const override;
		Rect getRect() const override;
		void draw(SDL_Renderer* renderer, Point offset = Point(0, 0)) override;
		static void drawBox(SDL_Renderer* renderer, Point position, Point offset = Point(0, 0));
		static void createBoxTexture(SDL_Renderer* renderer);
		void update() override;
};
