#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2_image/SDL_image.h>
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

#define PI 3.14159265

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int IDEAL_FPS = 100;
const int TICKS_PER_FRAME = 1000 / (IDEAL_FPS + 10); //Please do not even ask

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
	//Start up SDL and create window
	Point a = Point(0,0);
	Point b = Point(200,200);
	
	Line c = Line(a, b);
	c.setColorChannels();
	
	const char* message = "this is random test message for testing purposes";
	SDL_Color red = {255,0,0,255};
	
	int mousePosX, mousePosY;
	Line newLine;
	Point newPoint;
	Dot dot = Dot(Point(300, 150));
	dot.setColorChannels(0xFF);
	
	std::vector<Box*>* gnar = new std::vector<Box*>;
	
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
			Font gFont = Font();
			
			gnar->push_back(new Box(Point(50, 50)));
			gnar->push_back(new Box(Point(200, 200)));
			gnar->push_back(new Box(Point(350, 200)));
			//gnar->push_back(new Box(Point(700, 500)));
			
			//Timer Stuff
			Timer time;
			int countedFrames = 0;
			
			Timer frameCap;
			int ticks = 0;
			
			std::stringstream fpsStr;
			//Event handler
			SDL_Event e;
			PointDelta dx = PointDelta(0, 0, 4, 4);
			
			
			BoundedPoint screenPos = BoundedPoint(0, 0, 0, 640, 0, 480);
			
			//While application is running
			
			HeldKey shift(SDLK_LSHIFT, 30);
			time.start();
			while(!quit) {
				if (countedFrames > 1000) {
					time.start();
					countedFrames = 1;
				}
				frameCap.start();
				while(SDL_PollEvent(&e) != 0) {
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
				//Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
				//gFont.renderTextWrapped(200, 100, "andrew did a good :D but sam did the red bar and lets be real thats more important lul", gRenderer, red, 250);
                
                float avgFPS = countedFrames / (time.getTicks() / 1000.f);
                fpsStr.str("");
                fpsStr << "FPS: " << avgFPS;
                
                gFont.renderText(100, 0, fpsStr.str(), gRenderer, red);
                if (dx.getNonZero()) {
					if (!collideRect(dot.getRect()+dx, gnar, screenPos.negate())) {
						dot += dx;
						screenPos += dx;
					} /*else if (!collideRect(dot.getRect()+dx/3, gnar)) {
						dot += dx/3;
					} else if (!collideRect(dot.getRect()+dx/4, gnar)) {
						dot += dx/4;
					} else if (!collideRect(dot.getRect()+dx/5, gnar)) {
						dot += dx/5;
					}*/
				} 
				for (int i = 0; i < gnar->size(); i++) {
					(*gnar)[i]->draw(gRenderer, screenPos);
				}
				dot.draw(gRenderer);
				
                //Line aabc(dot.getPos(), dot.getRay().getEnd());
				Line aabc(dot.getRay());
                aabc.drawLine(gRenderer);
                newPoint = collideTestVectorToRay(gnar, aabc);
                if (!newPoint.isNull()) {
					newLine = Line(dot.getCenter(), newPoint.copy());
					newLine.setColorChannels(0x00, 0xFF, 0xFF);
					newLine.drawLine(gRenderer);
				}
				lineColor(gRenderer, 200, 200, 300, 300, 0xFFFF00FF);
				
				//Update the surface
				SDL_RenderPresent(gRenderer);
				SDL_UpdateWindowSurface(gWindow);
				countedFrames++;
			}
		}
	}
	close();
	delete gnar;
	return 0;
}
