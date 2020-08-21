#pragma once
#ifndef BACKGROUND_GROUP_H
#define BACKGROUND_GROUP_H

class BackgroundGroup;

#include "BackgroundElement.h"
#include "DrawGroup.h"
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "../wrappers/Surface.h"
#include<map>
#include<memory>
#include<SDL2/SDL.h>
#include<string>
#include<vector>

class BackgroundGroup : public DrawGroup {
	private:
		bool fullyRendered;
		std::vector<std::shared_ptr<BackElement>> elements;
		Texture texture;
	public:
		BackgroundGroup(GameInstance* parent);
		~BackgroundGroup();
		bool exists() override;
		int size() override;
		void add(Point position, const std::string& type = "missingTexture.jpg");
		void clearGroup() override;
		void drawGroup() override;
		void finalize();
		void setParent(GameInstance& parent);
};
#endif
