#include "headers.h"
#include "DataStructure.h"

bool init();
SDL_Renderer* createRenderer(SDL_Window*& window);
SDL_Window* createWindow();
void close(SDL_Window* window);

// TODO: Pick and stick to standard names for arguments, like all `const double&` should be num if theres just one etc

int main(int argc, char* argv[]) {
	LOG("Section: Setup");

	if (!init()) {
		LOG("Failed to initialize!\n");
		return 0;
	}
	SDL_Window* gameWindow = createWindow();
	SDL_Renderer* gRenderer = createRenderer(gameWindow);
	// TODO: Put this in a good place
	BoundedPoint screenPosition = BoundedPoint(Screen::xPositionMax, Screen::yPositionMax);
	GameInstance GAME(gameWindow, gRenderer, screenPosition);
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "RAY_CAST_ENABLE")) {
			GAME.gameState["RAY_CAST"] = 1;
		}
		if (!strcmp(argv[i], "-uncappedfps")) {
			GAME.gameState["cv_capped_fps"] = 1;
		}
	}

	srand(time(NULL));
	std::shared_ptr<Dot> player = std::make_shared<Dot>(Point(150, 150));
	player->setColorChannels((Uint8) 0xFF);
	Configuration config;
	GAME.addPlayer(player);

	LOG("MAKING THINGS");

	analyzeFile("level.txt", GAME); // Only adds sectors/walls currently, also maybe make this an internal GameInstance method

	// Enemy
	const Point BAD_POINT(220, 360);
	std::shared_ptr<BadTest> heck = GAME.createThing<BadTest>(BAD_POINT);
	GAME.gameState["verbose"] = 1;
	// TODO: Add to analyzer
	for (int x = 0; x <= Screen::maxWidth + 100; x += 25) {
		for (int y = 0; y <= Screen::maxWidth + 100; y += 25) {
			if (x % 100 == 0 && y % 100 == 0) {
				GAME.ground.add(Point(x, y), "resources/grass.png");
			}
		}
	}
	Font gFont;
	std::string foo = "duck dev best dev";
	std::shared_ptr<AppearingText> ap = GAME.createText<AppearingText>(foo, Point(250, 0), 10, Colors::Red, 300);
	ap->setFont(gFont);
	Point playerDelta(0, 0);
	Controller contra;
	contra.parent = &GAME;
	contra.addCheat("hell", [](GameInstance* g) {g->createText<AppearingText>("u suck dum dum", Point(250, 100), 10, Colors::Red, 300);});
	contra.addListener("Ray", 120);
	contra.addListener("PathReset", 50);
	contra.addListener("Shoot", 500);
	contra.addPlayerKeys(playerDelta); // Maybe allow for multiple bindings of the same command somehow? vectors likely? Also remove this dumb fix
	FpsText fps(gFont, Point(100, 10), Colors::Red);
	
	GAME.createText<AlertText>("this shouldn't last long", Point(300, 150), Colors::Red, 20, 2500);

	SpriteSheet spriteSheetTest(gRenderer, "resources/bigsprite.png", 50, 50);
	spriteSheetTest.addAnimation("dumb", 0, 4, 500);

	std::shared_ptr<SectorPathFollower> foodd = GAME.createThing<SectorPathFollower>(Rect(GAME.sectors[3]->structure().getCenter(), 25, 25));
	//std::shared_ptr<BasicBullet> bb = GAME.createThing<BasicBullet>(Point(100, 100));

	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);

	std::shared_ptr<FootSteps> foots = GAME.createThing<FootSteps>();

	Surface surf;
	surf.load("resources/missingTexture.jpg");
	//surf.limitPalette();
	surf.bilateralFilter(50, 10, 5);
	surf.limitPalette();
	GAME.instanceBegin();
	// TODO: Do more testing on pathfinding
	foodd->mine.createPath(GAME.sectors[3], GAME.sectors[0]);
	player->ping();
	LOG("Section: Main Loop");
	while (!contra.quit) {
		playerDelta.zero(); // >:(
		contra.handleEvents();
		player->velocityDelta(playerDelta); // Update player
		GAME.update();
		// Drawing
		GAME.draw();
		if (!GAME.gameState["RAY_CAST"] && contra.checkListener(config["Ray"]).getHeld()) { // Raycasting
			player->rayCast();
		}
		if (contra.checkListener(config["PathReset"]).getHeld() && GAME.gameState["PathFinished"]) {
			auto twigs = GAME.sectors.currentSector(player);
			if (twigs) {
				auto twigsAgain = GAME.sectors.currentSector(foodd);
				if (twigsAgain) {
					foodd->mine.createPath(twigsAgain, twigs);
				}
			}
		}
		if (contra.checkListener(config["Shoot"]).getHeld()) {
			player->shoot();
			contra.checkListener(config["Shoot"]).reset();
		}
		
		// Testing stuff
		spriteSheetTest.draw("dumb", GAME.getTrueRenderer(), {200, 200}, getDirectionFromAngle(player->getAngle()));

		GAME.sectors.drawGroup();
		fps.draw(GAME.getRenderer());
		fps.drawFrameTime(GAME.getRenderer());
		surf.draw(gRenderer, Point(0,0));
		GAME.finalizeFrame();
	}
	LOG("Section: End of Program");
	SDL_DestroyRenderer(gRenderer);
	close(gameWindow);
	return 0;
}

bool init() {
	bool success = true;
	// Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		LOG("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		if (TTF_Init() < 0) {
			LOG("True Type Font could not be Initialized!");
			success = false;
		}
	}
	return success;
}

SDL_Window* createWindow() {
	return SDL_CreateWindow(Screen::title.c_str(), Screen::defaultPos, Screen::defaultPos, Screen::width, 
							Screen::height, Screen::arguments);
}

SDL_Renderer* createRenderer(SDL_Window*& window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
