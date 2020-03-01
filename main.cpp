#include "source/headers.h"
#include "source/GameInstance.h"
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
	Rect f(Point(0, 0), Point(20, 20));
	Rect f2(Point(0, 0), Point(20, 20));
	Rect g(Point(21, 21), Point(25, 25));
	Rect te(Point(5, 5), Point(34, 7));
	std::cout << "f == f2: " << (f == f2) << std::endl;
	std::cout << "f == g: " << (f == g) << std::endl;
	std::cout << "f.overlap(g): " << f.overlap(g) << std::endl; 
	std::cout << "g.overlap(f): " << g.overlap(f) << std::endl;
	std::cout << "te.overlap(f): " << te.overlap(f) << std::endl; 
	std::cout << "te.overlap(g): " << te.overlap(g) << std::endl; 
	std::cout << "Float: " << sizeof(float) << std::endl;
	std::cout << "Double: " << sizeof(double) << std::endl;
	std::cout << "Point: " << sizeof(Point) << std::endl;
	std::cout << "Line: " << sizeof(Line) << std::endl;
	std::cout << "Rect: " << sizeof(Rect) << std::endl;
	std::cout << "Node: " << sizeof(Node) << std::endl;
	std::cout << "Node Pointer: " << sizeof(Node*) << std::endl;
	std::cout << "Node Smart Pointer: " << sizeof(std::shared_ptr<Node>) << std::endl;
	std::cout << "BigWall: " << sizeof(BigWall) << std::endl;
	std::cout << "Vector: " << sizeof(std::vector<bool>) << std::endl;
	//return 0;
	std::map<std::string, int> gameState; // This will later be placed into the class to hold level instances
	// TODO: Write command line args like in source/idtech1, in addition to command line args such as DRAW_PATHS_ENABLE
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
	// Box creation
	//Box::createBoxTexture(gRenderer);

	GAME.addThing(std::make_shared<BigWall>(Rect(0, 200, 100, 300)));
	GAME.addThing(std::make_shared<BigWall>(Rect(200, 200, 300, 100)));
	GAME.addThing(std::make_shared<BigWall>(Rect(500, 200, 100, 400)));
	GAME.addThing(std::make_shared<BigWall>(Rect(600, 500, 100, 300)));
	GAME.addThing(std::make_shared<BigWall>(Rect(300, 450, 100, 300)));
	//std::shared_ptr<BadTest> heck = std::make_shared<BadTest>(Point(100, 400));
	//heck->setTexture(gRenderer);
	//GAME.addThing(heck);
	groundGroup.setParent(GAME);

	for (int x = 0; x <= Screen::MAX_WIDTH; x += 25) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 25) {
			//GAME.addNode(Point(x, y));
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
	Line lip(Point(325, 425), Point(125, 425));
	lip += Point(0, 5);
	Rect testtest(Line(Point(0, 5), Point(5, 0)), Line(Point(10, 15), Point(15, 10)));
	Point pef[] = {testtest.getTopLeft(), testtest.getTopRight(), testtest.getBottomRight(), testtest.getBottomLeft()};
	for (Point pgbab: pef) {
		std::cout << pgbab << std::endl;
	}
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
		testtest.draw(gRenderer, Point(0, 0));
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
