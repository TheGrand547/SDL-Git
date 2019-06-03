#include "PlayerMoveCommand.h"

PlayerMoveCommand::PlayerMoveCommand(void(*command)(PointDelta*), PointDelta* target) {
	this->command = command;
	this->target = target;
}

PlayerMoveCommand::~PlayerMoveCommand() {
	this->target = NULL;
}

PlayerMoveCommand& PlayerMoveCommand::operator=(const PlayerMoveCommand that) {
	this->target = that.target;
	this->command = that.command;
	return *this;
}

void PlayerMoveCommand::execute() {
	this->command(this->target);
}

int PlayerMoveCommand::DEFAULT() {
	return 0;
}
