#pragma once
#include "Trigger.h"
#include "Animation.h"
#include "Vehicle.h"

class SpeedUpgrade : public Trigger
{
public:
	SpeedUpgrade(int w, int h, int x, int y);
	~SpeedUpgrade();


private:
	Animation* sprite_;

protected:
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
};

