#include "SpriteSheet.h"


/// TODO: Rewrite this as just a storage place for various textures, instead of the animation thing it is now
/* 
Animation definition structure should be something as follows, 
Everything on a line after a '#' will be ignored as a comment
Each semicolon is treated as a line break
example: file=SpritSheet.png;delay=50;size=50x50;
# Filename
file = ...; 
# Interval between frames, in milliseconds
delay = 50; 
# Following only apply to sprite sheets
# Dimension of each sprite in 480x640 style
size = ...;
*/
// file=resources/animtest.png;delay=50;size=64x64;

// Cause i'm lazy and I want the background code to work i'll do this later

SpriteSheet::SpriteSheet(const std::string& filename, int width, int height, SDL_Renderer* renderer) : key(""), width(width), height(height) {
	this->frame.loadFromFile(renderer, filename);
	this->frame.setColorKey(0xFF, 0xFF, 0xFF);
	this->maxX = this->frame.getWidth() / this->width;
	this->maxY = this->frame.getHeight() / this->height;
	if (this->maxY != 8) {
		LOG("Improperly formatted SpriteSheet! Expected 8 rows, got %i rows.", this->maxY);
	}
}

SpriteSheet::~SpriteSheet() {}

void SpriteSheet::draw(SDL_Renderer* renderer, Point position, EntityDir dir, Uint index) {
	if (index >= this->maxX) {
		LOG("ERROR: Sprite Sheet Index out of bounds! %i is greater than the width of %i!", (int)index, this->maxX);
		return;
	}
	SDL_Rect f;
	f.x = (index % this->maxX) * this->width;
	f.y = (dir % this->maxY) * this->height;
	f.w = this->width;
	f.h = this->height;
	
	this->frame.draw(renderer, position, &f);
}

void SpriteSheet::draw(SDL_Renderer* renderer, Point position, EntityDir dir) {
	if (!this->animations[this->key].isReal()) return;
	this->animations[this->key].update();
	this->draw(renderer, position, dir, this->animations[this->key].currentIndex);
}

void SpriteSheet::addAnimation(std::string tag, Uint startingIndex, Uint endingIndex, Uint interval) {
	if (this->animations[tag].isReal()) return;
	if (startingIndex >= this->maxX || endingIndex >= this->maxX) {
		LOG("ERROR: Sprite Sheet Index out of bounds! %i or %i is greater than the width of %i!", startingIndex, endingIndex, this->maxX);
		return;
	}
	this->animations[tag] = Animation(startingIndex, endingIndex, interval);
}

void SpriteSheet::startAnimation(std::string tag) {
	if (this->animations[tag].isReal()) {
		if (!strcmp(this->key.c_str(), tag.c_str())) { // Same tag, restart animation
			this->animations[tag].reset();
		} else { // New animation
			this->animations[this->key].exit();
			this->animations[tag].start();
			this->key = tag;
		}
	} else {
		LOG("Invalid Animation tag of %s", tag.c_str());
	}
}
