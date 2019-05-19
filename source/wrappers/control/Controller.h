#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../../essential/Configuration.h"
#include "../../PointDelta.h"
#include "ControllerCommand.h"
#include "CommandBase.h"
#include<map>
#include<vector>


/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	/* There are two types of events the Controller will handle; Keys and Listeners 
	 * Keys are for "simple" command such as the movement delta of the player changing
	 * Listeners are an extention of HeldKey for more complicated external usage */
	private:
		/** TODO: Add controller support **/
		std::map<int, CommandBase> keys;
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
