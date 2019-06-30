#pragma once
#include "Container.h"
#include "Animation.h"
class PauseMenu :
	public Container, public Observer, public Observable
{
public:
	PauseMenu();
	~PauseMenu();
	virtual bool receiveEvent(Event& e) override;
protected:
	Animation* menu_;
	bool pausa;
};

