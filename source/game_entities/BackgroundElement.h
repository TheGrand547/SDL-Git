#pragma once
#ifndef BACKGROUND_ELEMENT_H
#define BACKGROUND_ELEMENT_H
#include<SDL.h>
#include "../essential/constants.h"
#include "../primitives/Point.h"
#include "../primitives/Rect.h"
#include "../wrappers/Surface.h"
#include<string>

// Background element of the map, notably the ground
struct BackElement {
	Point position;
	std::string type;
	
	BackElement(Point position, const std::string& type = "missingTexture.jpg");
	BackElement(const BackElement& other);
	~BackElement();
	BackElement& operator=(BackElement& other);
	static std::shared_ptr<Surface> createGroundSurface(const std::string& type = "missingTexture.jpg");
};
#endif
