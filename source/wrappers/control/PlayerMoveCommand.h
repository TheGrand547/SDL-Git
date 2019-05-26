#pragma once
#ifndef PLAYER_MOVE_COMMAND_H
#define PLAYER_MOVE_COMMAND_H
#include "ButtonCommand.h"
#include "../../PointDelta.h"
class PlayerMoveCommand : public ButtonCommand {
	private:
		PointDelta* target;
		void (*command)(PointDelta*);
	public:
		PlayerMoveCommand(void(*command)(PointDelta*), PointDelta* target);
		~PlayerMoveCommand();
		void execute();
};
#endif
