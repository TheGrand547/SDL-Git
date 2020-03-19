#include "source/headers.h"
#include "source/GameInstance.h"
#include "source/wrappers/SpriteSheet.h"
bool init();
SDL_Renderer* createRenderer(SDL_Window* window);
SDL_Window* createWindow();
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

// TODO: Static Member Variable Initialization -> Should put somewhere less conspicuous
SDL_Renderer* MegaBase::renderer = NULL;
Point* MegaBase::offset = NULL;
SuperTexture Box::mTexture;


int main(int argc, char* argv[]) {
	std::map<std::string, int> gameState; // TODO: Write command line args like in source/idtech1, in addition to command line args such as DRAW_PATHS_ENABLE
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "RAY_CAST_ENABLE")) {
			gameState["RAY_CAST"] = 1;
		}
	}
	if(!init()) {
		printf("Failed to initialize!\n");
		return 0;
	}
	SDL_Window* gameWindow = createWindow();
	SDL_Renderer* gRenderer = createRenderer(gameWindow);
	srand(time(NULL));
	BoundedPoint screenPosition = BoundedPoint(Screen::MAX_SCREEN_X_POS, Screen::MAX_SCREEN_Y_POS);
	std::shared_ptr<Dot> dot = std::make_shared<Dot>(Point(190, 150));
	dot->setColorChannels(0xFF);
	Configuration config;	
	// TODO: Create a file structure for containing level data so its not hardcoded 
	// TODO: Have some DrawGroup pointers for collision, node, and other groups/structures needed
	GameInstance GAME(gRenderer, screenPosition);
	GAME.addThing(dot);
	MegaBase::setOffset(&GAME.getOffset());
	MegaBase::setRenderer(gRenderer);
	AlertTextHandler handler;
	BackgroundGroup groundGroup;
	
	GAME.createThing<BigWall>(Rect(0, 200, 100, 300));
	GAME.createThing<BigWall>(Rect(200, 200, 300, 100));
	GAME.createThing<BigWall>(Rect(500, 200, 100, 400));
	GAME.createThing<BigWall>(Rect(600, 500, 100, 300));
	GAME.createThing<BigWall>(Rect(300, 450, 100, 300));
	GAME.addThing(std::make_shared<BigWall>(Rect(Line(Point(50, 0), Point(0, 50)), Line(Point(50, 0), Point(100, 50)))));
	
	// Enemy
	std::shared_ptr<BadTest> heck = std::make_shared<BadTest>(Point(120, 380));
	heck->setTexture(gRenderer);
	GAME.addThing(heck);
	groundGroup.setParent(GAME);

	for (int x = 0; x <= Screen::MAX_WIDTH; x += 25) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 25) {
			if (x % 100 == 0 && y % 100 == 0) {
				groundGroup.add(Point(x, y), Ground::filenames[Ground::GRASS]);
			}
		}
	}
	GAME.instanceBegin();
	Font gFont;
	std::string foo = "duck dev best dev";
	AppearingText ap(foo, &gFont, Point(250, 0), 15, COLORS::RED, 300);
	PointDelta popo = PointDelta(0, 0, 2);
	Controller contra;
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(popo); // Maybe allow for multiple bindings of the same command somehow? vectors likely? Also remove this dumb fix
	FpsText fps(gFont, Point(100, 10), COLORS::RED); // TODO: Add handler for these things, also have this singular timer passed to all "groups" for consistency
	handler.addMessage(AlertText("this shouldn't last long", Point(300, 150), COLORS::RED, 20, 2500));
	// TODO: Standardize between draw and render, ie pick one you indecisive fuck
	// Pass dot values it needs
	Line lip(heck->getPosition(), heck->getPosition() + Point(200, 0));
	lip += Point(0, 5);
	SpriteSheet g("resources/animtest.png", 50, 50, gRenderer);
	while(!contra.quit) {
		clearScreen(gRenderer);
		popo.zero(); // >:(
		contra.handleEvents();
		dot->velocityDelta(popo); // Update player
		GAME.update();
		/* Drawing */
		groundGroup.drawGroup();
		GAME.draw();
		//bads.drawGroup();
		//ap.update(gRenderer);
		//dot.draw(); // Player must always be drawn onto the top layer for best visibility, for the time being
		if (gameState["RAY_CAST"]) {
			if (contra.checkListener(config["Ray"]).getHeld()) { // Raycasting
				dot->rayCast();
			}
		}
		g.draw(gRenderer);
		lip.drawLine(gRenderer);
		fps.draw(gRenderer);
		renderChanges(gRenderer, gameWindow);
	}
	close(gameWindow);
	return 0;
}

bool init() {
	bool success = true;
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		if (TTF_Init() < 0) {
			printf("True Type Font could not be Initialized!");
			success = false;
		}
	}
	return success;
}

SDL_Window* createWindow() {
	return SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, Screen::WINDOW_ARGUMENTS);
}

SDL_Renderer* createRenderer(SDL_Window* window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void close(SDL_Window* window) {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void clearScreen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);
}

void renderChanges(SDL_Renderer* renderer, SDL_Window* window) {
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
