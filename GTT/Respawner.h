#pragma once
#include "LogicComponent.h"
#include "Health.h"
#include "GameObject.h"
#include "Observer.h"

class Respawner : public LogicComponent,
	public Observer,
	public Observable {
public:
	// Pass the health component this respawn
	// will observe
	Respawner(Health* healthToObserve);
	virtual ~Respawner();

	virtual void update(GameObject *o, Uint32 deltaTime) override;

	// Respawn the GameObject this component is attached to.
	// Uses the nearest respawnPoint (if there's any) if none
	// is provided
	void respawn(GameObject* respawnPoint = nullptr);

	// Sets the respawn point that will be used
	// when 'respawn()' is called. You must first
	// add the respawn point with 'addRespawnPoint'
	// If no name is provided, the nearest respawn
	// point will be picked
	void setCurrentRespawn(string name = "");
	string getCurrentRespawnPoint();

	void addRespawnPoint(GameObject* respawnPoint, string name);
	bool deleteRespawnPoint(string name, bool callDestructor = true);
	bool hasRespawnPoint(string name);
	GameObject* getRespawnPoint(string name);

	virtual bool receiveEvent(Event &e) override;

private:
	map<string, GameObject*> respawnPoints_;
	string currentRespawnPoint_ = "";
	bool respawnReady_ = false;

	string searchNearestRespawn();
};

