#pragma once
#include "Container.h"
#include "Text.h"
#include "Vehicle.h"

class AmmoDisplay :
	public Container
{
public:
	AmmoDisplay();
	virtual void update(Uint32 deltaTime);
	virtual ~AmmoDisplay();

private:
	Text* currentAmmo_;
	Font* font_;
	Sprite* background_;
};

