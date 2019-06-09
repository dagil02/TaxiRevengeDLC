#include "AimAtCursorAC.h"
#include "Reticule.h"
#include "Game.h"

void AimAtCursorAC::update(GameObject * o, Uint32 deltaTime)
{
	double disX = Reticule::getInstance()->getCenter().x + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().x - o->getCenter().x;
	double disY = Reticule::getInstance()->getCenter().y + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().y - o->getCenter().y;
	double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));
	o->setRotation(degrees * 180.0 / M_PI);
	if (disX < 0)
		o->setRotation(-o->getRotation());
}
