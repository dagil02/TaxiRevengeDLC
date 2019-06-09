#pragma once
#include "LogicComponent.h"
#include "Observer.h"

// AKA: GASOLINA
class Health :	public LogicComponent,
				public Observable,
				public Observer {
public:
	Health(int maxHealth);
	virtual ~Health();

	virtual void update(GameObject* o, Uint32 deltaTime) override;

	int getHealth();
	int getMaxHealth();
	void damage(int damage);
	void heal(int heal);
	void setDamageOverTime(int damage, int frequency);

	// Sets the current health to the maximum health
	void resetHealth();

	// Are you sure you want to use this instead
	// 'heal()' or 'damage()'?
	void setHealth(int health);

	void increaseMaxHealth();

	virtual bool receiveEvent(Event &e) override;

private:
	int maxHealth_;
	int health_;

	// Damage over time attributes (all in ms)
	int damageOverTimeValue_ = 0;
	Uint32 damageFrequency_ = 0;
	Uint32 damageTimer_ = 0;

	void damageOverTime(Uint32 deltaTime);
};

