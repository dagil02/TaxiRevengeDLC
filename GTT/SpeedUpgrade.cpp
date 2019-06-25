#include "SpeedUpgrade.h"

SpeedUpgrade::SpeedUpgrade(int w, int h, int x, int y) : Trigger(w, h, x, y)
{
	sprite_ = new Animation();
	sprite_->loadAnimation("../Assets/sprites/fuelupgrade.png", "idle");
	sprite_->playAnimation("idle");
	this->addRenderComponent(sprite_);
}


SpeedUpgrade::~SpeedUpgrade()
{
	delete sprite_; sprite_ = nullptr;
}

void SpeedUpgrade::beginCallback(b2Contact * contact)
{
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();
	Vehicle* taxiTurret = Vehicle::getInstance();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
		&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		taxiTurret->SpeedBost();
		active_ = false;
	}
}

void SpeedUpgrade::endCallback(b2Contact * contact)
{
}
