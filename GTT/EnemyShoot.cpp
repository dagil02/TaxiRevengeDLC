#include "EnemyShoot.h"
#include "Enemy.h"
#include "Turret.h"


EnemyShoot::EnemyShoot()
{
}

void EnemyShoot::update(GameObject* o, Uint32 deltaTime)
{
	Enemy* e = dynamic_cast<Enemy*>(o);
	if (e != nullptr) {
		int i = 0;

		if (e->taxiOnRange()) {
			e->getTurret()->AIShoot();
		}
	}
}


EnemyShoot::~EnemyShoot()
{
}
