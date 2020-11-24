#include "Text.h"

Text::Text() {}
Text::Text(const Font& font) : font(font) {}
Text::Text(Font&& font) : font(std::forward<Font>(font)) {}
Text::~Text() {}
