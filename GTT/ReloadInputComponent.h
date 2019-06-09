#pragma once
#include "InputComponent.h"
class ReloadInputComponent :
	public InputComponent
{
public:
	ReloadInputComponent(SDL_Keycode reloadkey = SDLK_r);
	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual ~ReloadInputComponent();

private:
	SDL_Keycode reloadkey_;
};

