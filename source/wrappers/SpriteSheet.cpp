#include "SpriteSheet.h"


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

SpriteSheet::SpriteSheet(const std::string& filename, int width, int height, SDL_Renderer* renderer) : width(width), 
					height(height), currentX(0), currentY(0) {
	this->frame.loadFromFile(filename, renderer);
	this->frame.setColorKey(0xFF, 0xFF, 0xFF);
	this->maxX = this->frame.getWidth() / this->width;
	this->maxY = this->frame.getHeight() / this->height;
}

SpriteSheet::~SpriteSheet() {}

void SpriteSheet::draw(SDL_Renderer* renderer, Point position) {
	SDL_Rect f;
	f.x = (this->currentX % this->maxX) * this->width;
	f.y = (this->currentY % this->maxY) * this->height;
	f.w = this->width;
	f.h = this->height;
	
	this->frame.draw(position, renderer, &f);
}

void SpriteSheet::drawTo(SDL_Renderer* renderer, Texture& fo) {
	std::cout << renderer << " and " << &fo << std::endl;
}
