#pragma once
#include "ImpactComponent.h"
class ExplosiveImC :
	public ImpactComponent
{
public:
	ExplosiveImC(Proyectile* o, int radius=200);
	virtual void Impact(b2Contact* contact);
	virtual ~ExplosiveImC();

private:
	int radius_;
};

