#include "DeathState.h"
#include "Game.h"



DeathState::DeathState()
{
}


DeathState::~DeathState()
{
}

void DeathState::start() {
	timer = SDL_GetTicks() / 1000;
	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);

	// BACKGROUND
	setBackground();

	//Container to GameObj list
	stage_.push_back(background_);
	//stage_.push_back(Reticule::getInstance());
}

void DeathState::end() {
}

void DeathState::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	if(SDL_GetTicks() / 1000 - timer < 5)

	GameState::update(deltaTime);
}

void DeathState::setBackground() {
	backgroundSprite_ = new Sprite(DEATH_BACKGROUND_INFO.idlePath, DEATH_BACKGROUND_INFO.width, DEATH_BACKGROUND_INFO.height);

	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->addRenderComponent(backgroundSprite_);
}

