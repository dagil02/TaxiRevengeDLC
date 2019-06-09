#pragma once
#include "LogicComponent.h"

class EnemyShoot :
	public LogicComponent
{
public:
	EnemyShoot();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~EnemyShoot();
};

