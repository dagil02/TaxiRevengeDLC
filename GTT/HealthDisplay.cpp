#include "HealthDisplay.h"
#include <string>

HealthDisplay::HealthDisplay() {
	setPosition(Vector2D(35, 35));
	setWidth(300); setHeight(75);
	
	//fuHealth  display background
	background = new Sprite("./../Assets/sprites/healthMeter-empty.png");
	background->setCamera(UI_CAMERA);

	//fuHealth  display foreground
	bar = new Sprite("./../Assets/sprites/healthMeter-bar.png");
	bar->setCamera(UI_CAMERA);
	bar->setAutoSize(false);
	bar->setSize(getWidth()*0.633, getHeight()*0.409);//size and position relative to background sprite do not change
	bar->setAutoPos(false);
	bar->setPos(position_.x + getWidth()*0.267, position_.y + getHeight()*0.284);

	bardefaultwidth = getWidth()*0.633;
	
	addRenderComponent(background);
	addRenderComponent(bar);

	bar_clip = new SDL_Rect();

	//Percentage of current fuHealth
	SDL_Color fontColor = SDL_Color();
	fontColor.r = 255; fontColor.g = 255; fontColor.b = 255;
	f_ = new Font(FONT_COOLFONT, 60);
	fuhealthAmount_ = new Text(f_, "", fontColor);
	fuhealthAmount_->setCamera(UI_CAMERA);
	addRenderComponent(fuhealthAmount_);
	fuhealthAmount_->setText(to_string((int)(healthPercentage_ * 100)) + " %");
	fuhealthAmount_->setAutoPos(false);
	fuhealthAmount_->setPos(getPosition().x + 5 + getWidth(), getPosition().y + getHeight() * 0.23);
	fuhealthAmount_->setAutoSize(false);
	fuhealthAmount_->setSize(90, 40);
}

HealthDisplay::~HealthDisplay() {
	delete background;
	delete bar;
	delete f_;
	delete fuhealthAmount_;
}

// Percentage from 0 to 1
void HealthDisplay::setHealthPercentage(float healthPercentage) {
	healthPercentage_ = healthPercentage;
	if (healthPercentage_ < 0) healthPercentage_ = 0;
	Texture* tex = bar->getTexture();
	bar_clip->x = bar_clip->y = 0;
	bar_clip->w = tex->getWidth() * healthPercentage_;
	bar_clip->h = tex->getHeight();

	bar->setSize(bardefaultwidth * healthPercentage_, bar->getRect()->h);
	bar->setClipRect(bar_clip);
	
	fuhealthAmount_->setText(to_string((int)(healthPercentage_ * 100)) + " %");

}


int HealthDisplay::getHealthPercentage() {
	return healthPercentage_;
}


void HealthDisplay::reposition (Vector2D newPos) {
	setPosition (newPos);
	bar->setPos(position_.x + getWidth()*0.267, position_.y + getHeight()*0.284);
	fuhealthAmount_->setPos(getPosition().x + 5 + getWidth(), getPosition().y + getHeight() * 0.23);
}
