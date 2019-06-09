#pragma once
#include "LogicComponent.h"

class CursorLC : public LogicComponent {
public:
	CursorLC();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~CursorLC();
};

