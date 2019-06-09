#pragma once
#include "Sprite.h"
class Text : public Sprite
{
public:
	Text(Font* font, string text = "", SDL_Color color = SDL_Color());
	virtual ~Text();

	const string getText();
	const Font* getFont();
	const SDL_Color getColor();

	void setText(string text);
	void setFont(Font* font);
	void setColor(SDL_Color color);

private:
	Font* font_;
	string text_;
	SDL_Color color_;

	bool reload();
};

