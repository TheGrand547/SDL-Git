#pragma once
#ifndef PLAYER_MOVE_COMMAND_H
#define PLAYER_MOVE_COMMAND_H
#include "ButtonCommand.h"
#include "../../primitives/PointDelta.h"
class PlayerMoveCommand : public ButtonCommand {
	private:
		PointDelta* target;
		void (*command)(PointDelta*);
	public:
		PlayerMoveCommand(void(*command)(PointDelta*), PointDelta* target);
		~PlayerMoveCommand();
		PlayerMoveCommand& operator=(const PlayerMoveCommand other);
		void execute() override;
		int DEFAULT() override;
};
#endif
