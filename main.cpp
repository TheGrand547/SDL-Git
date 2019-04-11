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
#include "source/primatives/Line.h"
#include "source/primatives/Point.h"
#include "source/wrappers/Font.h"
#include "source/primatives/Rect.h"
#include "source/wrappers/Timer.h"
#include "source/wrappers/Texture.h"
#include "source/util.h"
#include "source/MyBase.h"
#include "source/Dot.h"
#include "source/Box.h"
#include "source/PointDelta.h"
#include "source/BoundedPoint.h"
#include "source/HeldKey.h"
#include "source/CollideBase.h"
#include "source/BoundedRect.h"
#include "source/BackgroundElement.h"
#define PI 3.14159265


/* Temporary globals before the eventually switch to game instances being tracked in seperate Objects. */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/* TODO: Remove & rework copy-pasted starting code */
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
	
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

SDL_Renderer* gRenderer = NULL;

bool init() {
	//Initialization flag
	bool success = true;
	
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	} else {
		//Create window
		gWindow = SDL_CreateWindow("SDL Experimenting", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		} else {
			TTF_Init();
			//Get window surface
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return success;
}

bool loadMedia() {
	return true;
}

void setTexture(std::vector<Box*>* vec, SuperTexture* texture) {
	for (Box* box: *vec) {
		box->setTexture(texture);
	}
}

void close() {
	//Deallocate surface
	SDL_FreeSurface(gXOut);
	gXOut = NULL;

	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
int main(int argc, char *argv[]) {
	int mousePosX, mousePosY;
	Line tempLine;
	tempLine.setColorChannels(0x00, 0xFF, 0xFF);
	Point newPoint;
	
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	//std::vector<std::vector<Box*>*>* holy = new std::vector<std::vector<Box*>*>;
	
	std::vector<Box*>* boxes = new std::vector<Box*>;
	
	if(!init()) {
		printf( "Failed to initialize!\n" );
	} else {
		//Load media
		if(!loadMedia()) {
			printf("Failed to load media!\n");
		} else {			
			//Main loop flag
			bool quit = false;
			
			SDL_Rect IOP = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
			SDL_Color red = {255, 0, 0, 255};
			
			/* TODO: Add method for initializing everything on sccreen to clean up main() */
			
			/* Initializes the pointer to the single texture shared by all
			 * Box objects, then creates the boxes and assigns the pointer to them */
			SuperTexture* mTexture = Box::createBoxTexture(gRenderer);
			boxes->push_back(new Box(Point(50, 50)));
			boxes->push_back(new Box(Point(200, 200)));
			boxes->push_back(new Box(Point(350, 200)));
			setTexture(boxes, mTexture);
			
			BackElement test = BackElement(Point(300, 50));
			test.loadTexture(gRenderer);
			
			//String for rendering text to the screen
			std::stringstream fpsStr;
			
			//Event handler
			SDL_Event e;
			
			//Timer Stuff
			Timer time;
			int countedFrames = 0;
			
			PointDelta dx = PointDelta(0, 0, 4, 4);
			
			Font gFont = Font();
			
			BoundedPoint screenPos = BoundedPoint(0, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			
			
			HeldKey shift(SDLK_LSHIFT, 30);
			time.start();
			
			while(!quit) {
				//Clear screen
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
                
                /* Framerate related Calculations */
                if (countedFrames > 1000) {
					time.start();
					countedFrames = 1;
				}
                float avgFPS = countedFrames / (time.getTicks() / 1000.f);
                fpsStr.str("");
                fpsStr << "FPS: " << avgFPS;
				gFont.renderText(100, 0, fpsStr.str(), gRenderer, red);
				/* End of framerate related Calculations */
				
				/* Collision Detection 
				 * Only does detection if dx 
				 * Exists to improve performance */
                if (dx.getNonZero()) {
					for (int i = 1; i < 6; i++) {
						if (collideRectPlusExtras(dot.getRect(), boxes, dx/i, screenPos)) {
							dot += dx/i;
							screenPos += dx/i;
							break;
						}
					}
				}
				/* End of Collision Detection */
				
				/* Raycasting */
				if (shift.getHeld()) {
					Line ray(dot.getRay());
					newPoint = collideTestVectorToRay(boxes, ray, screenPos.negate());
					if (!newPoint.isNull()) {
						tempLine = Line(dot.getCenter(), newPoint.copy());
						tempLine.drawLine(gRenderer);
					}
				}
				/* End of Raycasting */
				
				
				/* Drawing things onto the screen */
				test.draw(gRenderer, screenPos);
				
				for (Box* box: *boxes) {
					box->draw(gRenderer, screenPos);
				}
				dot.draw(gRenderer);
				/* End of Drawing */
			
				
				/* Render all changes onto the window */
				SDL_RenderPresent(gRenderer);
				SDL_UpdateWindowSurface(gWindow);
				
				//Necessary to keep up approximate framerate estimation
				countedFrames++; 
			}
		}
	}
	close();
	delete boxes;
	return 0;
}
