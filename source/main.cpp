#include "headers.h"

#define unless(condition) if(!condition)

bool init();
SDL_Renderer* createRenderer(SDL_Window* window);
SDL_Window* createWindow();
void close(SDL_Window* window);

int main(int argc, char* argv[]) {
	LOG("Section: Setup");
	// TODO: Write command line args like in source/idtech1, in addition to command line args such as DRAW_PATHS_ENABLE
	std::map<std::string, int> gameState; 
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "RAY_CAST_ENABLE")) {
			gameState["RAY_CAST"] = 1;
		}
	}
	if (!init()) {
		LOG("Failed to initialize!\n");
		return 0;
	}
	SDL_Window* gameWindow = createWindow();
	SDL_Renderer* gRenderer = createRenderer(gameWindow);
	
	srand(time(NULL));
	BoundedPoint screenPosition = BoundedPoint(Screen::MAX_SCREEN_X_POS, Screen::MAX_SCREEN_Y_POS);
	std::shared_ptr<Dot> dot = std::make_shared<Dot>(Point(190, 150));
	dot->setColorChannels(0xFF);
	Configuration config;	
	GameInstance GAME(gameWindow, gRenderer, screenPosition);
	
	GAME.addPlayer(dot);
	AlertTextHandler handler;
	handler.parent = &GAME;
		
	LOG("MAKING THINGS");
	// TODO: Add to analyzer
	GAME.createThing<BigWall>(Rect(0, 200, 100, 300));
	GAME.createThing<BigWall>(Rect(200, 200, 300, 100));
	GAME.createThing<BigWall>(Rect(500, 200, 100, 400));
	GAME.createThing<BigWall>(Rect(600, 500, 100, 300));
	GAME.createThing<BigWall>(Rect(300, 450, 100, 300));
	GAME.createThing<BigWall>(Rect(Line(Point(50, 0), Point(0, 50)), Line(Point(50, 0), Point(100, 50))));
		
	analyzeFile("test.txt", GAME); // Only adds sectors currently, also maybe make this an internal GameInstance method
	
	// Enemy
	std::shared_ptr<BadTest> heck = GAME.createThing<BadTest>(Point(220, 360));
	heck->setTexture(gRenderer);

	// TODO: Add to analyzer
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 25) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 25) {
			if (x % 100 == 0 && y % 100 == 0) {
				GAME.ground.add(Point(x, y), Ground::filenames[Ground::GRASS]);
			}
		}
	}	
	GAME.instanceBegin();
	Font gFont;
	std::string foo = "duck dev best dev";
	AppearingText ap(foo, &gFont, Point(250, 0), 10, COLORS::RED, 300);
	Point playerDelta(0, 0);
	Controller contra;
	contra.addListener("Ray", 120);
	contra.addListener("PathReset", 50);
	contra.addPlayerKeys(playerDelta); // Maybe allow for multiple bindings of the same command somehow? vectors likely? Also remove this dumb fix
	FpsText fps(gFont, Point(100, 10), COLORS::RED); // TODO: Add handler for these things, also have this singular timer passed to all "groups" for consistency
	handler.addMessage(AlertText("this shouldn't last long", Point(300, 150), COLORS::RED, 20, 2500));
	
	Line patrolLine(heck->getPosition(), heck->getPosition() + Point(200, 0));
	patrolLine += Point(0, 5);
	
	SpriteSheet spriteSheetTest("resources/bigsprite.png", 50, 50, gRenderer);
	spriteSheetTest.addAnimation("dumb", 0, 4, 500);
	
	std::shared_ptr<SectorPathFollower> foodd = GAME.createThing<SectorPathFollower>(Rect(GAME.sectors[3]->structure().getCenter(), 10, 10));
	foodd->mine.createPath(GAME.sectors[3], GAME.sectors[0]);
	LOG("Section: Main Loop");
	while (!contra.quit) {
		playerDelta.zero(); // >:(
		contra.handleEvents();
		dot->velocityDelta(playerDelta); // Update player
		GAME.update();
		/* Drawing */
		GAME.draw();
		ap.update(gRenderer);
		if (!gameState["RAY_CAST"] && contra.checkListener(config["Ray"]).getHeld()) { // Raycasting
			dot->rayCast();
		}
		if (contra.checkListener(config["PathReset"]).getHeld() && GAME.gameState["PathFinished"]) {
			auto twigs = GAME.sectors.sectorsThatTouch(dot);
			if (twigs.size() > 0) {
				auto twigsAgain = GAME.sectors.sectorsThatTouch(foodd);
				if (twigsAgain.size() > 0) {
					foodd->mine.createPath(twigsAgain[0], twigs[0]);
				}
			}
		}
		// Testing stuff
		spriteSheetTest.draw("dumb", GAME.getRenderer(), {200, 200}, getDirectionFromAngle(dot->getAngle()));
		patrolLine.drawLine(gRenderer, GAME.getOffset());

		fps.draw(gRenderer);
		fps.drawFrameTime(gRenderer);
		GAME.finalizeFrame();
	}
	LOG("Section: End of Program");
	SDL_DestroyRenderer(gRenderer);
	close(gameWindow);
	return 0;
}

bool init() {
	bool success = true;
	//Initialize SDL
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
	return SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, 
							Screen::SCREEN_HEIGHT, Screen::WINDOW_ARGUMENTS | SDL_RENDERER_PRESENTVSYNC);
}

SDL_Renderer* createRenderer(SDL_Window* window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}
