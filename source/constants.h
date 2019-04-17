#pragma once
#include<SDL2/SDL.h>
/* File to store all constants */


namespace cBox {
	const int BOX_WIDTH = 100;
	const int BOX_HEIGHT = 100;
	const float BOX_OUTDENT = .5;
	const SDL_Color BOX_INNER_BORDER_COLOR = {0x30, 0x30, 0x30, 0xFF};
	const SDL_Color BOX_OUTER_BORDER_COLOR = {0x00, 0x00, 0x00, 0xFF};
}

/* Enumeration to get rid of overhead on my end 
 * as all background elements are fundamentally the same */
namespace Ground {
	enum Type {
		GRASS = 0, METAL = 1
	};
	const std::string filenames[2] = {"resources/grass.png", "missingTexture.jpg"};
	const int DEFAULT_WIDTH = 100; 
	const int DEFAULT_HEIGHT = 100;
}

namespace Player {
	const int PLAYER_X_DIMENSION = 10;
	const int PLAYER_Y_DIMENSION = 10;
}

namespace Screen {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	const int MAX_WIDTH = 1280;
	const int MAX_HEIGHT = 960;
}
