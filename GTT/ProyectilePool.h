#pragma once
#include "GameObject.h"
#include "Proyectile.h"
#include <vector>

class ProyectilePool :public GameObject
{
	static const int MAXPROYECTILES = 100;

	ProyectilePool(ProyectilePool&) = delete;
	ProyectilePool& operator=(const ProyectilePool&) = delete;

	static unique_ptr<ProyectilePool> instance_; //ptr instance class


public:
	//builder
	ProyectilePool();
	virtual ~ProyectilePool();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new ProyectilePool());
		}
	}
	//get singleton class
	inline static ProyectilePool* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void handleInput(Uint32 time, const SDL_Event& event) {};
	virtual Proyectile* addProyectile(Vector2D pos, Vector2D vel, float angle, ProyectileInfo prType, bool isAnEnemy);

	

private:	
	Proyectile proyectiles_[MAXPROYECTILES];
	Proyectile* getUnusedProyectile();

};

