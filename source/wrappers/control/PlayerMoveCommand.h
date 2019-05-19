#pragma once
#ifndef PLAYER_MOVE_COMMAND_H
#define PLAYER_MOVE_COMMAND_H
#include "CommandBase.h"
#include "../../primatives/Point.h"
#include "../../PointDelta.h"

class PlayerMoveCommand : public CommandBase {
	public:
		PlayerMoveCommand() {}
		~PlayerMoveCommand() {}
		void execute() {}
};
#endif
