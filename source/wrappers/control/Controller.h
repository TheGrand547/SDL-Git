#pragma once
#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../../essential/Configuration.h"
#include "../../primitives/Point.h"
#include "../HeldKey.h"
#include "ButtonCommand.h"
#include "CommandBase.h"
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
	private:
		// Low Priority TODO: Add controller support

		// TODO: You're next on the chopping blocks
		std::map<int, std::shared_ptr<CommandBase>> keys;
		std::map<int, HeldKey> listeners;

		std::stringstream cheatStream;
		std::map<int, GameCommand> buttons;
		std::map<std::string, GameCommand> cheatMap;

		Configuration config;
		const Uint8* keyboard;
	public:
		GameInstance* parent; // TODO: Elegance please
		int mouseX, mouseY;
		bool quit = false;
		Controller();
		~Controller();
		void handleEvents();
		void addButton(int value, GameCommand func);
		void addButton(std::string str, GameCommand func);
		void addKey(int value, std::shared_ptr<CommandBase> command);
		void addListener(int key, int threshold = 150);
		void addListener(std::string key, int threshold = 150);
		void updateListeners();
		HeldKey& checkListener(int key);
		void addPlayerKeys();
		void addCheat(std::string key, GameCommand func); // TODO: Make this not dependent on function pointers
};
#endif
