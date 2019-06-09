#pragma once
#include "GameObject.h"

#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include <vector>

class EnemyPool :public GameObject
{
public:
	EnemyPool(EnemyPool&) = delete;
	EnemyPool& operator=(const EnemyPool&) = delete;

	static EnemyPool* GetInstance() {
		if (instance_ == nullptr) {
			instance_ = new EnemyPool();
		}
		return instance_;
	}

	inline static void destroyInstance() {
		delete instance_; instance_ = nullptr;
	}

	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual Enemy* addEnemy(Vector2D pos, Vector2D vel, ProyectileInfo prType);
	virtual ~EnemyPool();
private:
	EnemyPool();
	static const int MAXENEMIES = 100;
	Enemy enemies_[MAXENEMIES];
	Enemy* getUnusedEnemy();
	static EnemyPool* instance_;
};
