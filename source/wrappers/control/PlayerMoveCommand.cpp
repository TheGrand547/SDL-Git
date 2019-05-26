#include "PlayerMoveCommand.h"

PlayerMoveCommand::PlayerMoveCommand(void(*command)(PointDelta*), PointDelta* target) {
	this->command = command;
	this->target = target;
}

PlayerMoveCommand::~PlayerMoveCommand() {
	delete this->target;
}

void PlayerMoveCommand::execute() {
	this->command(this->target);
}
