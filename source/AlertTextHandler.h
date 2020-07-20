#pragma once
#ifndef ALERT_TEXT_HANDLER_H
#define ALERT_TEXT_HANDLER_H
#include "wrappers/AlertText.h"
#include<vector>

class GameInstance;

// TODO: Make this compatible with all kinds of text
class AlertTextHandler {
	private:
		std::vector<AlertText> alerts;
	public:
		GameInstance* parent;
		AlertTextHandler();
		~AlertTextHandler();
		void addMessage(AlertText message);
		void draw();
};
#endif
