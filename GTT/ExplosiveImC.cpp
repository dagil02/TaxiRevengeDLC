#include "ExplosiveImC.h"
#include "Vehicle.h"

ExplosiveImC::ExplosiveImC(Proyectile* o, int radius):ImpactComponent(o)
{
	radius_ = radius;
}

void ExplosiveImC::Impact(b2Contact * contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();
		b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

		if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() != taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() != taxiBody)) {
			/*
			playSound(explosion);
			playAnimation(explosion);
			for(auto e: activeEnemies){
				if(e.pos.x+e.width>=o.pos.x-radius && e.pos.x<=o.pos.x+radius){
					if(e.pos.y+height>=o.pos.y-radius && e.pos.y<=o.pos.y + radius){
						e.damage(o.damage);
					}
				}
			}
			*/
			o_->setActive(false);
		}
	}
}

ExplosiveImC::~ExplosiveImC()
{
}
