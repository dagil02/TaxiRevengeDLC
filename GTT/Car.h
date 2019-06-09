#pragma once
#include "Container.h"
#include "Observable.h"
#include "Observer.h"
#include "PhysicObject.h"
#include <Box2D/Box2D.h>
#include "Animation.h"

#include <vector>
#include "Health.h"
#include <cmath> 

class AimComponent;

class Car :
	public Container, public Observable, public Observer
{
public:
	Car();
	virtual ~Car();

	//get
	PhysicObject* GetPhyO();
	float32 GetMaxSpeed();
	float32 GetTurnSpeed();
	virtual AimComponent* GetAimComponent();
	Health* getHealthComponent();
	virtual void setPosition(const Vector2D &pos, bool force = false) override;

	virtual bool receiveEvent(Event& e) { return false; };

protected:
	float32 maxSpeed_;
	float32 turnSpeed_;
	PhysicObject* phyO_;
	Animation* sprite_;
	AimComponent* aimC_;//forma de apuntar con la torreta (depende de si es Jugador o IA)
	Health* health_;
};

