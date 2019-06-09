#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"

class GasMainMenu :
	public GameState, public Observer, public Observable {
public:
	GasMainMenu ();
	virtual ~GasMainMenu ();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);

private:
	Container *background_;
	Sprite *backgroundSprite_;

	map<string, Button*> buttons_;
	Sprite *fillSprite_, *gunSprite_, *backSprite_;

	void setBackground ();
	void setButtons ();
	void setButtonComponents ();
};

