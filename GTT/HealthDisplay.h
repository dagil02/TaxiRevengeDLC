#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Text.h"

class HealthDisplay : public Container {
public:
	HealthDisplay();
	virtual ~HealthDisplay();

	void setHealthPercentage(float healthPercentage);
	int getHealthPercentage();

	void reposition (Vector2D newPos);

private:
	Sprite* background;
	Sprite* bar;
	SDL_Rect* bar_clip;
	float bardefaultwidth;

	Font* f_;
	Text* fuhealthAmount_;

	float healthPercentage_;
};

