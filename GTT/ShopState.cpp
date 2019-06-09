#include "ShopState.h"
#include "Reticule.h"
#include "Game.h"
#include <string.h>
#include "Vehicle.h"
#include "Turret.h"
#include "Money.h"

ShopState::ShopState() {
}

ShopState::~ShopState() {
	delete backSprite_;
	delete backgroundSprite_;
	delete bckPistolSprite_;
	delete bckShotgunSprite_;
	delete bckRifleSprite_;
	delete bckMachinegunSprite_;
	delete weapon1ButtonSprite_;
	delete weapon2ButtonSprite_;
	delete weapon3ButtonSprite_;
	delete weapon4ButtonSprite_;
	delete pistolSprite_;
	delete shotgunSprite_;
	delete rifleSprite_;
	delete machinegunSprite_;
	delete weapon1Sprite_;
	delete weapon2Sprite_;
	delete weapon1OwnedS_;
	delete weapon2OwnedS_;
	delete weapon3OwnedS_;
	delete weapon4OwnedS_;


	for (auto button : buttons_) {
		delete button.second; button.second = nullptr;
	}
	buttons_.clear();
}

void ShopState::start() {
	int i; //recoge el valor del index si el elemento está en el vector
	if (!isRegistered(this, i))
		registerObserver(this);

	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);

	//Initialize owned
	for (size_t i = 0; i < 3; i++)	owned_[i] = false;
		
	owned_[0] = true;

	setBackground();
	setButtons();
	setButtonComponents();
	startTexts();
	startIcons();

	//Money Display
	moneyDisplay_ = new MoneyDisplay(new Font(FONT_LATO, 60), SDL_Color({ 225, 160, 0 }));
	moneyDisplay_->reposition(Vector2D(CAMERA_WIDHT / 1.3, CAMERA_HEIGHT / 1.5), 1.5);
	
	//Container to GameObj list
	stage_.push_back(background_);				//Backgrounds
	stage_.push_back(bckPistol_);
	stage_.push_back(bckShotgun_);
	stage_.push_back(bckRifle_);
	stage_.push_back(bckMachinegun_);
	stage_.push_back(weapon1_);
	stage_.push_back(weapon2_);


	stage_.push_back(buttons_["backButton"]);		//Buttons
	stage_.push_back(buttons_["weapon1Button"]);
	stage_.push_back(buttons_["weapon2Button"]);
	stage_.push_back(buttons_["weapon3Button"]);
	stage_.push_back(buttons_["weapon4Button"]);

	stage_.push_back(pistol_);						//Icons
	stage_.push_back(shotgun_);
	stage_.push_back(rifle_);
	stage_.push_back(machinegun_);
	stage_.push_back(moneyDisplay_);

	stage_.push_back(weapon1Owned_);				//Owned
	stage_.push_back(weapon2Owned_);
	stage_.push_back(weapon3Owned_);
	stage_.push_back(weapon4Owned_);


	stage_.push_back(armory_);						//Texts
	stage_.push_back(inventory_);
	stage_.push_back(pistolT_);
	stage_.push_back(shotgunT_);
	stage_.push_back(rifleT_);
	stage_.push_back(machinegunT_);

	stage_.push_back(pistolI_);					//Inventory weapons
	stage_.push_back(shotgunI_);
	stage_.push_back(rifleI_);
	stage_.push_back(machinegunI_);

	stage_.push_back(Reticule::getInstance());
}

void ShopState::end() {
}

void ShopState::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}

void ShopState::updateState()
{
	moneyDisplay_->setSimpleMoney(Money::getInstance()->getCurrentMoney());
}

bool ShopState::receiveEvent(Event & e)
{
	switch (e.type_)
	{
	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);
		if (MouseClickLeft_.button_ == buttons_["backButton"]->getIndex())
			Game::getInstance()->getGameStateMachine()->fromFillMenuToGasMainMenu();

		else if (MouseClickLeft_.button_ == buttons_["weapon1Button"]->getIndex())
		{
			
			selected(0);
		}

		else if (MouseClickLeft_.button_ == buttons_["weapon2Button"]->getIndex())
		{
				selected(1);
		}

		else if (MouseClickLeft_.button_ == buttons_["weapon3Button"]->getIndex())
		{
			selected(2);
		}

		else if (MouseClickLeft_.button_ == buttons_["weapon4Button"]->getIndex())
		{
			selected(3);
		}
	}
	default:
		break;
	}
	return true;
}

