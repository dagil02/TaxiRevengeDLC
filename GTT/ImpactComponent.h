#pragma once
#include "Proyectile.h"

class ImpactComponent
{
public:
	ImpactComponent(Proyectile* o);
	virtual void Impact(b2Contact * contact);
	virtual ~ImpactComponent();
protected:
	Proyectile* o_;
};

