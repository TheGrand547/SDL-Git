#include<iostream>
#include<math.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include<SDL2/SDL2_rotozoom.h>
#include<SDL2/SDL2_framerate.h>
#include<SDL2_ttf/SDL_ttf.h>
#include<SDL2_image/SDL_image.h>
#include<stdio.h>
#include<sstream>
#include<vector>
SDL_Renderer* gRenderer = NULL;
#include "util.h"
#include "Line.h"
#include "MyBase.h"
#include "Point.h"
#include "Dot.h"
#include "Rect.h"
#include "Box.h"
#include "Font.h"
#include "Texture.h"
#include "Timer.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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
using namespace std;
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
	Dot dot = Dot(Point(0, 0));
	dot.setColorChannels(0xFF);
	vector<Box> gnar;
	
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
			Box test = Box(Point(50, 50), Point(150,150));
			Box te = Box(Point(200, 200), Point(300,300));	
			gnar.push_back(test);
			gnar.push_back(te);
			gnar.push_back(Box(Point(350, 200), Point(450,300)));
			
			Point dx = Point(0,0);
			
			
			Timer time;
			int countedFrames = 0;
			time.start();
			
			stringstream fpsStr;
			//Event handler
			SDL_Event e;
			//While application is running
			while(!quit) {
				//Handle events on queue
				dx = Point(0, 0);
				while(SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					} else if (e.type == SDL_KEYDOWN) {
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
						}
					}
				}
				SDL_GetMouseState(&mousePosX, &mousePosY);
				//Clear screen
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                //c.drawLine(gRenderer);
                //gFont.renderTextWrapped(0, 0, "Will this work? I really hope so just to annoy my boy coyote, INFINITE AMMO BTW", gRenderer, red, 250);
                float avgFPS = countedFrames / (time.getTicks() / 1000.f);
                fpsStr.str("");
                fpsStr << "FPS: " << avgFPS;
                
                gFont.renderText(100, 0, fpsStr.str(), gRenderer, red);
                
                if (!collideRect(dot.getRect()+dx, gnar)) {
					dot += dx;
				}
				for (int i = 0; i < gnar.size(); i++) {
					gnar[i].draw(gRenderer);
				}
                Line aabc(dot.getPos(), Point(0, dot.getPos().y()));
                //aabc.drawLine(gRenderer);
                newPoint = collideTestVectorToRay(gnar, aabc);
                if (!newPoint.isNull()) {
					newLine = Line(dot.getPos(), newPoint.copy());
					newLine.setColorChannels(0x00, 0x00, 0xFF);
					newLine.drawLine(gRenderer);
				}
                dot.draw(gRenderer);
				lineColor(gRenderer, 200, 200, 400, 300, 0xFF0000FF);
				//Update the surface
				SDL_RenderPresent(gRenderer);
				SDL_UpdateWindowSurface(gWindow);
				++countedFrames;
			}
		}
	}
	close();
	return 0;
}