void ShopState::setButtons()
{
	//Build
	buttons_["backButton"] = new Button();
	buttons_["backButton"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon1Button"] = new Button();
	buttons_["weapon1Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon2Button"] = new Button();
	buttons_["weapon2Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon3Button"] = new Button();
	buttons_["weapon3Button"]->getMouseClickIC()->registerObserver(this);
	buttons_["weapon4Button"] = new Button();
	buttons_["weapon4Button"]->getMouseClickIC()->registerObserver(this);

	//Set
	buttons_["backButton"]->setPosition(BACK_BUTTON_POSITION);
	buttons_["backButton"]->setWidth(BACK_BUTTON_INFO.width);
	buttons_["backButton"]->setHeight(BACK_BUTTON_INFO.height);
	buttons_["backButton"]->setIndex(1);

	buttons_["weapon1Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W ,FIRST_WEAPON_BCK.y));
	buttons_["weapon1Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon1Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon1Button"]->setIndex(2);

	buttons_["weapon2Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 125));
	buttons_["weapon2Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon2Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon2Button"]->setIndex(3);

	buttons_["weapon3Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 250));
	buttons_["weapon3Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon3Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon3Button"]->setIndex(4);

	buttons_["weapon4Button"]->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W + WEAPON_BUTTON_W , FIRST_WEAPON_BCK.y + 375));
	buttons_["weapon4Button"]->setWidth(WEAPON_BUTTON_W);
	buttons_["weapon4Button"]->setHeight(WEAPON_BUTTON_H);
	buttons_["weapon4Button"]->setIndex(5);
}

void ShopState::setBackground()
{
	//Global background
	backgroundSprite_ = new Sprite(GAS_BACKGROUND_INFO.idlePath, GAS_BACKGROUND_INFO.width, GAS_BACKGROUND_INFO.height);
	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->addRenderComponent(backgroundSprite_);

	//Weapons backgrounds
	bckPistolSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckPistol_ = new Container();

	bckPistol_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckPistol_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckPistol_->addRenderComponent(bckPistolSprite_);
	bckPistol_->setPosition(FIRST_WEAPON_BCK);

	bckShotgunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckShotgun_ = new Container();

	bckShotgun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckShotgun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckShotgun_->addRenderComponent(bckShotgunSprite_);
	bckShotgun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 125));

	bckRifleSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckRifle_ = new Container();

	bckRifle_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckRifle_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckRifle_->addRenderComponent(bckRifleSprite_);
	bckRifle_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 250));

	bckMachinegunSprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, WEAPONS_BACKGROUNDS_W, WEAPONS_BACKGROUNDS_H);
	bckMachinegun_ = new Container();

	bckMachinegun_->setWidth(WEAPONS_BACKGROUNDS_W);
	bckMachinegun_->setHeight(WEAPONS_BACKGROUNDS_H);
	bckMachinegun_->addRenderComponent(bckMachinegunSprite_);
	bckMachinegun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x, FIRST_WEAPON_BCK.y + 375));

	//Inventory backgrounds
	weapon1Sprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, INV_W, INV_H);
	weapon1_ = new Container();

	weapon1_->setWidth(INV_W);
	weapon1_->setHeight(INV_H);
	weapon1_->addRenderComponent(weapon1Sprite_);
	weapon1_->setPosition(INV1_POSITION);
	
	weapon2Sprite_ = new Sprite(BLACK_BACKGROUND_INFO.idlePath, INV_W, INV_H);
	weapon2_ = new Container();

	weapon2_->setWidth(INV_W);
	weapon2_->setHeight(INV_H);
	weapon2_->addRenderComponent(weapon2Sprite_);
	weapon2_->setPosition(INV2_POSITION);

}

