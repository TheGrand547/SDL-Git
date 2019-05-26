/* TODO: Write a header file to include all these headers */
#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2_image/SDL_image.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2/SDL_thread.h>
#include<stdio.h>
#include<sstream>
#include<vector>
#include "source/game_entities/Box.h"
#include "source/game_entities/BackgroundElement.h"
#include "source/primitives/Line.h"
#include "source/primitives/Point.h"
#include "source/wrappers/Font.h"
#include "source/primitives/Rect.h"
#include "source/wrappers/Timer.h"
#include "source/wrappers/Texture.h"
#include "source/essential/util.h"
#include "source/essential/random.h"
#include "source/MyBase.h"
#include "source/Dot.h"
#include "source/PointDelta.h"
#include "source/BoundedPoint.h"
#include "source/HeldKey.h"
#include "source/game_entities/base/CollideBase.h"
#include "source/BoundedRect.h"
#include "source/essential/Configuration.h"
#include "source/game_entities/BadTest.h"
#include "source/wrappers/control/Controller.h"
#include "source/AppearingText.h"
#include "source/wrappers/FpsText.h"

/* Handles initializing and de-initializing nicely */
bool init();
void close();
void clearScreen(SDL_Renderer* renderer);

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main(int argc, char *argv[]) {
	int mousePosX, mousePosY;
	Line tempLine;
	tempLine.setColorChannels(0x00, 0xFF, 0xFF);
	Point newPoint;
	
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	Configuration config;
	
	std::vector<Box*>* boxes = new std::vector<Box*>;
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
	boxes->push_back(new Box(Point(50, 50)));
	boxes->push_back(new Box(Point(200, 200)));
	boxes->push_back(new Box(Point(350, 200)));
	Box::setTexture(boxes, mTexture);
	
	Texture* groundTexture = BackElement::createGroundTexture(gRenderer, Ground::GRASS);
	
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			ground->push_back(new BackElement(Point(x, y)));
		}
	}
	BackElement::setGroundTextures(ground, groundTexture);
	
	BadTest small(Point(300, 350), boxes);
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
		popo->zero(); // THERE MUST BE A BETTER WAY
		/* Clear the rendering screen */
		clearScreen(gRenderer);
		/* Event Handling */
		contra.handleEvents();
		SDL_GetMouseState(&mousePosX, &mousePosY);
		
		/* Collision Detection: Only does detection if the Player Movement Vector exists to improve performance */
		if (popo->getNonZero()) {
			/* TODO: Make this not look like shit */
			px = (*popo) * text.getRatio();
			float xDelta = 0;
			float yDelta = 0;
			for (int i = 1; i < 6; i++) {
				if (!xDelta) {
					if (collideRectTest(dot.getRect() + px.onlyX() / i, boxes)) {
						xDelta = px.x() / i;
						screenPos += px.onlyX() / i;
					}
				}
				if (!yDelta) {
					if (collideRectTest(dot.getRect() + px.onlyY() / i, boxes)) {
						yDelta = px.y() / i;
						screenPos += px.onlyY() / i;					
					}
				}
				if (xDelta && yDelta) {
					break;
				}
			}
			dot += PointDelta(xDelta, yDelta, px.getMagnitude());
			Point dotTest = dot.getPos().copy();
			/* TODO: Make this not look like shit */
			if (dotTest.x() < Screen::SCREEN_WIDTH / 2) {
				screenPos.xZero();
			}
			if (dotTest.y() < Screen::SCREEN_HEIGHT / 2) {
				screenPos.yZero();
			}
			if (dotTest.y() > (Screen::MAX_HEIGHT - (Screen::SCREEN_HEIGHT / 2))) {
				screenPos.maxY();
			}
			if (dotTest.x() > (Screen::MAX_WIDTH - (Screen::SCREEN_WIDTH / 2))) {
				screenPos.maxX();
			}
		} 
		/* End of Collision Detection */


		/* Drawing things onto the screen */
		for (BackElement* back: *ground) {
			back->draw(gRenderer, screenPos);
		}
		for (Box* box: *boxes) {
			box->draw(gRenderer, screenPos);
		}
		small.render(gRenderer, screenPos);
		ap.update(gRenderer);
		dot.draw(gRenderer, screenPos.negate()); // Player must always be drawn onto the top layer for best visibility
		/* End of Drawing */
		
		/* Raycasting */
		if (contra.checkListener(config["Ray"]).getHeld()) {
			newPoint = collideTestVectorToRay(boxes, dot.getRay());
			if (!newPoint.isNull()) {
				tempLine = Line(dot.getCenter(), newPoint.copy());
				tempLine.drawLine(gRenderer, screenPos);
			}
			
		}
		/* End of Raycasting */
		
		text.draw(gRenderer); // Draw FPS on screen
		/* Render all changes onto the window */
		SDL_RenderPresent(gRenderer);
		SDL_UpdateWindowSurface(gWindow);
	}
	close();
	delete popo;
	delete groundTexture;
	delete mTexture;
	delete ground;
	delete boxes;
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
