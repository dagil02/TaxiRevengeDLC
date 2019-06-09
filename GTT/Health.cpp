#include "Health.h"

Health::Health(int maxHealth) {
	maxHealth_ = maxHealth;
	health_ = maxHealth;
}

Health::~Health() {

}

void Health::update(GameObject * o, Uint32 deltaTime) {
	damageOverTime(deltaTime);
}

int Health::getHealth() {
	return health_;
}

int Health::getMaxHealth() {
	return maxHealth_;
}

void Health::damage(int damage) {
	int finalHealth = health_ - damage;
	
	if (finalHealth < 0)
		finalHealth = 0;

	setHealth(finalHealth);
}

void Health::heal(int heal) {
	int finalHealth = health_ + heal;
	
	if (finalHealth > maxHealth_)
		finalHealth = maxHealth_;

	setHealth(finalHealth);
}

void Health::setDamageOverTime(int damage, int frequency) {
	damageOverTimeValue_ = damage;
	damageFrequency_ = frequency;
}

void Health::resetHealth() {
	setHealth(maxHealth_);
}

void Health::setHealth(int health) {
	// Send an event about the health change
	HealthChangedEvent e(this, health, health_, maxHealth_);
	broadcastEvent(e);

	health_ = health;
}

void Health::increaseMaxHealth()
{
	maxHealth_ += HP_INCREASE;
}

bool Health::receiveEvent(Event& e) {
	if (e.type_ == RESPAWNED)
		resetHealth();

	return true;
}

void Health::damageOverTime(Uint32 deltaTime) {
	if (damageFrequency_ <= 0 && damageOverTimeValue_ == 0)
		return;

	damageTimer_ += deltaTime;
	while (damageTimer_ >= damageFrequency_) {
		damage(damageOverTimeValue_);
		damageTimer_ -= damageFrequency_;
	}
}