void ShopState::setButtonComponents()
{
	//Create Sprite
	backSprite_ = new Sprite(BACK_BUTTON_INFO.idlePath, BACK_BUTTON_INFO.width, BACK_BUTTON_INFO.height, BACK_BUTTON_POSITION.x, BACK_BUTTON_POSITION.y);
	weapon1ButtonSprite_ = new Sprite(BUY_BUTTON_PATH, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon2ButtonSprite_ = new Sprite(BUY_BUTTON_PATH, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon3ButtonSprite_ = new Sprite(BUY_BUTTON_PATH, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);
	weapon4ButtonSprite_ = new Sprite(BUY_BUTTON_PATH, WEAPON_BUTTON_W, WEAPON_BUTTON_H, 0, 0);

	//Add rendercomponent
	buttons_["backButton"]->addRenderComponent(backSprite_);
	buttons_["weapon1Button"]->addRenderComponent(weapon1ButtonSprite_);
	buttons_["weapon2Button"]->addRenderComponent(weapon2ButtonSprite_);
	buttons_["weapon3Button"]->addRenderComponent(weapon3ButtonSprite_);
	buttons_["weapon4Button"]->addRenderComponent(weapon4ButtonSprite_);

}

void ShopState::startTexts()
{
	//Armory
	armory_ = new Container();
	armoryText_ = new Text(new Font(FONT_COOLFONT, 50), "Armory", SDL_Color({ 255, 255, 255 }));
	armoryText_->setCamera(UI_CAMERA);
	armory_->setWidth(armoryText_->getFont()->getSize()*armoryText_->getText().length());
	armory_->setHeight(armoryText_->getFont()->getSize());
	armory_->setPosition(ARMORY_TEXT_POSITION);
	armory_->addRenderComponent(armoryText_);

	//Inventory
	inventory_ = new Container();
	inventoryText_ = new Text(new Font(FONT_COOLFONT, 50), "Inventory", SDL_Color({ 255, 255, 255 }));
	inventoryText_->setCamera(UI_CAMERA);
	inventory_->setWidth(inventoryText_->getFont()->getSize()*inventoryText_->getText().length());
	inventory_->setHeight(inventoryText_->getFont()->getSize());
	inventory_->setPosition(INVENTORY_TEXT_POSITION);
	inventory_->addRenderComponent(inventoryText_);

	//Weapon names
	pistolT_ = new Container();
	pistolText_ = new Text(new Font(FONT_LATO, 30), "Pistol - Owned" , SDL_Color({ 255, 255, 255 }));
	pistolText_->setCamera(UI_CAMERA);
	pistolT_->setWidth(pistolText_->getFont()->getSize()*pistolText_->getText().length() / 2);
	pistolT_->setHeight(pistolText_->getFont()->getSize());
	pistolT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - pistolText_->getFont()->getSize()/2 ));
	pistolT_->addRenderComponent(pistolText_);

	shotgunT_ = new Container();
	shotgunText_ = new Text(new Font(FONT_LATO, 30), "Shotgun - " + SHOTGUN_PRICE, SDL_Color({ 255, 255, 255 }));
	shotgunText_->setCamera(UI_CAMERA);
	shotgunT_->setWidth(shotgunText_->getFont()->getSize()*shotgunText_->getText().length() / 2);
	shotgunT_->setHeight(shotgunText_->getFont()->getSize());
	shotgunT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, 125 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - shotgunText_->getFont()->getSize() / 2));
	shotgunT_->addRenderComponent(shotgunText_);

	rifleT_ = new Container();
	rifleText_ = new Text(new Font(FONT_LATO, 30), "Sniper - " + RIFLE_PRICE, SDL_Color({ 255, 255, 255 }));
	rifleText_->setCamera(UI_CAMERA);
	rifleT_->setWidth(rifleText_->getFont()->getSize()*rifleText_->getText().length() / 2);
	rifleT_->setHeight(rifleText_->getFont()->getSize());
	rifleT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2, 250 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - rifleText_->getFont()->getSize() / 2));
	rifleT_->addRenderComponent(rifleText_);

	machinegunT_ = new Container();
	machinegunText_ = new Text(new Font(FONT_LATO, 28), "Machinegun - " + MACHINEGUN_PRICE, SDL_Color({ 255, 255, 255 }));
	machinegunText_->setCamera(UI_CAMERA);
	machinegunT_->setWidth(machinegunText_->getFont()->getSize()*machinegunText_->getText().length() / 1.8);
	machinegunT_->setHeight(machinegunText_->getFont()->getSize());
	machinegunT_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W / 2 - 35, 375 + FIRST_WEAPON_BCK.y + WEAPONS_BACKGROUNDS_H / 2 - machinegunText_->getFont()->getSize() / 2));
	machinegunT_->addRenderComponent(machinegunText_);
}

