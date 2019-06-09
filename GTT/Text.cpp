#include "Text.h"
#include "Game.h"


Text::Text(Font* font, string text, SDL_Color color) :
			Sprite(new Texture(Game::getInstance()->getRenderer(), text, *font, color)) {
	font_ = font;
	text_ = text;
	color_ = color;
}

Text::~Text() {

}

const string Text::getText() {
	return text_;
}

const Font * Text::getFont() {
	return font_;
}

const SDL_Color Text::getColor() {
	return color_;
}

void Text::setText(string text) {
	text_ = text;
	reload();
}

void Text::setFont(Font * font) {
	font_ = font;
	reload();
}

void Text::setColor(SDL_Color color) {
	color_ = color;
	reload();
}

bool Text::reload() {
	return texture_->loadFromText(Game::getInstance()->getRenderer(), text_, *font_, color_);

}
