#pragma once
#include "Container.h"
#include "Animation.h"
#include "PhysicObject.h"
#include "Trigger.h"

class ImpactComponent;

class Proyectile : public Trigger {
public:
	Proyectile();
	virtual ~Proyectile();

	virtual void SetBirth(double birthTime);
	virtual void update(Uint32 time);
	virtual void render(Uint32 time);
	virtual void ChangeBulletType(ProyectileInfo p, bool isAnEnemy);
	virtual void beginCallback(b2Contact *contact) override;
	virtual void endCallback(b2Contact *contact) override;
	PhysicObject* GetPhyO();
	double GetDamage();
	double GetSpeed();
	void DeactivateBullet();
	bool isAnEnemy();

protected:
	Animation* animC_=nullptr;
	ImpactComponent* impC_=nullptr;
	double damage_;
	double lifeTime_;//tiempo de vida hasta volver a desactivarse
	double birthTime_;//tiempo en el que se activo el objeto
	double speed_;
	bool bodyReadyToDestroy_;
	bool zombie_;
	bool isAnEnemy_;


	static b2Filter colFilter;
};

