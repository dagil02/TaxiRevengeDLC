#pragma once
#include "InputComponent.h"
class ChangeWeaponIC :
	public InputComponent
{
public:
	ChangeWeaponIC(SDL_Keycode changekey=SDLK_q);
	virtual ~ChangeWeaponIC() {};
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);

private:
	SDL_Keycode changekey_;
};

