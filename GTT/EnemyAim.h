#pragma once
#include "AimComponent.h"
class EnemyAim :
	public AimComponent
{
public:
	EnemyAim();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~EnemyAim();
};