void ShopState::startIcons()
{
	//Weapon Icons
	pistolSprite_ = new Sprite(GUN.idlePath, ICON_W, ICON_H);
	pistol_ = new Container();

	pistol_->setWidth(ICON_W);
	pistol_->setHeight(ICON_H * 1.65);
	pistol_->addRenderComponent(pistolSprite_);
	pistol_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y - (ICON_H / 3.5)));
	pistol_->setRotation(90);

	shotgunSprite_ = new Sprite(SHOTGUN.idlePath, ICON_W, ICON_H);
	shotgun_ = new Container();

	shotgun_->setWidth(ICON_W * 0.8);
	shotgun_->setHeight(ICON_H * 2.6 * 0.8);
	shotgun_->addRenderComponent(shotgunSprite_);
	shotgun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y + 125 - shotgun_->getHeight() / 3.6));
	shotgun_->setRotation(90);

	rifleSprite_ = new Sprite(SNIPER.idlePath, ICON_W, ICON_H);
	rifle_ = new Container();

	rifle_->setWidth(ICON_W * 0.4);
	rifle_->setHeight(ICON_H * 6 * 0.4);
	rifle_->addRenderComponent(rifleSprite_);
	rifle_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.15, FIRST_WEAPON_BCK.y + 250 - rifle_->getHeight() / 3.5));
	rifle_->setRotation(90);

	machinegunSprite_ = new Sprite(MACHINEGUN.idlePath, ICON_W, ICON_H);
	machinegun_ = new Container();

	machinegun_->setWidth(ICON_W);
	machinegun_->setHeight(ICON_H * 1.8);
	machinegun_->addRenderComponent(machinegunSprite_);
	machinegun_->setPosition(Vector2D(FIRST_WEAPON_BCK.x + WEAPONS_BACKGROUNDS_W * 0.10, FIRST_WEAPON_BCK.y + 375 - machinegun_->getHeight() / 3.7));
	machinegun_->setRotation(90);

	//Weapons in inventory
	pistolI_ = new Container(*pistol_);
	pistolI_->setPosition(Vector2D(INV1_POSITION.x + (INV_W - pistolI_->getWidth())/2 ,INV1_POSITION.y + (INV_H - pistolI_->getHeight()) / 2));
	shotgunI_ = new Container(*shotgun_);
	shotgunI_->setActive(false);
	rifleI_ = new Container(*rifle_);
	rifleI_->setActive(false);
	machinegunI_ = new Container(*machinegun_);
	machinegunI_->setActive(false);
	//Add to array
	inventoryWeapons_[0] = pistolI_;
	inventoryWeapons_[1] = shotgunI_;
	inventoryWeapons_[2] = rifleI_;
	inventoryWeapons_[3] = machinegunI_;


	//Owned Icons (Equip)
	weapon1OwnedS_ = new Sprite(EQUIP_BUTTON_PATH, buttons_["weapon1Button"]->getWidth(), buttons_["weapon1Button"]->getHeight());
	weapon1Owned_ = new Container();

	weapon1Owned_->setWidth(buttons_["weapon1Button"]->getWidth());
	weapon1Owned_->setHeight(buttons_["weapon1Button"]->getHeight());
	weapon1Owned_->addRenderComponent(weapon1OwnedS_);
	weapon1Owned_->setPosition(buttons_["weapon1Button"]->getPosition());
	weapon1Owned_->setActive(true);

	weapon2OwnedS_ = new Sprite(EQUIP_BUTTON_PATH, buttons_["weapon2Button"]->getWidth(), buttons_["weapon2Button"]->getHeight());
	weapon2Owned_ = new Container();

	weapon2Owned_->setWidth(buttons_["weapon2Button"]->getWidth());
	weapon2Owned_->setHeight(buttons_["weapon2Button"]->getHeight());
	weapon2Owned_->addRenderComponent(weapon2OwnedS_);
	weapon2Owned_->setPosition(buttons_["weapon2Button"]->getPosition());
	weapon2Owned_->setActive(false);

	weapon3OwnedS_ = new Sprite(EQUIP_BUTTON_PATH, buttons_["weapon3Button"]->getWidth(), buttons_["weapon3Button"]->getHeight());
	weapon3Owned_ = new Container();

	weapon3Owned_->setWidth(buttons_["weapon3Button"]->getWidth());
	weapon3Owned_->setHeight(buttons_["weapon3Button"]->getHeight());
	weapon3Owned_->addRenderComponent(weapon3OwnedS_);
	weapon3Owned_->setPosition(buttons_["weapon3Button"]->getPosition());
	weapon3Owned_->setActive(false);

	weapon4OwnedS_ = new Sprite(EQUIP_BUTTON_PATH, buttons_["weapon4Button"]->getWidth(), buttons_["weapon4Button"]->getHeight());
	weapon4Owned_ = new Container();

	weapon4Owned_->setWidth(buttons_["weapon4Button"]->getWidth());
	weapon4Owned_->setHeight(buttons_["weapon4Button"]->getHeight());
	weapon4Owned_->addRenderComponent(weapon4OwnedS_);
	weapon4Owned_->setPosition(buttons_["weapon4Button"]->getPosition());
	weapon4Owned_->setActive(false);
}

