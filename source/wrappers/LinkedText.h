#pragma once
#ifndef LINKED_TEXT_H
#define LINKED_TEXT_H
#include "../essential/constants.h"
#include "Text.h"
#include <sstream>
#include <string>

template<class T> class LinkedText : public Text {
	protected:
		Point position;
		std::string message;
		const T& reference;
	public:
		LinkedText(Point position, const T& reference, const std::string& text = "");
		~LinkedText();
		bool finished() const override;
		void draw(Renderer renderer) override;
};

template<class T> LinkedText<T>::LinkedText(Point position, const T& reference, const std::string& text) : position(position), 
										message(text), reference(reference) {}

template<class T> LinkedText<T>::~LinkedText() {}

template<class T> bool LinkedText<T>::finished() const {
	return false;
}

template<class T> void LinkedText<T>::draw(Renderer renderer) {
	std::stringstream stream;
	stream << this->message << this->reference;
	this->font.drawText(this->position, stream.str(), renderer.renderer, Colors::Red);
}
#endif
