#pragma once
#ifndef BACKGROUND_GROUP_H
#define BACKGROUND_GROUP_H
#include "BackgroundElement.h"
#include "DrawGroup.h"
#include "../GameInstance.h"
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "../wrappers/Texture.h"
#include<map>
#include<memory>
#include<SDL2/SDL.h>
#include<string>
#include<vector>

class BackgroundGroup : public DrawGroup {
	private:
		GameInstance* parent;
		std::map<std::string, std::shared_ptr<Texture>> textures;
		std::vector<std::shared_ptr<BackElement>> elements;
	public:
		BackgroundGroup();
		~BackgroundGroup();
		bool exists() override;
		int size() override;
		void add(Point position, const std::string& type = "missingTexture.jpg");
		void clearGroup() override;
		void drawGroup() override;
		void setParent(GameInstance& parent);
};
#endif
