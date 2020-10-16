#pragma once
#include "SDL_Headers.h"
#include <string>
// File to store all constants*

namespace Colors {
	const SDL_Color Red = {0xFF, 0x00, 0x00, 0xFF};
	const SDL_Color Blue = {0x00, 0x00, 0xFF, 0xFF};
	const SDL_Color Green = {0x00, 0xFF, 0x00, 0xFF};
	const SDL_Color Cyan = {0x00, 0xFF, 0xFF, 0xFF};
	const SDL_Color Black = {0x00, 0x00, 0x00, 0xFF};
	const SDL_Color DarkGray = {0x30, 0x30, 0x30, 0xFF};
	const SDL_Color LightGray = {0xC0, 0xC0, 0xC0, 0xFF};
}

namespace Player {
	const int xDimension = 15;
	const int yDimension = 30;
	const int rayCastLength = 250;
}

namespace Screen {
	const int width = 640;
	const int height = 480;
	const int maxWidth = width * 2;
	const int maxHeight = height * 2;
	const int defaultPos = SDL_WINDOWPOS_CENTERED;
	const std::string title = "Testing";
	const Uint32 arguments = SDL_WINDOW_SHOWN;// | SDL_WINDOW_FULLSCREEN;
	/* Stupider Constants */
	const int xPositionMax = maxWidth - width;
	const int yPositionMax = maxHeight - height;
	const int xScrollMax = maxWidth - (width / 2);
	const int yScrollMax = maxHeight - (height / 2);
}
