#pragma once
#include "Container.h"
#include "Observer.h"
#include "Text.h"

class MoneyDisplay : public Container {
public:
	MoneyDisplay(Font* font = new Font(FONT_LATO, 60), SDL_Color fontColor = SDL_Color({255, 255, 255}), int currentMoney = 0);
	virtual ~MoneyDisplay();

	void setMoney(int money);
	void setSimpleMoney(int money);
	void reposition(Vector2D v, double increase);

private:
	Text* textSprite_;
	string currencyString_ = " $";
};

