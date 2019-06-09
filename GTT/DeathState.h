#pragma once
#include "GameState.h"
#include "Container.h"
#include "Sprite.h"
class DeathState :public GameState
{
public:
	DeathState();
	virtual ~DeathState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime);

private:
	Container *background_;
	Sprite *backgroundSprite_;

	Sprite *fillSprite_, *gunSprite_, *backSprite_;
	int timer = 0;
	void setBackground();
};

