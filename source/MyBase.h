#pragma once
#include<iostream>
/*
 * Really simple class to base any type of object that needs to have color channels 
 * defined. 
 */ 

class MyBase {
	public:
		uint8_t rChannel,  bChannel, gChannel, aChannel;
		
		MyBase(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF) {
			this->rChannel = r;
			this->gChannel = g;
			this->bChannel = b;
			this->aChannel = a;
		}
		
		void setColorChannels(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF) { 
			this->rChannel = r;
			this->gChannel = g;
			this->bChannel = b;
			this->aChannel = a;
		}
		void _setColorChannels(uint8_t r = 0x00, uint8_t g = 0x00, uint8_t b = 0xFF, uint8_t a = 0xFF) { 
			rChannel = r;
			gChannel = g;
			bChannel = b;
			aChannel = a;
		}
		
		void setColorChannels(MyBase* other) {
			this->rChannel = other->rChannel;
			this->gChannel = other->gChannel;
			this->bChannel = other->bChannel;
			this->aChannel = other->aChannel;
		}
		
		void setColorChannels(MyBase other) {
			this->rChannel = other.rChannel;
			this->gChannel = other.gChannel;
			this->bChannel = other.bChannel;
			this->aChannel = other.aChannel;
		}
		
		void setColorChannels(int r, int g, int b, int a) {
			rChannel = r;
			gChannel = g;
			bChannel = b;
			aChannel = a;
		}
};
