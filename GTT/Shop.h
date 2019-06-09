#pragma once
#include "Trigger.h"

class Shop : public Trigger {
public:
	Shop(int w, int h, int x, int y);
	virtual ~Shop();

protected:
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
};

