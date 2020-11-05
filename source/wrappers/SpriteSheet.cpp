#include "SpriteSheet.h"
/* 
Animation definition structure should be something as follows, 
example: file=SpritSheet.png;size=50x50;
# Filename
file = ...; 
# Following only apply to sprite sheets
# Dimension of each sprite in 480x640 style
size = ...;
*/

SpriteSheet::SpriteSheet(SDL_Renderer* renderer, const std::string& filename, int width, int height) : key(""), width(width), height(height) {
	this->frame.loadFromFile(renderer, filename);
	this->frame.setColorKey(0xFF, 0xFF, 0xFF);
	this->maxX = this->frame.getWidth() / this->width;
	this->maxY = this->frame.getHeight() / this->height;
	if (this->maxY != 8) LOG("Improperly formatted SpriteSheet! Expected 8 rows, got %i rows.", this->maxY);
}

SpriteSheet::~SpriteSheet() {}

bool SpriteSheet::draw(std::string tag, SDL_Renderer* renderer, Point position, EntityDir dir) {
	/* True - the selected animation either doesn't exist or is finished playing
	 * False - the selected animation displayed properly */
	if (!this->animations[tag].isReal()) return false;
	if (!this->animations[tag].isStarted()) {
		this->animations[this->key].exit();
		this->animations[tag].start();
		this->key = tag;
	}
	if (!this->animations[this->key].update()) return false;

	Uint index = this->animations[this->key].currentIndex;
	if (index >= this->maxX) {
		LOG("ERROR: Sprite Sheet Index out of bounds! %i is greater than the width of %i!", index, this->maxX);
		return false;
	}

	SDL_Rect rectangle;
	rectangle.x = index * this->width;
	rectangle.y = dir * this->height;
	rectangle.w = this->width;
	rectangle.h = this->height;
	this->frame.draw(renderer, position, &rectangle);
	return true;
}

void SpriteSheet::addAnimation(std::string tag, Uint startingIndex, Uint endingIndex, Uint interval) {
	if (this->animations[tag].isReal()) return;
	if (startingIndex >= this->maxX || endingIndex >= this->maxX) {
		LOG("ERROR: Sprite Sheet Index out of bounds! %i or %i is greater than the width of %i!", startingIndex, endingIndex, this->maxX);
		return;
	}
	this->animations[tag] = SpriteSheet::Animation(startingIndex, endingIndex, interval);
}


SpriteSheet::Animation::Animation(Uint startingIndex, Uint endingIndex, Uint interval) : started(false), endingIndex(endingIndex), 
					interval(interval), startingIndex(startingIndex), currentIndex(0) {}

SpriteSheet::Animation::Animation(const Animation& other) : started(other.started), endingIndex(other.endingIndex), 
					interval(other.interval), startingIndex(other.startingIndex), currentIndex(other.currentIndex) {}

SpriteSheet::Animation::~Animation() {}

SpriteSheet::Animation& SpriteSheet::Animation::operator=(const SpriteSheet::Animation& other) {
	if (this != &other) {
		this->started = other.started;
		this->currentIndex = other.currentIndex;
		this->endingIndex = other.endingIndex;
		this->interval = other.interval;
		this->startingIndex = other.startingIndex;
	}
	return *this;
}

bool SpriteSheet::Animation::isReal() const {
	return this->interval;
}

bool SpriteSheet::Animation::isStarted() const {
	return this->started;
}

bool SpriteSheet::Animation::update() {
	if (this->started && this->timer.getTicks() >= this->interval) {
		this->currentIndex++;
		this->started = this->currentIndex <= this->endingIndex;
		this->timer.start();
	}
	return this->started;
}

void SpriteSheet::Animation::exit() {
	this->currentIndex = this->startingIndex;
	this->started = false;
	this->timer.stop();
}

void SpriteSheet::Animation::pause() {
	this->timer.pause();
}

void SpriteSheet::Animation::start() {
	this->started = true;
	this->timer.start();
	this->currentIndex = this->startingIndex;
}

void SpriteSheet::Animation::reset() {
	this->start();
}
