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
		std::vector<BackElement*> elements;
	public:
		BackgroundGroup();
		~BackgroundGroup();
		int size() override;
		void add(Point position, Ground::Type type);
		void clearGroup() override;
		void drawGroup() override;
};
#endif
