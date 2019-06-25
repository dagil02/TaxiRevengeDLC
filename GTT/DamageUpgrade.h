#pragma once
#include "Trigger.h"
#include "Animation.h"
#include "Vehicle.h"

class DamageUpgrade : public Trigger
{
public:
	DamageUpgrade(int w, int h, int x, int y);
	~DamageUpgrade();
private:
	Animation* sprite_;
	int boostTime = 15000;

protected:
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
};

