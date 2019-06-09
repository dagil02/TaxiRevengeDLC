#include "FuelUpgrade.h"

FuelUpgrade::FuelUpgrade(int w, int h, int x, int y) : Trigger(w, h, x, y)
{
	sprite_ = new Animation();
	sprite_->loadAnimation("../Assets/sprites/fuelupgrade.png", "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);
}


FuelUpgrade::~FuelUpgrade()
{
	delete sprite_; sprite_ = nullptr;
}

void FuelUpgrade::beginCallback(b2Contact * contact)
{
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
		&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		Vehicle::getInstance()->getHealthComponent()->increaseMaxHealth();
		active_ = false;
	}
}

void FuelUpgrade::endCallback(b2Contact * contact)
{
}
