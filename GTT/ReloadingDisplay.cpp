#include "ReloadingDisplay.h"
#include "Game.h"
#include "Turret.h"


ReloadingDisplay::ReloadingDisplay()
{
	setWidth(250); setHeight(58);
	setPosition(Vector2D(Game::getInstance()->getCamera(UI_CAMERA)->getWidth() * 0.5 - getWidth() * 0.5, Game::getInstance()->getCamera(UI_CAMERA)->getHeight() *0.90));

	background = new Sprite("./../Assets/sprites/ReloadBarBackground.png");
	background->setCamera(UI_CAMERA);

	bar = new Sprite("./../Assets/sprites/ReloadBar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setAutoPos(false);
	
	bar->setSize(getWidth()*0.875, getHeight());
	bar->setPos(getPosition().x+0.0625*getWidth(), getPosition().y);
	barWidth = bar->getRect()->w;

	perfReSegment = new Sprite("./../Assets/sprites/PerfReInd.png");
	perfReSegment->setCamera(UI_CAMERA);
	perfReSegment->setAutoSize(false);
	perfReSegment->setAutoPos(false);

	addRenderComponent(bar);
	addRenderComponent(background);
	addRenderComponent(perfReSegment);

	bar_clip = new SDL_Rect();
}

void ReloadingDisplay::setReloadingPercentage()
{
	if (Vehicle::getInstance()->getCurrentTurret() != nullptr) {
		Texture* tex = bar->getTexture();
		bar_clip->x = bar_clip->y = 0;
		bar_clip->w = tex->getWidth() * Vehicle::getInstance()->getCurrentTurret()->GetReloadPercentage();
		bar_clip->h = tex->getHeight();

		bar->setSize(barWidth *  Vehicle::getInstance()->getCurrentTurret()->GetReloadPercentage(), getHeight());
		bar->setClipRect(bar_clip);
		perfReSegment->setSize(barWidth*Vehicle::getInstance()->getCurrentTurret()->GetPerfReloadSeg(), getHeight());
		perfReSegment->setPos(bar->getRect()->x + barWidth * Vehicle::getInstance()->getCurrentTurret()->GetPerfReloadIni(), getPosition().y);
	}
}

ReloadingDisplay::~ReloadingDisplay()
{
	delete bar;
	delete background;
	delete perfReSegment;
}

void ReloadingDisplay::update(Uint32 deltaTime)
{
	setReloadingPercentage();
}

void ReloadingDisplay::render(Uint32 deltaTime)
{
	Container::render(deltaTime);
	
}

bool ReloadingDisplay::isReloading()
{
	if (Vehicle::getInstance()->getCurrentTurret() == nullptr)return false;
	return Vehicle::getInstance()->getCurrentTurret()->isReloading();
}
