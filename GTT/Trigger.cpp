#include "Trigger.h"
#include <functional>

Trigger::Trigger(int w, int h, int x, int y) {
	width_ = w; height_ = h;
	position_ = Vector2D(x, y);

	phyO_ = new PhysicObject(b2_kinematicBody, w, h, x, y);
	phyO_->setSensor(true);
	addLogicComponent(phyO_);

	// Set the callbacks
	CustomContactListener::getInstance()->addBeginCallback(bind(&Trigger::beginCallbackHelper, this, std::placeholders::_1));
	CustomContactListener::getInstance()->addEndCallback(bind(&Trigger::endCallbackHelper, this, std::placeholders::_1));
}


Trigger::~Trigger() {
	delete phyO_; phyO_ = nullptr;
}

PhysicObject * Trigger::getPhysicsObject() {
	return phyO_;
}

void Trigger::beginCallbackHelper(b2Contact * contact) {
	if (active_)
		beginCallback(contact);
}

void Trigger::endCallbackHelper(b2Contact * contact) {
	if (active_)
		endCallback(contact);
}
