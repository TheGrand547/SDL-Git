#pragma once
class MyBase {
public:
	uint8_t rChannel,  bChannel, gChannel, aChannel;
	void setColorChannels(uint8_t r = 0x00, uint8_t g = 0x00, 
						uint8_t b = 0xFF, uint8_t a = 0xFF) { 
		rChannel = r;
		gChannel = g;
		bChannel = b;
		aChannel = a;
	}
	void _setColorChannels(uint8_t r = 0x00, uint8_t g = 0x00, 
						uint8_t b = 0xFF, uint8_t a = 0xFF) { 
		rChannel = r;
		gChannel = g;
		bChannel = b;
		aChannel = a;
	}
	
	void setColorChannels(int r, int g, int b, int a) {
		rChannel = r;
		gChannel = g;
		bChannel = b;
		aChannel = a;
	}

};
