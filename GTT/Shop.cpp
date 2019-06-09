#include "Shop.h"
#include "Vehicle.h"

Shop::Shop(int w, int h, int x, int y) : Trigger(w, h, x, y) {

}

Shop::~Shop() {

}

void Shop::beginCallback(b2Contact * contact) {
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		contact->SetEnabled (true);
		//Game::getInstance()->setState(NAME_GAS_MAIN_STATE);
		Game::getInstance ()->setCloseToShop (true);
	}
}

void Shop::endCallback(b2Contact * contact){
	b2Body* body = phyO_->getBody();
	b2Body* taxiBody = Vehicle::getInstance()->GetPhyO()->getBody();

	if ((contact->GetFixtureA()->GetBody() == body || contact->GetFixtureA()->GetBody() == taxiBody)
			&& (contact->GetFixtureB()->GetBody() == body || contact->GetFixtureB()->GetBody() == taxiBody)) {
		contact->SetEnabled (false);
		//Game::getInstance()->setState(NAME_GAS_MAIN_STATE);
		Game::getInstance ()->setCloseToShop (false);
	}
	
}
