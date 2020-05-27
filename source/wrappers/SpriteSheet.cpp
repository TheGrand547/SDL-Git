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

SpriteSheet::SpriteSheet(const std::string& filename, int width, int height, SDL_Renderer* renderer) : width(width), height(height) {
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
		LOG("ERROR: Sprite Sheet Index out of bounds! %i is greater than the width of %i!", index, this->maxX);
		return;
	}
	int x = dir;
	x++;
	SDL_Rect f;
	f.x = (index % this->maxX) * this->width;
	f.y = (0 % this->maxY) * this->height;
	f.w = this->width;
	f.h = this->height;
	
	this->frame.draw(renderer, position, &f);
}
