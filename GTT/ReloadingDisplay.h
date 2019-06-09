#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Vehicle.h"

class ReloadingDisplay :
	public Container
{
public:
	ReloadingDisplay();
	void setReloadingPercentage();
	virtual ~ReloadingDisplay();
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);
	virtual bool isReloading();


private:
	Sprite* background;
	Sprite* bar;
	Sprite* perfReSegment;
	SDL_Rect* bar_clip;
	double barWidth;

};

