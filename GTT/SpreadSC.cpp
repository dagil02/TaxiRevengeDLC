#include "SpreadSC.h"


SpreadSC::SpreadSC(Turret * turret, double dispersionAngle, int numPellets) :ShootComponent(turret)
{
	dispersionAngle_ = dispersionAngle;
	numPellets_ = numPellets;
}

void SpreadSC::shoot(ProyectileInfo prType, bool isAnEnemy)
{
	double ang = turret_->getRotation() / 180.0 * M_PI - (dispersionAngle_ / 180.0*M_PI / 2);

	Vector2D spawndir (sin(turret_->getRotation() / 180.0*M_PI)*100, -cos(turret_->getRotation() / 180.0*M_PI)*100);
	Vector2D spawnpoint = Vector2D(turret_->getCenter().x + spawndir.x*0.25 , turret_->getCenter().y + spawndir.y*0.25);

	ProyectilePool::getInstance()->addProyectile(spawnpoint,
		Vector2D(sin(ang), -cos(ang)), turret_->getRotation()/180.0*M_PI, prType, isAnEnemy);

	double incrang = dispersionAngle_ / 180.0*M_PI / (numPellets_-1);
	ang += incrang;
	
	for (int i = 1; i < numPellets_; i++) {
		ProyectilePool::getInstance()->addProyectile(spawnpoint,
			Vector2D((sin(ang)), (-cos(ang))), turret_->getRotation()/180.0*M_PI, prType, isAnEnemy);
		ang += incrang;
	}
}

void SpreadSC::changeProperties(double prop1, int prop2)
{
	dispersionAngle_ = prop1;
	numPellets_ = prop2;
}
