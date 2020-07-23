#pragma once
#ifndef ALERT_TEXT_HANDLER_H
#define ALERT_TEXT_HANDLER_H
#include "wrappers/AlertText.h"
#include "wrappers/Text.h"
#include<memory>
#include<vector>

class GameInstance;

// TODO: Make this compatible with all kinds of text
class AlertTextHandler {
	private:
		std::vector<AlertText> alerts;
		std::vector<std::shared_ptr<Text>> stored;
	public:
		GameInstance* parent;
		AlertTextHandler();
		~AlertTextHandler();
		void addMessage(AlertText message);
		void draw();
		
		template<typename T, typename... Args> std::shared_ptr<T> createText(Args... args) {
			static_assert(std::is_base_of<Text, T>::value, "createText must be templated with a class that derives from Text.");
			std::shared_ptr<T> text = std::make_shared<T>(args...);
			this->stored.push_back(text);
			return text;
		}
		
};
#endif
