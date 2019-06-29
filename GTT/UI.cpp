
#include "UI.h"

UI *UI::singleton_ = nullptr;

UI::UI() {
	UIElements_ = vector<GameObject*>();

	// Common font for all UI elements
	font_ = new Font(FONT_LATO, 60);
	fontColor_ = SDL_Color();
	fontColor_.r = 255; fontColor_.g = 255; fontColor_.b = 255;

	// DISPLAYS

	// Health
	healthDisplay_ = new HealthDisplay();
	UIElements_.push_back(healthDisplay_);

	// Money
	moneyDisplay_ = new MoneyDisplay(font_, fontColor_);
	UIElements_.push_back(moneyDisplay_);

	//Ammo
	ammoDisplay_ = new AmmoDisplay();
	UIElements_.push_back(ammoDisplay_);

	//Dialogues
	dialogues_ = new DialoguesManager();
	UIElements_.push_back(dialogues_);

	//Reload
	reloadDisplay_ = new ReloadingDisplay();
	UIElements_.push_back(reloadDisplay_);

	// Enemy count
	enemyCount_ = new EnemyCountDisplay();
	UIElements_.push_back(enemyCount_);

	pauseMenu = nullptr;
	

	pausa(true);
}


UI::~UI() {
	for (vector<GameObject*>::iterator it = UIElements_.begin(); it != UIElements_.end(); it++) {
		delete (*it); (*it) = nullptr;
	}
	UIElements_.clear();

	delete font_; font_ = nullptr;
}

UI * UI::getInstance() {
	if (singleton_ == nullptr)
		singleton_ = new UI();

	return singleton_;
}

void UI::render(Uint32 deltaTime) {
	
	for (auto element : UIElements_) {
		element->render(deltaTime);
	}

	pauseMenu->render(Vector2D(123, 567), 200, 200);
}

void UI::update(Uint32 deltaTime)
{
	dialogues_->update(deltaTime);
	
	if (reloadDisplay_ != nullptr)
		reloadDisplay_->setActive(reloadDisplay_->isReloading());
	for (auto element : UIElements_) {
		element->update(deltaTime);
	}
}

void UI::addUIElement(Container * c)
{
	UIElements_.push_back(c);
}


bool UI::receiveEvent(Event& e) {
	if (e.type_ == HEALTH_CHANGED) {
		HealthChangedEvent* he = static_cast<HealthChangedEvent*>(&e);
		healthDisplay_->setHealthPercentage((float) he->currentHealth_/he->maxHealth_);
	}
	else if (e.type_ == MONEY_CHANGED) {
		moneyDisplay_->setMoney(static_cast<MoneyChangedEvent*>(&e)->currentMoney_);
	}

	return true;
}

void UI::setAmmoActive(bool active) const {
	ammoDisplay_->setActive(active);
}

void UI::pausa(bool pause)
{
	if (pause) pauseMenu = new Sprite("../Assets/sprites/damageupgrade.png");
	else { 
		delete pauseMenu;
		pauseMenu = nullptr;
	}
}

