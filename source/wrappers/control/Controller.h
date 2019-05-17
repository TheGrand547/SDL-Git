#pragma once
#ifndef FUCK_THIS_SO_MUCH
#define FUCK_THIS_SO_MUCH
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../../essential/Configuration.h"
//#include "../../primatives/Point.h"
#include "../../PointDelta.h"
//#include "../../essential/util.h"
#include "ControllerCommand.h" // TODO: Create folder/sub-folder for "controller" related
//#include<map>


/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	private:
		std::map<int, ControllerCommand<PointDelta, Point>*> keydown;
		std::map<int, ControllerCommand<PointDelta, void(*)(PointDelta*)>*> keyup;
		Configuration config;
		PointDelta* target;
	public:
		Controller(Configuration config, PointDelta* target);
		~Controller();
		void handleEvents(SDL_Event e);
		void addKey(std::string key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*));
		void addKey(int key, void(*keyDownCommand)(PointDelta*, Point), Point keyDownArgument, void(*keyUpCommand)(PointDelta*, void(*)(PointDelta*)), void(*keyUpArgument)(PointDelta*));

		
		static void ADD(PointDelta* p, Point g) {(*p) += g;}
		static void SUBTRACT(PointDelta* p, Point g) {(*p) -= g;}
		static void X_ZERO(PointDelta* p) {p->xZero();}
		static void Y_ZERO(PointDelta* p) {p->yZero();}
		static void GREATER_ZERO(PointDelta* p, void(*g)(PointDelta*)) {if(*p > 0) g(p);}
		static void LESSER_ZERO(PointDelta* p, void(*g)(PointDelta*)) {if(*p < 0) g(p);}
};
#endif
