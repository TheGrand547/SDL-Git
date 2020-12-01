#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../essential/Configuration.h"
#include "HeldKey.h"
#include <map>
#include <memory>
#include <vector>
#include <SDL.h>
#include <sstream>
#include <string>

class GameInstance;

typedef void (*GameCommand)(GameInstance*);

// Class to handle event handling(haha) less messily and with easier functionality to implement new events 
class Controller {
	/* There are three types of events the Controller will handle; Keys, Buttons, and Listeners 
	 * Keys are for commands that have distinct states of down and up
	 * Buttons are for actions that only activate when they key is held down, but don't care when released
	 * Listeners are an extention of HeldKey for more complicated external usage */
	protected:
		// Low Priority TODO: Add controller support

		Configuration config;
		const Uint8* keyboard;
		std::map<int, GameCommand> buttons;
		std::map<int, std::pair<GameCommand, GameCommand>> keys;
		std::map<int, HeldKey> listeners;
		std::map<std::string, GameCommand> cheatMap;
		std::stringstream cheatStream;
	public:
		bool quit;
		GameInstance* parent;
		int mouseX, mouseY;
		Controller();
		~Controller();
		HeldKey& checkListener(int key);
		void handleEvents();
		void addButton(int value, GameCommand func);
		void addButton(const std::string& str, GameCommand func);
		void addKey(int value, GameCommand down, GameCommand up);
		void addKey(const std::string& str, GameCommand down, GameCommand up);
		void addListener(int key, int threshold = 150);
		void addListener(const std::string& key, int threshold = 150);
		void updateListeners();
		void addPlayerKeys();
		void addCheat(const std::string& key, GameCommand func);
};
#endif
