#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
#include "HealthDisplay.h"
#include "MoneyDisplay.h"

class GasFillMenu : public GameState, public Observer, public Observable {
public:
	GasFillMenu ();
	virtual ~GasFillMenu ();

	virtual void start() override;
	virtual void end() override;
	virtual void updateState();

	virtual void update(Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);

private:
	Container *background_, *blackBackground_, *blackBackgroundToPay_, *toPayText_;
	Sprite *backgroundSprite_, *blackBackgoundSprite_, *blackBackgroundToPaySprite_;

	map<string, Button*> buttons_;
	Sprite *fill_5_Sprite_, *fill_10_Sprite_, *fill_25_Sprite_, *backSprite_, *paySprite_;

	HealthDisplay *healthDisplay_;
	MoneyDisplay *moneyDisplay_, *toPayDisplay_;

	Text *toPayString_;

	int moneySpent_ = 0;
	float refilled_ = 0;

	void setBackground ();
	void setButtons ();
	void setButtonComponents ();
};

