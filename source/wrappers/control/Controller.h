#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include<SDL2/SDL.h>
#include<SDL2/SDL2_gfxPrimitives.h>
#include "../../essential/Configuration.h"
#include "../../PointDelta.h"
#include "../../HeldKey.h"
#include "ButtonCommand.h"
#include "ControllerCommand.h"
#include "CommandBase.h"
#include<map>
#include<vector>


/* Class to handle event handling(haha) less messily
 * with easier functionality to implement new events */ 
class Controller {
	/* There are three types of events the Controller will handle; Keys, Buttons, and Listeners 
	 * Keys are for commands that have distinct states of down and up
	 * Buttons are for actions that only activate when they key is held down, but don't care when released
	 * Listeners are an extention of HeldKey for more complicated external usage */
	private:
		/** TODO: Add controller support **/
		/* TODO: Make these not pointers */
		std::map<int, CommandBase*> keys;
		std::map<int, ButtonCommand*> buttons;
		std::map<int, HeldKey> listeners;
		Configuration config;
		const Uint8* stuff = SDL_GetKeyboardState(NULL);
	public:
		bool quit = false;
		Controller(Configuration config);
		~Controller();
		void handleEvents();
		void addButton(int value, ButtonCommand* button);
		void addKey(int value, CommandBase* command);
		void addListener(int key, int threshold = 150);
		void addListener(std::string key, int threshold = 150);
		void tickListeners();
		HeldKey& checkListener(int key);
		void addPlayerKeys(PointDelta* target);
};
#endif
