#include "source/headers.h"
bool init(SDL_Renderer*& renderer, SDL_Window*& window);
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

/* TODO: Add a super simple "base" class to handle this shit for me */
SDL_Renderer* MegaBase::renderer = NULL;
BoundedPoint* MegaBase::offset = NULL;

int main(int argc, char *argv[]) {
	/* TODO: Add Method/Class for initializing everything on screen to clean up main() and help smooth the transition to using 'Screen' as the base class for the project */
	SDL_Window* gameWindow = NULL;
	SDL_Renderer* gRenderer = NULL;
	if(!init(gRenderer, gameWindow)) {
		printf("Failed to initialize!\n");
		return 0;
	}
	
	BoundedPoint screenPosition = BoundedPoint(Screen::MAX_SCREEN_X_POS, Screen::MAX_SCREEN_Y_POS);
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	dot.setRenderingValues(gRenderer, &screenPosition);
	Configuration config;
	
	MegaBase::setOffset(&screenPosition);
	MegaBase::setRenderer(gRenderer);

	CollideBaseGroup boxes;
	/* TODO: Create a file structure for containing level data so its not hardcoded */
	/* Initializes the pointer to the single texture shared by all Box objects, then creates the boxes and assigns the pointer to them */
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer); // TODO: KILL THIS WITH FIRE
	boxes.push_back(CollideBaseFactory::CreateBox(Point(50, 50)));
	boxes.push_back(CollideBaseFactory::CreateBox(Point(200, 200)));
	boxes.push_back(CollideBaseFactory::CreateBox(Point(350, 200)));
	boxes.push_back(CollideBaseFactory::CreateBox(Point(500, 200)));
	boxes.setTexture(mTexture);
	
	BackgroundGroup groundGroup;
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			groundGroup.add(Point(x, y), Ground::GRASS);
		}
	}
	EnemyDrawGroup bads;
	bads.add(new BadTest(Point(300, 350), &boxes));
	
	Font gFont;
	std::string foo = "mani is pretty smart sometimes, but kotlin is a dumb language cause it has no semi-colons iirc";
	AppearingText ap(foo, &gFont, Point(0, 0), 15, COLORS::RED, 300);
	
	PointDelta popo = PointDelta(0, 0, 4);
	Controller contra;
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(&popo);
	FpsText fps(&gFont, Point(100, 10), COLORS::RED);
	boxes.setOffset(&screenPosition);
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


bool init(SDL_Renderer*& renderer, SDL_Window*& gWindow) {
	bool success = true; //Initialization flag
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		SDL_Init(SDL_INIT_VIDEO);
		gWindow = SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			TTF_Init();
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
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
