#include "DamageUpgrade.h"



DamageUpgrade::DamageUpgrade(int w, int h, int x, int y) : Trigger(w, h, x, y)
{
	sprite_ = new Animation();
	sprite_->loadAnimation("../Assets/sprites/fuelupgrade.png", "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);
}


DamageUpgrade::~DamageUpgrade()
{
	delete sprite_; sprite_ = nullptr;
}

void DamageUpgrade::beginCallback(b2Contact * contact)
{
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();
	Vehicle* taxiTurret = Vehicle::getInstance();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
		&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		taxiTurret->DamageBost();
		active_ = false;
	}
}

void DamageUpgrade::endCallback(b2Contact * contact)
{
}