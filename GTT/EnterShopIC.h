#pragma once
#include "InputComponent.h"
class EnterShopIC :
	public InputComponent {
public:
	EnterShopIC ();
	virtual ~EnterShopIC ();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
};

