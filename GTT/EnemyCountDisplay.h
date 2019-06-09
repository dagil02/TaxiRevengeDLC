#pragma once
#include "Container.h"
#include "Text.h"

class EnemyCountDisplay :
	public Container
{
public:
	EnemyCountDisplay();
	virtual void update(Uint32 deltaTime);
	virtual ~EnemyCountDisplay();

private:
	Text* enemyCount_;
	Font* font_;
};

