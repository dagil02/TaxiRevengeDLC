#pragma once

#include "GameObject.h"


class LogicComponent
{
public:
	LogicComponent();
	virtual ~LogicComponent();

	virtual void update(GameObject* o, Uint32 deltaTime) = 0;
};

