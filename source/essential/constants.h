#pragma once
#include "SDL_Headers.h"
#include <string>
/* File to store all constants */

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
	const int PLAYER_X_DIMENSION = 50;
	const int PLAYER_Y_DIMENSION = 50;
	const int PLAYER_RAY_CAST_LENGTH = 250;
}

namespace Screen {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int MAX_WIDTH = SCREEN_WIDTH * 2;
	const int MAX_HEIGHT = SCREEN_HEIGHT * 2;
	const int DEFAULT_POS = SDL_WINDOWPOS_CENTERED;
	const std::string WINDOW_TITLE = "Testing";
	const Uint32 WINDOW_ARGUMENTS = SDL_WINDOW_SHOWN;// | SDL_WINDOW_FULLSCREEN;
	/* Stupider Constants */
	const int MAX_SCREEN_X_POS = MAX_WIDTH - SCREEN_WIDTH;
	const int MAX_SCREEN_Y_POS = MAX_HEIGHT - SCREEN_HEIGHT;
	const int MAX_X_SCROLL_DISTANCE = MAX_WIDTH - SCREEN_WIDTH / 2;
	const int MAX_Y_SCROLL_DISTANCE = MAX_HEIGHT - SCREEN_HEIGHT / 2;
}