void ShopState::selected(int weapon)
{
	if (weapon == 1) 
		if (!owned_[weapon] && Money::getInstance()->getCurrentMoney() >= SHOTGUN_PRICE_INT)
		{
			Money::getInstance()->addMoney(-SHOTGUN_PRICE_INT);
			owned_[weapon] = true;
			weapon2Owned_->setActive(true);
			shotgunText_->setText("Shotgun - Owned");
		}

	if (weapon == 2)
		if (!owned_[weapon] && Money::getInstance()->getCurrentMoney() >= RIFLE_PRICE_INT)
		{
			Money::getInstance()->addMoney(-RIFLE_PRICE_INT);
			owned_[weapon] = true;
			weapon3Owned_->setActive(true);
			rifleText_->setText("Sniper - Owned");

		}
	if (weapon == 3)
		if (!owned_[weapon] && Money::getInstance()->getCurrentMoney() >= MACHINEGUN_PRICE_INT)
		{
				Money::getInstance()->addMoney(-MACHINEGUN_PRICE_INT);
				owned_[weapon] = true;
				weapon4Owned_->setActive(true);
				machinegunText_->setText("Machinegun - Owned");
		}
	if (owned_[weapon]) 
	{
		if (equipped_[0] != -1)
			inventoryWeapons_[equipped_[0]]->setActive(false);
		if (equipped_[1] != -1)
			inventoryWeapons_[equipped_[1]]->setActive(false);

		if (equipped_[0] != weapon && equipped_[1] != weapon)
		{
			equipped_[1] = equipped_[0];
			equipped_[0] = weapon;

		}

		if (equipped_[1] != -1)
		{
			if (!inventoryWeapons_[equipped_[1]]->isActive())
				inventoryWeapons_[equipped_[1]]->setActive(true);
			inventoryWeapons_[equipped_[1]]->setPosition(Vector2D(INV2_POSITION.x + (INV_W - pistolI_->getWidth()) / 2, INV2_POSITION.y + (INV_H - pistolI_->getHeight()) / 2));
			if (equipped_[1] != equipped_[0] && equipped_[0] != -1)
				equip(equipped_[1]);
		}

		if (equipped_[0] != -1)
		{
			if (!inventoryWeapons_[equipped_[0]]->isActive())
				inventoryWeapons_[equipped_[0]]->setActive(true);
			inventoryWeapons_[equipped_[0]]->setPosition(Vector2D(INV1_POSITION.x + (INV_W - pistolI_->getWidth()) / 2, INV1_POSITION.y + (INV_H - pistolI_->getHeight()) / 2));
			if (equipped_[1] != equipped_[0] && equipped_[1] != -1)
				equip(equipped_[0]);
		}
	}
		
	updateState();
}

void ShopState::equip(int turret)
{
	switch (turret)
	{
	case 0:
		Vehicle::getInstance()->EquipTurret(new Turret(GUN));
		break;
	case 1:
		Vehicle::getInstance()->EquipTurret(new Turret(SHOTGUN));
		break;
	case 2:
		Vehicle::getInstance()->EquipTurret(new Turret(SNIPER));
		break;
	case 3:
		Vehicle::getInstance()->EquipTurret(new Turret(MACHINEGUN));
		break;
	default:
		break;
	}
}

