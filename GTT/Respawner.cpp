#include "Respawner.h"

Respawner::Respawner(Health *healthToObserve) {
	healthToObserve->registerObserver(this);
	registerObserver(healthToObserve);
}


Respawner::~Respawner() {
	for (auto respawnPoint : respawnPoints_) {
		delete respawnPoint.second;
	}
	respawnPoints_.clear();
}

void Respawner::update(GameObject * o, Uint32 deltaTime) {
	if (respawnReady_ && currentRespawnPoint_ != ""
		&& hasRespawnPoint(currentRespawnPoint_)) {

		o->setPosition(respawnPoints_[currentRespawnPoint_]->getPosition(), true);
		respawnReady_ = false;

		Event e(this, RESPAWNED);
		broadcastEvent(e);
	}
}

void Respawner::respawn(GameObject* respawnPoint) {
	respawnReady_ = true;
}

void Respawner::setCurrentRespawn(string name) {
	if (!respawnPoints_.empty())
		currentRespawnPoint_ = name != "" ? name : searchNearestRespawn();
}

string Respawner::getCurrentRespawnPoint() {
	return currentRespawnPoint_;
}

void Respawner::addRespawnPoint(GameObject * respawnPoint, string name) {
	// If this is the first respawn added, set it as the current
	// respawn point
	if (respawnPoints_.size() == 0) currentRespawnPoint_ = name;

	respawnPoints_[name] = respawnPoint;
}

bool Respawner::deleteRespawnPoint(string name, bool callDestructor) {
	map<string, GameObject*>::iterator it = respawnPoints_.find(name);
	if (it != respawnPoints_.end()) {
		if (callDestructor)
			delete (*it).second;
		respawnPoints_.erase(it);

		return true;
	}

	return false;
}

bool Respawner::hasRespawnPoint(string name) {
	return respawnPoints_.find(name) != respawnPoints_.end();
}

GameObject * Respawner::getRespawnPoint(string name) {
	if (respawnPoints_.find(name) != respawnPoints_.end())
		return respawnPoints_[name];
	else
		return nullptr;
}

bool Respawner::receiveEvent(Event& e) {
	if (e.type_ == HEALTH_CHANGED) {
		HealthChangedEvent* healthEvent = static_cast<HealthChangedEvent*>(&e);

		if (healthEvent->currentHealth_ <= 0) {
			respawn();
		}
	}

	return true;
}

string Respawner::searchNearestRespawn() {
	string closestGameObject = "";

	for (auto respawnPoint:respawnPoints_) {
		if (closestGameObject == "" || respawnPoint.second->getPosition().Length() < respawnPoints_[closestGameObject]->getPosition().Length())

			closestGameObject = respawnPoint.first;
	}

	return closestGameObject;
}
