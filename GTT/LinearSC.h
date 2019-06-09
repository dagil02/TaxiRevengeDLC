#pragma once
#include "ShootComponent.h"

//Componente de disparo para armas que disparan balas de una en una con 
//una trayectoria lineal

class LinearSC : public ShootComponent
{
public:
	LinearSC(Turret* turret, double innac=0, int prob=0);
	virtual void shoot(ProyectileInfo prType, bool isAnEnemy);
	virtual void changeProperties(double prop1, int prop2) {};
	virtual ~LinearSC() {};

private:
	double innacuracy_;//grado de imprecision
	int probab_;//probabilidad con la que el arma es imprecisa en %
};

