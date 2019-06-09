#pragma once
#include "Car.h"
#include "Trigger.h"
#include "NodeMap.h"
#include "IApatrol.h"
#include "IAFollow.h"

class Turret;

class Enemy :public Car
{
public:
	Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos, WeaponInfo weapon);
	virtual void Damage(double damage);
	virtual void Die();
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);
	virtual int getDistanceFromTaxi();
	virtual Turret* getTurret();
	virtual bool taxiOnRange();
	IAMovementBehaviour* getIABehaviour();
	bool isFollowing() {
		return followmode_;
	};
	virtual ~Enemy();
private:
	bool bodyReadyToDestroy_;
	bool followmode_;

	//zombie y alive gestionan la animáción previa a la destruccióin del GO. 
	bool alive_;
	bool zombie_;

	IAMovementBehaviour* patrol_;
	IAMovementBehaviour* follow_;
	NodeMap* routemap_;
	int speed_;
	int pursuitRange_;
	Turret* turret_;
	int reward_;
};

