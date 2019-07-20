#include "source/headers.h"
bool init(); //TODO fucking kill this
SDL_Renderer* createRenderer(SDL_Window* window);
SDL_Window* createWindow();
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

SDL_Renderer* MegaBase::renderer = NULL;
BoundedPoint* MegaBase::offset = NULL;

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
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	Configuration config;
	// TODO: Get rid of MegaBase, as it's a temporary fix
	MegaBase::setOffset(&screenPosition);
	MegaBase::setRenderer(gRenderer);
	CollideBaseGroup boxes;
	NodeDrawGroup nodes;
	AlertTextHandler handler;
	// TODO: Create a file structure for containing level data so its not hardcoded 
	EnemyDrawGroup bads;
	bads.setDot(&dot);
	bads.setCollision(&boxes);
	bads.setNavigation(&nodes);
	BackgroundGroup groundGroup;
	// Initializes the pointer to the single texture shared by all Box objects, then creates the boxes and assigns the pointer to them
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer); // TODO: KILL THIS WITH FIRE
	Point ar[] = {Point(50, 50), Point(200, 200), Point(400, 200), Point(200, 500), Point(500, 400), Point(700, 600), Point(800, 200)};
	for (Point point: ar) {
		boxes.push_back(CollideBaseFactory::CreateBox(point, mTexture));
	}
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			if (Node::checkLocationValidity(Point(x, y), &boxes)) {
				nodes.add(new Node(Point(x, y), &nodes, &boxes));
			}
			groundGroup.add(Point(x, y), Ground::GRASS); // Consider having Nodes placed based on ground tiles?
			if (x == y) {
				bads.add(new BadTest(Point(x, y)));
			}
		}
	}
	Font gFont;
	std::string foo = "ptr is a tard but not really omegalul get rekt scrub";
	AppearingText ap(foo, &gFont, Point(250, 0), 15, COLORS::RED, 300);
	PointDelta popo = PointDelta(0, 0, 4);
	Controller contra;
	contra.addButton("Exit", new SimpleButtonCommand<bool>([](bool* b) {*b = true;}, &contra.quit));
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(&popo);
	FpsText fps(&gFont, Point(100, 10), COLORS::RED); // Add handler for these things
	handler.addMessage(AlertText("this shouldn't last long", Point(300, 150), COLORS::RED, 20, 2500));
	// TODO: Standardize between draw and render, ie pick one you indecisive fuck
	while(!contra.quit) {
		clearScreen(gRenderer);
		popo.zero(); // >:(
		contra.handleEvents();
		dot.collideTest(popo * fps.getRatio(), &boxes); // Player collision detection
		bads.update();
		/* Drawing */
		groundGroup.drawGroup();
		boxes.drawGroup();
		bads.drawGroup();
		ap.update(gRenderer);
		handler.draw();
		dot.draw(); // Player must always be drawn onto the top layer for best visibility, for the time being
		if (contra.checkListener(config["Ray"]).getHeld()) { // Raycasting
			dot.rayCast(&boxes); 
		}
		fps.draw(gRenderer);
		renderChanges(gRenderer, gameWindow);
	}
	close(gameWindow);
	delete mTexture;
	return 0;
}

bool init() {
	bool success = true; //Initialization flag
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
