#pragma once
#ifndef TEXT_H
#define TEXT_H
#include "Font.h"

// Base class for all text related things so there can be a text container
class Text {
	protected:
		// Add the attribute stuff
		struct Attribute {
			
		};
		Font font;
	public:
		Text();
		// TODO: See if std::forward can work its magic
		Text(const Font& font);
		Text(Font&& font);
		virtual ~Text();
		virtual bool finished() const = 0;
		virtual void draw(Renderer renderer) = 0;
		template<typename T> void setFont(T font) {
			this->font = std::forward<Font>(font);
		}
};
#endif
