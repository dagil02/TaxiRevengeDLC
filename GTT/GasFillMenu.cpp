#include "GasFillMenu.h"
#include "Reticule.h"
#include "Game.h"
#include "Vehicle.h"
#include "Money.h"


GasFillMenu::GasFillMenu () {
}


GasFillMenu::~GasFillMenu () {
	delete background_; background_ = nullptr;
	delete blackBackground_; blackBackground_ = nullptr;
	delete backgroundSprite_;
	delete blackBackgoundSprite_;
	delete blackBackgroundToPaySprite_;
	delete fill_5_Sprite_;
	delete fill_10_Sprite_;
	delete fill_25_Sprite_;
	delete backSprite_;
	delete paySprite_;
	delete healthDisplay_; healthDisplay_ = nullptr;
	delete moneyDisplay_; moneyDisplay_ = nullptr;

	for (auto button : buttons_) {
		delete button.second; button.second = nullptr;
	}
	buttons_.clear();
}


void GasFillMenu::start () {
	int i; //recoge el valor del index si el elemento est� en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);
	
	// BACKGROUND
	setBackground ();

	// BUTTONS
	setButtons ();
	setButtonComponents ();

	// health display (not the same object as in the UI so there's no need to hide the rest of the UI and reposition the bar every state change)
	healthDisplay_ = new HealthDisplay(); 
	healthDisplay_->reposition (GAS_MENU_HEALTH_BAR_POSITION);
	healthDisplay_->setHealthPercentage (float (Vehicle::getInstance ()->getHealthComponent ()->getHealth ()) / Vehicle::getInstance ()->getHealthComponent ()->getMaxHealth ());

	//Money Display
	moneyDisplay_ = new MoneyDisplay();
	moneyDisplay_->reposition(Vector2D(BLACK_BACKGROUND_POS.x + BLACK_BACKGROUND_W * 0.85 , BLACK_BACKGROUND_POS.y + BLACK_BACKGROUND_H / 2 - moneyDisplay_->getHeight() / 1.5),1.5);

	//To Pay Display
	toPayDisplay_ = new MoneyDisplay();
	toPayDisplay_->reposition(TOPAY_DISPLAY_POS,1.4);
	toPayDisplay_->setSimpleMoney(0);
	//To pay string
	toPayText_ = new Container();
	toPayString_ = new Text(new Font(FONT_COOLFONT, 50), "To Pay:", SDL_Color({ 255, 255, 255 }));
	toPayString_->setCamera(UI_CAMERA);
	toPayText_->setWidth(toPayString_->getFont()->getSize()*toPayString_->getText().length());
	toPayText_->setHeight(toPayString_->getFont()->getSize());
	toPayText_->setPosition(Vector2D(TOPAY_DISPLAY_POS.x - toPayString_->getFont()->getSize()*toPayString_->getText().length() / 1.5, TOPAY_DISPLAY_POS.y - toPayText_->getHeight() - 25));
	toPayText_->addRenderComponent(toPayString_);
	
	//Container to GameObj list
	stage_.push_back(background_);
	stage_.push_back(blackBackground_);
	stage_.push_back(blackBackgroundToPay_);
	stage_.push_back(toPayText_);
	stage_.push_back(buttons_["fill_5_Button"]);
	stage_.push_back(buttons_["fill_10_Button"]);
	stage_.push_back(buttons_["fill_25_Button"]);
	stage_.push_back(buttons_["backButton"]);
	stage_.push_back(buttons_["payButton"]);
	stage_.push_back (healthDisplay_);
	stage_.push_back(moneyDisplay_);
	stage_.push_back(toPayDisplay_);
	stage_.push_back(Reticule::getInstance());
}


void GasFillMenu::end () {
}

void GasFillMenu::updateState()
{
	moneyDisplay_->setSimpleMoney(Money::getInstance()->getCurrentMoney());
	healthDisplay_->setHealthPercentage(float(Vehicle::getInstance()->getHealthComponent()->getHealth()) / Vehicle::getInstance()->getHealthComponent()->getMaxHealth());
	moneySpent_ = 0;
	refilled_ = 0;
}


void GasFillMenu::update (Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}


bool GasFillMenu::receiveEvent (Event & e) {
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);
		int max = Vehicle::getInstance ()->getHealthComponent ()->getMaxHealth ();
		int moneyAvailable = Money::getInstance()->getCurrentMoney();

		if (MouseClickLeft_.button_ == buttons_["fill_5_Button"]->getIndex()) {
			if (moneyAvailable - moneySpent_ > PRICE_FOR_5 && Vehicle::getInstance()->getHealthComponent()->getHealth() + (max * 0.05) <= max){
				moneySpent_ += PRICE_FOR_5;
				refilled_ += 0.05;
				Vehicle::getInstance()->getHealthComponent()->heal(int(max * 0.05));
			}
		}
		else if (MouseClickLeft_.button_ == buttons_["fill_10_Button"]->getIndex ()) {
			if (moneyAvailable - moneySpent_ > PRICE_FOR_10 && Vehicle::getInstance()->getHealthComponent()->getHealth() + (max * 0.10) <= max) {
				moneySpent_ += PRICE_FOR_10;
				refilled_ += 0.10;
				Vehicle::getInstance()->getHealthComponent()->heal(int(max * 0.10));
			}
		}
		else if (MouseClickLeft_.button_ == buttons_["fill_25_Button"]->getIndex ()) {
			if (moneyAvailable - moneySpent_ > PRICE_FOR_25 && Vehicle::getInstance()->getHealthComponent()->getHealth() + (max * 0.25) <= max) {
				moneySpent_ += PRICE_FOR_25;
				refilled_ += 0.25;
				Vehicle::getInstance()->getHealthComponent()->heal(int(max * 0.25));
			}
		}
		else if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex ()) {
			if (refilled_ != 0)
				Vehicle::getInstance()->getHealthComponent()->heal(-int(max * refilled_));
			updateState();
			Game::getInstance ()->getGameStateMachine ()->fromFillMenuToGasMainMenu ();
		}

		else if (MouseClickLeft_.button_ == buttons_["payButton"]->getIndex())
		{
			Money::getInstance()->addMoney(-moneySpent_);
			updateState();
		}

		healthDisplay_->setHealthPercentage ((Vehicle::getInstance ()->getHealthComponent ()->getHealth () / float (max)));
		toPayDisplay_->setSimpleMoney(moneySpent_);
		break;
	}
	default:
		break;
	}
	return true;
}


