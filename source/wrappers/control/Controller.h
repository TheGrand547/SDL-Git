#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../../essential/Configuration.h"
#include "../../PointDelta.h"
#include "../../HeldKey.h"
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
		std::map<int, CommandBase*> keys;
		std::map<int, HeldKey> listeners;
		Configuration config;
	public:
		Controller(Configuration config);
		~Controller();
		void handleEvents(SDL_Event e);
		void addKey(int value, CommandBase* command);
		void addListener(int key, int threshold = 150);
		void addListener(std::string key, int threshold = 150);
		void tickListeners();
		HeldKey& checkListener(int key);
		void addPlayerKeys(PointDelta* target);
};
#endif
