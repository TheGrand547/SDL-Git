#include "source/headers.h"
bool init(SDL_Renderer*& renderer, SDL_Window*& window); // TODO: Write methods for initializing individual renderers, windows, ect
void close(SDL_Window* window);
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

SDL_Renderer* DrawGroup::renderer = NULL;

int main(int argc, char *argv[]) {
	SDL_Window* gWindow = NULL; // TODO: Rename these to something not dumb and arbitrary
	SDL_Renderer* gRenderer = NULL;
	if(!init(gRenderer, gWindow)) {
		printf("Failed to initialize!\n");
		return 0;
	}
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	Configuration config;
	DrawGroup::SET_RENDERER(gRenderer);
	CollideBaseGroup boxes;
	/* TODO: Add method for initializing everything on screen to clean up main() and help smooth the transition to using 'Screen' as the base class for the project */
	 
	/* TODO: Create a file structure for containing level data so its not hardcoded */
	/* Initializes the pointer to the single texture shared by all Box objects, then creates the boxes and assigns the pointer to them */
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer); 
	// TODO: Add CollideBaseFactory -> remove all references to pointers in main if possible
	boxes.push_back(new Box(Point(50, 50)));
	boxes.push_back(new Box(Point(200, 200)));
	boxes.push_back(new Box(Point(350, 200)));
	boxes.push_back(new Box(Point(500, 200)));
	boxes.setTexture(mTexture);
	
	BackgroundGroup groundGroup;
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			groundGroup.add(Point(x, y), Ground::GRASS);
		}
	}
	BadTest small(Point(300, 350), &boxes);
	small.set(gRenderer);
	
	Font gFont = Font();
	BoundedPoint screenPos = BoundedPoint(Screen::MAX_SCREEN_X_POS, Screen::MAX_SCREEN_Y_POS);
	
	PointDelta px;
	std::string foo = "mani is pretty smart sometimes, but kotlin is a dumb language cause it has no semi-colons iirc";
	AppearingText ap(foo, 10, 0, 20, "resources/Font.ttf", COLORS::RED, Point(0, 0), 300);
	
	PointDelta popo = PointDelta(0, 0, 4);
	Controller contra(config);
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(&popo);
	FpsText fps(&gFont, Point(100, 10), COLORS::RED);
	while(!contra.quit) {
		clearScreen(gRenderer);
		popo.zero(); // >:(
		contra.handleEvents();
		dot.collideTest(popo * fps.getRatio(), &boxes, screenPos); // Player collision detection
		/* Drawing */
		groundGroup.drawGroup(screenPos);
		boxes.drawGroup(screenPos);
		small.render(gRenderer, screenPos);
		ap.update(gRenderer); // TODO: Seperate the upating and the drawing of entities
		dot.draw(gRenderer, screenPos.negate()); // Player must always be drawn onto the top layer for best visibility
		/* Raycasting */
		if (contra.checkListener(config["Ray"]).getHeld()) { // TODO: put this elsewhere
			Point newPoint = collideTestVectorToRay(&boxes, dot.getRay());
			if (!newPoint.isNull()) {
				Line tempLine = Line(dot.getCenter(), newPoint.copy());
				tempLine.setColorChannels(COLORS::CYAN);
				tempLine.drawLine(gRenderer, screenPos);
			}
		}
		fps.draw(gRenderer);
		renderChanges(gRenderer, gWindow); // Render all changes onto the window
	}
	close(gWindow);
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
		//Create window
		gWindow = SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			TTF_Init(); //Initialize true-type font
			renderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED); //Create rendererer
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
