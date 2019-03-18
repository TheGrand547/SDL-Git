#pragma once
#include<SDL2/SDL.h>
#include "Rect.h"
class Dot: public MyBase {
private:
	Point position;
	Rect myRect;
public:
	Dot(Point startingCoordinate) {
		position = startingCoordinate;
		myRect = Rect(startingCoordinate, startingCoordinate + Point(10,10));
	}
	
	void operator-=(Point delta) {
        myRect += delta;
    }
    
	void operator+=(Point delta) {
        myRect += delta;
	}
	
	Point getPos() {
		return myRect.getTopLeft();
	}
	
	Rect getRect() {
		return myRect;
	}
	
	void draw(SDL_Renderer* renderer) {
		SDL_SetRenderDrawColor(renderer, rChannel, gChannel, 
								bChannel, aChannel);
		SDL_Rect temp = myRect.getSDLRect();
		SDL_RenderFillRect(renderer, &temp);
	}
};
