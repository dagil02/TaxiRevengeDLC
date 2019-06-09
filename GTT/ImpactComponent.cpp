#include "ImpactComponent.h"
#include "Vehicle.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "GameManager.h"



ImpactComponent::ImpactComponent(Proyectile * o)
{
	o_ = o;
}

void ImpactComponent::Impact(b2Contact * contact)
{
	if (o_->getPhysicsObject() != nullptr) {
		b2Body* body = o_->getPhysicsObject()->getBody();

		if (contact->GetFixtureA()->GetBody() == body || contact->GetFixtureB()->GetBody() == body) {
			Enemy* e = (Enemy*)contact->GetFixtureA()->GetBody()->GetUserData();
			if(e==nullptr)
				e = (Enemy*)contact->GetFixtureB()->GetBody()->GetUserData();
			o_;
			if (e != nullptr && !o_->isAnEnemy()) {
				e->Damage(o_->GetDamage());
				SoundManager::getInstance()->playSound_Ch(0, ENEMY_HIT_DAMAGE, 0); //channel 0, because not interrupt other sounds
			} else
				if (o_->isAnEnemy() && (contact->GetFixtureA()->GetBody() == Vehicle::getInstance()->GetPhyO()->getBody()
					|| contact->GetFixtureB()->GetBody() == Vehicle::getInstance()->GetPhyO()->getBody())) {
					Vehicle::getInstance()->getHealthComponent()->damage(o_->GetDamage());

					//check taxi is registered who observer
					int i; //i take index observer vector value
					if (!o_->isRegistered(Vehicle::getInstance(), i)) { o_->registerObserver(Vehicle::getInstance()); }
					Event eV(o_, IMPACT_DAMAGE);
					o_->broadcastEvent(eV);
					GameManager::getInstance()->addHit();
			}
 				
			if (!(o_->isAnEnemy() && e != nullptr))
				o_->DeactivateBullet();
			
		}
	}
}

ImpactComponent::~ImpactComponent()
{
}
