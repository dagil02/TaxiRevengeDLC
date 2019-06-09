#pragma once
#include "ImpactComponent.h"
class BounceImC :
	public ImpactComponent
{
public:
	BounceImC(Proyectile* o, int maxBounces=4);
	virtual void Impact(b2Contact* contact);
	virtual ~BounceImC();

private:
	int maxBounces_;
	int bounces_;
	double timelastBounce_;
};

