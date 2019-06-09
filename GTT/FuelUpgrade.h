#pragma once
#include "Trigger.h"
#include "Animation.h"
#include "Vehicle.h"

class FuelUpgrade : public Trigger
{
public:
	FuelUpgrade(int w, int h, int x, int y);
	~FuelUpgrade();


private:
	Animation* sprite_;

protected:
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
};

