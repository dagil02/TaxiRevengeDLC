#pragma once
#include "Container.h"
class GameManager :
	public Container
{
	GameManager(GameManager &) = delete;
	GameManager & operator=(const GameManager &) = delete;

	static unique_ptr<GameManager> instance_; //ptr instance class
public:
	GameManager();
	virtual ~GameManager();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new GameManager());
		}
	}
	//get singleton class
	inline static GameManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		if (instance_ == nullptr)
			initInstance();
		return instance_.get();
	}
	virtual void update(Uint32 deltaTime);

	void addHit() { hits++; };
	void addKill() { kills++; if (kills == 4) calculatePuntuation();};
	void calculatePuntuation();
	void setEnemyCount(int enemies) { enemyCount = enemies; };
	void decreaseEnemyCount() { enemyCount--; };
	int getEnemyCount() { return enemyCount; };

private:
	int hits = 0;
	int kills = 0;
	int initTime = 0;
	int time = 0;
	int enemyCount = 0;


};

