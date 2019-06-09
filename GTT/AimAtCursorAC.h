#pragma once
#include "AimComponent.h"
class AimAtCursorAC :public AimComponent
{
public:
	AimAtCursorAC() {};
	virtual ~AimAtCursorAC() {};
	virtual void update(GameObject* o, Uint32 deltaTime);
};

