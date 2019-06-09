#pragma once
#include "ControlType.h"

class ShootIC :
	public ControlType
{
public:
	ShootIC(int shootkey=SDL_BUTTON_LEFT);
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual void ChangeInputMode(bool hold);
	virtual ~ShootIC();
private:
	int shootkey_;
	bool holdToShoot_=false;
	bool held_=false;

};

