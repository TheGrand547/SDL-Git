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
#include<memory>
#include<string>
#include<vector>
class BackgroundGroup : public DrawGroup {
	private:
		std::map<std::string, std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<BackElement>> elements;
	public:
		BackgroundGroup();
		~BackgroundGroup();
		bool exists() override;
		int size() override;
		void add(Point position, std::string type = "missingTexture.jpg");
		void clearGroup() override;
		void drawGroup() override;
};
#endif
