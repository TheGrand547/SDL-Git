#pragma once
#ifndef TEXT_HANDLER_H
#define TEXT_HANDLER_H
#include "essential/log.h"
#include "wrappers/Font.h"
#include <memory>
#include <vector>

class GameInstance;
class Text;

typedef std::shared_ptr<Text> TextPtr;
typedef std::vector<TextPtr> TextVector;

class TextHandler {
	protected:
		Font generic;
		TextVector stored;
	public:
		GameInstance* parent;
		TextHandler();
		~TextHandler();
		void draw();
		void setDefault();

		template<typename T, typename... Args> std::shared_ptr<T> createText(Args&&... args);
};

template<typename T, typename... Args> std::shared_ptr<T> TextHandler::createText(Args&&... args) {
	static_assert(std::is_base_of<Text, T>::value, "createText must be templated with a class that derives from Text.");
	std::shared_ptr<T> text = std::make_shared<T>(std::forward<Args>(args)...);
	if (text) {
		this->stored.push_back(text);
		text->setFont(this->generic);
	} else {
		LOG("Failed to create 'Text'");
	}
	return text;
}
#endif
