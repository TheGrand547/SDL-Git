#include "MyBase.h"

MyBase::MyBase(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	this->rChannel = r;
	this->gChannel = g;
	this->bChannel = b;
	this->aChannel = a;
}

MyBase::MyBase(SDL_Color color) {
	this->rChannel = color.r;
	this->gChannel = color.g;
	this->bChannel = color.b;
	this->aChannel = color.a;
}

void MyBase::setColorChannels(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { 
	this->rChannel = r;
	this->gChannel = g;
	this->bChannel = b;
	this->aChannel = a;
}

void MyBase::setColorChannelsTo(MyBase other) {
	this->rChannel = other.rChannel;
	this->gChannel = other.gChannel;
	this->bChannel = other.bChannel;
	this->aChannel = other.aChannel;
}

void MyBase::setColorChannels(SDL_Color color) {
	this->rChannel = color.r;
	this->gChannel = color.g;
	this->bChannel = color.b;
	this->aChannel = color.a;
}

