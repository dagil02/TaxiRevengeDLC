#pragma once
#include "HealthDisplay.h"
#include "CameraType.h"
#include "Observer.h"
#include "MoneyDisplay.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"
#include "DialoguesManager.h"
#include "EnemyCountDisplay.h"
#include "Animation.h"
#include "PauseMenu.h"

class UI : public Container, public Observer {
public:
	static UI* getInstance();

	inline static void destroyInstance() {
		delete singleton_;
		singleton_ = nullptr;
	}

	virtual void render(Uint32 deltaTime) override;
	virtual void update(Uint32 deltaTime) override;
	virtual void addUIElement(Container* c);

	virtual bool receiveEvent(Event& e) override;

	void setAmmoActive(bool active) const;

	void getEvents(Uint32 deltaTime, const SDL_Event & event);
	

private:
	static UI* singleton_;

	UI();
	virtual ~UI();

	vector<GameObject*> UIElements_;

	HealthDisplay* healthDisplay_;
	MoneyDisplay* moneyDisplay_;
	ReloadingDisplay* reloadDisplay_;
	AmmoDisplay* ammoDisplay_;
	DialoguesManager* dialogues_;
	EnemyCountDisplay* enemyCount_;

	Font* font_;
	SDL_Color fontColor_;

	//pausa
	PauseMenu* pauseMenu_;
};

