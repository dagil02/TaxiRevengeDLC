#pragma once

#include <list>
#include <SDL.h>
#include "GameObject.h"

class GameState
{

protected:
	list<GameObject*> stage_;

public:

	GameState(){}
	virtual ~GameState(){
		stage_.clear();
	}

	virtual void start() = 0;
	virtual void end() = 0;
	virtual void updateState() {};

	virtual void update(Uint32 deltaTime) { for (GameObject* o : stage_) o->update(deltaTime); }

	virtual void handleEvents(Uint32 deltaTime, SDL_Event& event) {
		bool e = false; //variable de control
		if (!stage_.empty()) {
			auto it = stage_.begin();
			//se recorre la lista, se comunica con la función correspondiente, si hay evento rompe el ciclo actual.
			while (it != stage_.end()) {
				(*it)->handleInput(deltaTime, event);
				it++;
			}
		}
	}
	virtual void render(Uint32 deltaTime) const { for (GameObject* o : stage_) o->render(deltaTime); }


	void addGameObject(GameObject *gameObject) {
		stage_.push_back(gameObject);
	};
};

