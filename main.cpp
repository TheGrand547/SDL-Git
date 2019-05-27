#include "source/headers.h"
/* Handles initializing and de-initializing nicely */
bool init();
void close();
void clearScreen(SDL_Renderer* renderer);
void renderChanges(SDL_Renderer* renderer, SDL_Window* window);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main(int argc, char *argv[]) {
	Line tempLine;
	tempLine.setColorChannels(0x00, 0xFF, 0xFF);
	Point newPoint;
	
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	Configuration config;
	
	//std::vector<Box*>* boxes = new std::vector<Box*>;
	CollideBaseGroup boxes;
	std::vector<BackElement*>* ground = new std::vector<BackElement*>;
	
	if(!init()) {
		printf( "Failed to initialize!\n" );
		return 0;
	}
	/* TODO: Add method for initializing everything on screen to clean up main() and help smooth the transition to
	 * using 'Screen' as the base class for the project */
	 
	/* TODO: Create a file structure for containing level data so its not hardcoded */
	/* Initializes the pointer to the single texture shared by all
	 * Box objects, then creates the boxes and assigns the pointer to them */
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer);
	boxes.push_back(new Box(Point(50, 50)));
	boxes.push_back(new Box(Point(200, 200)));
	boxes.push_back(new Box(Point(350, 200)));
	boxes.push_back(new Box(Point(500, 200))); /* Investigate the off by 2 pixel visual not smiley */
	boxes.setTexture(mTexture);
	
	Texture* groundTexture = BackElement::createGroundTexture(gRenderer, Ground::GRASS);
	
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			ground->push_back(new BackElement(Point(x, y)));
		}
	}
	BackElement::setGroundTextures(ground, groundTexture);
	
	BadTest small(Point(300, 350), boxes.get());
	small.set(gRenderer);
	
	Font gFont = Font();
	BoundedPoint screenPos = BoundedPoint(Screen::MAX_WIDTH - Screen::SCREEN_WIDTH, Screen::MAX_HEIGHT - Screen::SCREEN_HEIGHT);
	
	PointDelta px;
	std::string foo = "mani is pretty smart sometimes, but kotlin is a dumb language cause it has no semi-colons iirc";
	
	AppearingText ap(foo, 5, 0, 20, "resources/Font.ttf", COLORS::RED, Point(0, 0), 300);
	
	PointDelta* popo = new PointDelta(0, 0, 4);
	Controller contra(config);
	contra.addListener("Ray", 120);
	contra.addPlayerKeys(popo);
	
	
	FpsText text(new Font(), Point(100, 10), COLORS::RED);
	while(!contra.quit) {
		/* Clear the rendering screen */
		clearScreen(gRenderer);
		
		/* Event Handling */
		popo->zero(); // THERE MUST BE A BETTER WAY
		contra.handleEvents();
		
		/* Collision Detection */
		if (popo->getNonZero()) {
			dot.collideTest((*popo) * text.getRatio() , boxes.get(), screenPos);
		}
		/* Drawing things onto the screen */
		for (BackElement* back: *ground) {
			back->draw(gRenderer, screenPos);
		}
		boxes.drawGroup(gRenderer, screenPos);
		small.render(gRenderer, screenPos);
		ap.update(gRenderer);
		dot.draw(gRenderer, screenPos.negate()); // Player must always be drawn onto the top layer for best visibility
		/* End of Drawing */
		
		/* Raycasting */
		if (contra.checkListener(config["Ray"]).getHeld()) {
			newPoint = collideTestVectorToRay(boxes.get(), dot.getRay());
			if (!newPoint.isNull()) {
				tempLine = Line(dot.getCenter(), newPoint.copy());
				tempLine.drawLine(gRenderer, screenPos);
			}
			
		}
		/* End of Raycasting */
		
		
		text.draw(gRenderer); // Draw FPS on screen
		/* Render all changes onto the window */
		renderChanges(gRenderer, gWindow);
	}
	close();
	delete popo;
	delete groundTexture;
	delete mTexture;
	delete ground;
	return 0;
}


bool init() {
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow(Screen::WINDOW_TITLE.c_str(), Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			/* Initialize true-type font */
			TTF_Init();
			/* Create renderer */
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		}
	}
	return success;
}

void close() {
	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}

void clearScreen(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
}

void renderChanges(SDL_Renderer* renderer, SDL_Window* window) {
	SDL_RenderPresent(renderer);
	SDL_UpdateWindowSurface(window);
}
