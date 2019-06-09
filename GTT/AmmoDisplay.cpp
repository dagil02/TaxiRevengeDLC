#include "AmmoDisplay.h"
#include "Turret.h"
#include <string>
using namespace std;

AmmoDisplay::AmmoDisplay()
{

	setPosition(Vector2D(Game::getInstance()->getCamera(UI_CAMERA)->getWidth()*0.05, Game::getInstance()->getCamera(UI_CAMERA)->getHeight()*0.9));

	background_ = new Sprite("./../Assets/sprites/ammo-bg.png");
	background_->setCamera(UI_CAMERA);

	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	font_ = new Font(FONT_COOLFONT, 80);
	currentAmmo_ = new Text(font_, "", fontColor);
	currentAmmo_->setCamera(UI_CAMERA);

	addRenderComponent(background_);
	addRenderComponent(currentAmmo_);

	currentAmmo_->setAutoPos(true);
	currentAmmo_->setAutoSize(false);
	currentAmmo_->setSize(100, 40);

	background_->setAutoPos(false);
	background_->setPos(position_.x - 40, position_.y - 10);
	background_->setAutoSize(false);
	background_->setSize(250, 60);
}

void AmmoDisplay::update(Uint32 deltaTime)
{
	if(Vehicle::getInstance()->getCurrentTurret()!=nullptr)
	currentAmmo_->setText(to_string((int)(Vehicle::getInstance()->getCurrentTurret()->GetAmmo())) + " / " + to_string((int)(Vehicle::getInstance()->getCurrentTurret()->GetMaxAmmo())));
}


AmmoDisplay::~AmmoDisplay() {
	delete font_; font_ = nullptr;
	delete currentAmmo_; currentAmmo_ = nullptr;
	delete background_; background_ = nullptr;
}
