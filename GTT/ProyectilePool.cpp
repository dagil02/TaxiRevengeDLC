#include "ProyectilePool.h"


unique_ptr<ProyectilePool> ProyectilePool::instance_ = nullptr;

ProyectilePool::ProyectilePool()
{
	
}

ProyectilePool::~ProyectilePool() {

}


Proyectile * ProyectilePool::getUnusedProyectile()
{
	for (auto& proyectile : proyectiles_) {
		if (!proyectile.isActive()) {
			return &proyectile;
		}
	}
	return nullptr;
}

void ProyectilePool::update(Uint32 time) {
	for (auto& proyectile : proyectiles_) {
		if (proyectile.isActive()) {
			proyectile.update(time);
		}
	}
}

void ProyectilePool::render(Uint32 time) {
	for (auto& proyectile : proyectiles_)
	{
		if (proyectile.isActive()) {
			proyectile.render(time);
		}
	}
}

Proyectile * ProyectilePool::addProyectile(Vector2D pos, Vector2D vel, float angle, ProyectileInfo prType,  bool isAnEnemy)
{
	Proyectile* e;
	e = getUnusedProyectile();
	if (e != nullptr) {
		e->ChangeBulletType(prType, isAnEnemy);
		e->GetPhyO()->getBody()->SetTransform(Vector2D(pos.x*PHYSICS_SCALING_FACTOR, pos.y*PHYSICS_SCALING_FACTOR), angle);
		e->GetPhyO()->getBody()->SetLinearVelocity(Vector2D(vel.x * e->GetSpeed(), vel.y* e->GetSpeed()));
		e->SetBirth(SDL_GetTicks());
		e->setActive(true);
	}
	return e;
}



