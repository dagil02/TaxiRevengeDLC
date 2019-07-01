#pragma once
#include "Container.h"
#include "Sprite.h"
#include "GameState.h"
class PauseMenu :
	public GameState,public Container, public Observer, public Observable
{
public:
	PauseMenu();
	~PauseMenu();
	virtual void start() override;
	virtual void end() override;
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event);
protected:
	Sprite* menu_;
	Container* background_;
	bool pausa;
};

