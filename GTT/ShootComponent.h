#pragma once
#include "Turret.h"

class ProyectilePool;

class ShootComponent
{
public:
	ShootComponent(Turret* turret);
	virtual void changeProperties(double prop1, int prop2) = 0;
	virtual void shoot(ProyectileInfo prType, bool isAnEnemy)=0;
	virtual ~ShootComponent();
protected:
	Turret* turret_;
};