void GasFillMenu::setBackground() {
	//Global background
	backgroundSprite_ = new Sprite(GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->addRenderComponent(backgroundSprite_);

	//Gas amount background
	blackBackgoundSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, BLACK_BACKGROUND_INFO.width, BLACK_BACKGROUND_INFO.height);
	blackBackground_ = new Container();

	blackBackground_->setWidth(BLACK_BACKGROUND_INFO.width);
	blackBackground_->setHeight(BLACK_BACKGROUND_INFO.height);
	blackBackground_->setPosition(BLACK_BACKGROUND_INFO.pos);
	blackBackground_->addRenderComponent(blackBackgoundSprite_);

	//To pay background
	blackBackgroundToPaySprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, TOPAY_BACKGROUND_INFO.width, TOPAY_BACKGROUND_INFO.height);
	blackBackgroundToPay_ = new Container();

	blackBackgroundToPay_->setWidth(TOPAY_BACKGROUND_INFO.width);
	blackBackgroundToPay_->setHeight(TOPAY_BACKGROUND_INFO.height);
	blackBackgroundToPay_->setPosition(TOPAY_BACKGROUND_INFO.pos);
	blackBackgroundToPay_->addRenderComponent(blackBackgroundToPaySprite_);
}


void GasFillMenu::setButtons () {
	// build
	buttons_["fill_5_Button"] = new Button();
	buttons_["fill_5_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["fill_10_Button"] = new Button();
	buttons_["fill_10_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["fill_25_Button"] = new Button();
	buttons_["fill_25_Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);
	buttons_["payButton"] = new Button();
	buttons_["payButton"]->getMouseClickIC()->registerObserver(this);


	// set
	buttons_["fill_5_Button"]->setPosition(GAS_5_BUTTON_POSITION);
	buttons_["fill_5_Button"]->setWidth(GAS_5_BUTTON_INFO.width);
	buttons_["fill_5_Button"]->setHeight(GAS_5_BUTTON_INFO.height);
	buttons_["fill_5_Button"]->setIndex(1);

	buttons_["fill_10_Button"]->setPosition(GAS_10_BUTTON_POSITION);
	buttons_["fill_10_Button"]->setWidth(GAS_10_BUTTON_INFO.width);
	buttons_["fill_10_Button"]->setHeight(GAS_10_BUTTON_INFO.height);
	buttons_["fill_10_Button"]->setIndex(2);

	buttons_["fill_25_Button"]->setPosition(GAS_25_BUTTON_POSITION);
	buttons_["fill_25_Button"]->setWidth(GAS_25_BUTTON_INFO.width);
	buttons_["fill_25_Button"]->setHeight(GAS_25_BUTTON_INFO.height);
	buttons_["fill_25_Button"]->setIndex(3);

	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(4);

	buttons_["payButton"]->setPosition(PAY_BUTTON_POSITION);
	buttons_["payButton"]->setWidth(PAY_BUTTON_INFO.width);
	buttons_["payButton"]->setHeight(PAY_BUTTON_INFO.height);
	buttons_["payButton"]->setIndex(5);
}


void GasFillMenu::setButtonComponents () {
	fill_5_Sprite_ = new Sprite (GAS_5_BUTTON_INFO.idlePath, GAS_5_BUTTON_INFO.width, GAS_5_BUTTON_INFO.height, GAS_5_BUTTON_POSITION.x, GAS_5_BUTTON_POSITION.y);
	fill_10_Sprite_ = new Sprite (GAS_10_BUTTON_INFO.idlePath, GAS_10_BUTTON_INFO.width, GAS_10_BUTTON_INFO.height, GAS_10_BUTTON_POSITION.x, GAS_10_BUTTON_POSITION.y);
	fill_25_Sprite_ = new Sprite (GAS_25_BUTTON_INFO.idlePath, GAS_25_BUTTON_INFO.width, GAS_25_BUTTON_INFO.height, GAS_25_BUTTON_POSITION.x, GAS_25_BUTTON_POSITION.y);
	backSprite_ = new Sprite (BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);
	paySprite_ = new Sprite(PAY_BUTTON_INFO.idlePath, PAY_BUTTON_INFO.width, PAY_BUTTON_INFO.height, PAY_BUTTON_POSITION.x, PAY_BUTTON_POSITION.y);

	buttons_["fill_5_Button"]->addRenderComponent (fill_5_Sprite_);
	buttons_["fill_10_Button"]->addRenderComponent (fill_10_Sprite_);
	buttons_["fill_25_Button"]->addRenderComponent (fill_25_Sprite_);
	buttons_["backButton"]->addRenderComponent (backSprite_);
	buttons_["payButton"]->addRenderComponent(paySprite_);
}
