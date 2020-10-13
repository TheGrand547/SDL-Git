#pragma once
#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H
#include "wrappers/AlertText.h"
#include "wrappers/Text.h"
#include <memory>
#include <vector>

typedef std::shared_ptr<Text> TextPtr;
typedef std::vector<TextPtr> TextVector;

class GameInstance;

// TODO: Make this compatible with all kinds of text
class TextHandler {
	private:
		TextVector stored;
	public:
		GameInstance* parent;
		TextHandler();
		~TextHandler();
		void draw();

		template<typename T, typename... Args> std::shared_ptr<T> createText(Args... args) {
			static_assert(std::is_base_of<Text, T>::value, "createText must be templated with a class that derives from Text.");
			std::shared_ptr<T> text = std::make_shared<T>(args...);
			this->stored.push_back(text);
			return text;
		}
		
};
#endif
