#include "source/headers.h"
bool init();
SDL_Renderer* createRenderer(SDL_Window* window);
SDL_Window* createWindow();
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

// Static Member Variable Initialization -> Should put somewhere less conspicuous
SDL_Renderer* MegaBase::renderer = NULL;
BoundedPoint* MegaBase::offset = NULL;
SuperTexture Box::mTexture;

int main(int argc, char* argv[]) {
	if(!init()) {
		printf("Failed to initialize!\n");
		return 0;
	}
	/* TODO: Add Method/Class for initializing everything on screen to clean up main() and help smooth the transition to using 'Screen' as the base class for the project */
	SDL_Window* gameWindow = createWindow();
	SDL_Renderer* gRenderer = createRenderer(gameWindow);
	srand(time(NULL));
	BoundedPoint screenPosition = BoundedPoint(Screen::MAX_SCREEN_X_POS, Screen::MAX_SCREEN_Y_POS);
	Dot dot = Dot(Point(190, 150));
	dot.setColorChannels(0xFF);
	Configuration config;
	// TODO: Get rid of MegaBase, bad band-aid fix
	// TODO: Have some DrawGroup pointers for collision, node, and other groups/structures needed
	MegaBase::setOffset(&screenPosition);
	MegaBase::setRenderer(gRenderer);
	CollideBaseGroup boxes;
	NodeDrawGroup nodes;
	nodes.setCollision(boxes);
	AlertTextHandler handler;
	// TODO: Create a file structure for containing level data so its not hardcoded 
	EnemyDrawGroup bads;
	bads.setDot(&dot);
	bads.setCollision(boxes);
	bads.setNavigation(nodes);
	BackgroundGroup groundGroup;
	// Box creation
	Box::createBoxTexture(gRenderer);
	Point ar[] = {Point(200, 200), Point(400, 200), Point(300, 200), Point(500, 200), Point(500, 300), Point (500, 400), 
				  Point(500, 500), Point(600, 600), Point(600, 500)};
	for (Point point: ar) {
		boxes.push_back(CollideBaseFactory::CreateBox(point));
	}
	bads.add(new BadTest(Point(300, 400))); // Raw 'new', kill it
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 25) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 25) {
			nodes.addNodeAt(Point(x, y));
			if (x % 100 == 0 && y % 100 == 0) {
				groundGroup.add(Point(x, y), Ground::GRASS); // Consider having Nodes placed based on ground tiles?
			}
		}
	}
	Font gFont;
	std::string foo = "praise david oshry";
	AppearingText ap(foo, &gFont, Point(250, 0), 15, COLORS::RED, 300);
	PointDelta popo = PointDelta(0, 0, 4);
	Controller contra;
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(popo); // Maybe allow for multiple bindings of the same command somehow? vectors likely? Also remove this dumb fix
	FpsText fps(gFont, Point(100, 10), COLORS::RED); // TODO: Add handler for these things, also have this singular timer passed to all "groups" for consistency
	handler.addMessage(AlertText("this shouldn't last long", Point(300, 150), COLORS::RED, 20, 2500));
	// TODO: Standardize between draw and render, ie pick one you indecisive fuck
	while(!contra.quit) {
		clearScreen(gRenderer);
		popo.zero(); // >:(
		contra.handleEvents();
		dot.collideTest(popo * fps.getRatio(), boxes); // Player collision detection
		bads.update();
		/* Drawing */
		groundGroup.drawGroup();
		boxes.drawGroup();
		bads.drawGroup();
		ap.update(gRenderer);
		handler.drawHandler();
		dot.draw(); // Player must always be drawn onto the top layer for best visibility, for the time being
		if (contra.checkListener(config["Ray"]).getHeld()) { // Raycasting
			dot.rayCast(boxes); // Dot should already have access to this; make it so
		}
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
