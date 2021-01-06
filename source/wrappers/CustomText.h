#ifndef CUSTOM_TEXT_H
#define CUSTOM_TEXT_H
#include "Text.h"
#include "Timer.h"

// TODO: Possibly overhaul text systems at some point
class CustomText : public Text {
	protected:
		Timer time;
	public:
		CustomText(int ms);
		CustomText(int ms, const std::string& font, const int& size);
		~CustomText();
		void draw(Renderer renderer);
		void draw(Renderer renderer, Point position, const std::string& text);
};
#endif
