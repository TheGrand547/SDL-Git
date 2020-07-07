#pragma once
#ifndef PLAYER_MOVE_COMMAND_H
#define PLAYER_MOVE_COMMAND_H
#include "ButtonCommand.h"
#include "../../primitives/Point.h"

class PlayerMoveCommand : public ButtonCommand {
	private:
		Point* target;
		void (*command)(Point*);
	public:
		PlayerMoveCommand(void(*command)(Point*), Point* target);
		~PlayerMoveCommand();
		PlayerMoveCommand& operator=(const PlayerMoveCommand other);
		void execute() override;
		int DEFAULT() override;
};
#endif
