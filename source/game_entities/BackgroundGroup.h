#pragma once
#ifndef BACKGROUND_GROUP_H
#define BACKGROUND_GROUP_H
#include<SDL2/SDL.h>
#include "DrawGroup.h"
#include "../wrappers/Texture.h"
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "BackgroundElement.h"
#include<map>
#include<vector>
class BackgroundGroup : public DrawGroup {
	private:
		std::map<Ground::Type, Texture*> textures;
		std::vector<BackElement*> elements; //AHHHHHHHHHHHH
	public:
		BackgroundGroup();
		~BackgroundGroup();
		void add(Point position, Ground::Type type);
		void drawGroup(BoundedPoint& screenPosition);
};
#endif
