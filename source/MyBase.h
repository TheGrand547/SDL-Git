#pragma once
#include<SDL2/SDL.h>

/* Really simple class to base any type of object that needs to have color channels defined. */ 
class MyBase {
	public:
		uint8_t rChannel,  bChannel, gChannel, aChannel;
		MyBase(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF);
		MyBase(SDL_Color color);
		void setColorChannels(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF);
		void setColorChannelsTo(MyBase other);
		void setColorChannelsOf(MyBase other);
		void setColorChannels(SDL_Color color);
};
