#include "CursorLC.h"
#include "Game.h"


CursorLC::CursorLC()
{
}

void CursorLC::update(GameObject * o, Uint32 deltaTime)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	o->setPosition(Vector2D(((double)x/(double)Game::getInstance()->getWindowWidth())*(double)Game::getInstance()->getCameraWidth() - o->getWidth()/2,
		((double)y / (double)Game::getInstance()->getWindowHeight())*(double)Game::getInstance()->getCameraHeight()- o->getHeight()/2));
}


CursorLC::~CursorLC()
{
}
