#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
#include "HealthDisplay.h"
#include "MoneyDisplay.h"


class ShopState : public GameState, public Observer, public Observable {
public:
	ShopState();
	virtual ~ShopState();

	virtual void start() override;
	virtual void end() override;

	virtual void update(Uint32 deltaTime) override;
	virtual void updateState();
	virtual bool receiveEvent(Event& e);

private:

		//Weapons Info (gun 1, shotgun 2, sniper 3, machinegun 4)
	bool owned_ [4] = {true, false, false, false};
	int equipped_[2] = { 0, -1 };
	Container* inventoryWeapons_ [4];
		//Buttons
	map<string, Button*> buttons_;
	Sprite *weapon1ButtonSprite_, *weapon2ButtonSprite_, *weapon3ButtonSprite_, *weapon4ButtonSprite_;
	
	Container *weapon1Owned_, *weapon2Owned_, *weapon3Owned_, *weapon4Owned_;
	Sprite *weapon1OwnedS_, *weapon2OwnedS_, *weapon3OwnedS_, *weapon4OwnedS_;
		//Backgrounds
	Container *background_, *bckPistol_, *bckShotgun_, *bckRifle_, *bckMachinegun_, *weapon1_, *weapon2_;
	Sprite *backSprite_, *backgroundSprite_, *bckPistolSprite_, *bckShotgunSprite_, *bckRifleSprite_, *bckMachinegunSprite_, *weapon1Sprite_, *weapon2Sprite_;
	
		//Texts
	Container *armory_, *inventory_, *pistolT_, *shotgunT_, *rifleT_, *machinegunT_;
	Text *armoryText_, *inventoryText_, *shotgunText_, *pistolText_, *rifleText_, *machinegunText_;

		//Icons
	Container *pistol_, *shotgun_, *rifle_, *machinegun_;
	Sprite *pistolSprite_, *shotgunSprite_, *rifleSprite_, *machinegunSprite_;

		//Weapons in inventory
	Container *pistolI_, *shotgunI_, *rifleI_, *machinegunI_;

		//Money Display
	MoneyDisplay *moneyDisplay_;

	void setButtons();
	void setBackground();
	void setButtonComponents();
	void startTexts();
	void startIcons();
	void selected(int weapon);
	void equip(int turret);
};

