#include "EnemyCountDisplay.h"
#include "GameManager.h"
#include "Game.h"
#include <string>
using namespace std;


EnemyCountDisplay::EnemyCountDisplay()
{
	setPosition(Vector2D((Game::getInstance()->getCamera(UI_CAMERA)->getWidth() / 2) - 100, 35));
	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	font_ = new Font(FONT_LATO, 80);

	enemyCount_ = new Text(font_, "", fontColor);
	enemyCount_->setCamera(UI_CAMERA);
	addRenderComponent(enemyCount_);

	enemyCount_->setAutoSize(false);

	enemyCount_->setSize(200, 40);
}

void EnemyCountDisplay::update(Uint32 deltaTime)
{
	enemyCount_->setText(to_string((int)GameManager::getInstance()->getEnemyCount()) + " enemies left" );
}


EnemyCountDisplay::~EnemyCountDisplay() {
	delete enemyCount_; enemyCount_ = nullptr;
	delete font_; font_ = nullptr;
}
