#pragma once

#include "GameObject.h"


class InputComponent {
public:
	InputComponent();
	virtual ~InputComponent();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event) = 0;
};

