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
#include "source/primatives/Line.h"
#include "source/primatives/Point.h"
#include "source/wrappers/Font.h"
#include "source/primatives/Rect.h"
#include "source/wrappers/Timer.h"
#include "source/wrappers/Texture.h"
#include "source/essential/util.h"
#include "source/essential/random.h"
#include "source/MyBase.h"
#include "source/Dot.h"
#include "source/PointDelta.h"
#include "source/BoundedPoint.h"
#include "source/HeldKey.h"
#include "source/CollideBase.h"
#include "source/BoundedRect.h"

#define PI 3.14159265


/* Removed TODO on 4/17/19, previously copied code was a necessary evil to ensure proper functionality */
/* Handles initializing and de-initializing nicely */
bool init();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int main(int argc, char *argv[]) {
	int mousePosX, mousePosY;
	Line tempLine;
	tempLine.setColorChannels(0x00, 0xFF, 0xFF);
	Point newPoint;
	
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	//std::vector<std::vector<CollideBase*>*>* holy = new std::vector<std::vector<CollideBase*>*>;
	
	std::vector<Box*>* boxes = new std::vector<Box*>;
	std::vector<BackElement*>* ground = new std::vector<BackElement*>;
	
	if(!init()) {
		printf( "Failed to initialize!\n" );
		return 0;
	}
	//Main loop flag
	bool quit = false;
	
	/* TODO: Add method for initializing everything on screen to clean up main() and help smooth the transition to
	 * using 'Screen' as the base class for the project */
	
	/* Initializes the pointer to the single texture shared by all
	 * Box objects, then creates the boxes and assigns the pointer to them */
	SuperTexture* mTexture = Box::createBoxTexture(gRenderer);
	boxes->push_back(new Box(Point(50, 50)));
	boxes->push_back(new Box(Point(200, 200)));
	boxes->push_back(new Box(Point(350, 200)));
	Box::setTexture(boxes, mTexture);
	
	Texture* groundTexture = BackElement::createGroundTexture(gRenderer);
	
	for (int x = 0; x <= Screen::MAX_WIDTH; x += 100) {
		for (int y = 0; y <= Screen::MAX_HEIGHT; y += 100) {
			ground->push_back(new BackElement(Point(x, y)));
		}
	}
	for (BackElement* floor: *ground) {
		floor->setTexture(groundTexture);
	}
	
	//String for rendering text to the screen
	std::stringstream fpsStr;
	
	//Event handler
	SDL_Event e;
	
	//Timer Stuff
	Timer time;
	int countedFrames = 0;
	
	
	PointDelta dx = PointDelta(0, 0, 4, 4);
	
	Font gFont = Font();
	
	BoundedPoint screenPos = BoundedPoint(Screen::MAX_WIDTH - Screen::SCREEN_WIDTH, Screen::MAX_HEIGHT - Screen::SCREEN_HEIGHT);
	
	HeldKey shift(SDLK_LSHIFT, 30);
	time.start();
	float avgFPS = 100;
	while(!quit) {
		dx.setBounds(4, 4);
		/* Clear the rendering screen */
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(gRenderer);
		
		/* Event Handling */
		while(SDL_PollEvent(&e) != 0) {
			/* TODO: Make this a method to clean up main method */
			switch(e.type) {
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					if (e.key.repeat == 0) {
						switch (e.key.keysym.sym) {
							case SDLK_UP: 
								dx -= Point(0, 10);
								break;
							case SDLK_DOWN:
								dx += Point(0, 10);
								break;
							case SDLK_LEFT:
								dx -= Point(10, 0);
								break;
							case SDLK_RIGHT:
								dx += Point(10, 0);
								break;
							case SDLK_LSHIFT:
								
								break;
						}
					}
					if (e.key.keysym.sym == SDLK_LSHIFT) {
						shift.set(true);
					}
					break;
				case SDL_KEYUP:
					if (e.key.repeat == 0) {
						switch (e.key.keysym.sym) {
							case SDLK_UP: 
								if (dx.y() < 0) 
									dx.yZero();
								break;
							case SDLK_DOWN:
								if (dx.y() > 0) 
									dx.yZero();
								break;
							case SDLK_LEFT:
								if (dx.x() < 0) 
									dx.xZero();
								break;
							case SDLK_RIGHT:
								if (dx.x() > 0) 
									dx.xZero();
								break;
						}
					}
					if (e.key.keysym.sym == SDLK_LSHIFT) {
						shift.set(false);
					}
					break;
			}
		}
		shift.tick();
		SDL_GetMouseState(&mousePosX, &mousePosY);
		//gFont.renderTextWrapped(200, 100, "andrew did a good :D but sam did the red bar and lets be real thats more important lul", gRenderer, red, 250);
		
		/* Collision Detection 
		 * Only does detection if dx exists to improve performance */
		if (dx.getNonZero()) {
			/* Added to attempt to  */
			dx * (Screen::INTENDED_FRAME_RATE / avgFPS);
			for (int i = 1; i < 6; i++) {
				if (collideRectPlusExtras(dot.getRect(), boxes, dx/i, screenPos)) {
					dot += dx/i;
					screenPos += dx/i;
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
					
					break;
				}
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
		
		dot.draw(gRenderer, screenPos.negate()); // Player must always be drawn onto the upper most layer for best visibility
		
		/* End of Drawing */
		
		
		/* Raycasting */
		if (shift.getHeld()) {
			Line ray = dot.getRay();
			newPoint = collideTestVectorToRay(boxes, ray);
			if (!newPoint.isNull()) {
				tempLine = Line(dot.getCenter(), newPoint.copy());
				tempLine.drawLine(gRenderer, screenPos);
			}
		}
		/* End of Raycasting */
		
		
		 /* Framerate related Calculations */
		if (countedFrames > 1000) {
			time.start();
			countedFrames = 1;
		}
		avgFPS = countedFrames / (time.getTicks() / 1000.f);
		fpsStr.str("");
		fpsStr << "FPS: " << avgFPS;
		gFont.renderText(100, 0, fpsStr.str(), gRenderer, COLORS::RED);
		/* End of framerate related Calculations */
	
	
		/* Render all changes onto the window */
		SDL_RenderPresent(gRenderer);
		SDL_UpdateWindowSurface(gWindow);
		
		//Necessary to keep up approximate framerate estimation
		countedFrames++; 
	}
	close();
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
		gWindow = SDL_CreateWindow(Screen::WINDOW_TITLE, Screen::DEFAULT_POS, Screen::DEFAULT_POS, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
