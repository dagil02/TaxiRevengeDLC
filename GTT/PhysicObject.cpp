#include "PhysicObject.h"


PhysicObject::PhysicObject(b2BodyType type, int w, int h, int x, int y, bool createFixture) {
	visualSize_ = Vector2D(w, h);

	Vector2D halfSize = Vector2D(w / 2 * PHYSICS_SCALING_FACTOR, h / 2 * PHYSICS_SCALING_FACTOR);

	// Body definition and instantiation
	bodyDef_ = b2BodyDef();
	bodyDef_.position.Set(x * PHYSICS_SCALING_FACTOR + (w / 2 * PHYSICS_SCALING_FACTOR),
		y * PHYSICS_SCALING_FACTOR + (h / 2 * PHYSICS_SCALING_FACTOR));
	bodyDef_.type = type;
	body_ = Game::getInstance()->getWorld()->CreateBody(&bodyDef_);

	// Fixture definition and instantiation
	if (createFixture) {
		fixtureDef_ = b2FixtureDef();
		shape_.SetAsBox(halfSize.x, halfSize.y);
		fixtureDef_.shape = &shape_;
		fixtureDef_.density = 1;
		fixtureDef_.friction = DEFAULT_FRICTION;
		body_->CreateFixture(&fixtureDef_);
	}
}


PhysicObject::~PhysicObject() {
	Game::getInstance()->getWorld()->DestroyBody(body_); 
	body_ = nullptr;
}

void PhysicObject::update(GameObject * o, Uint32 deltaTime) {
	Vector2D nextPos = body_->GetPosition();
	nextPos.Divide(PHYSICS_SCALING_FACTOR);

	if (abs(body_->GetLinearVelocity().Length()) < 0.5)
		body_->SetLinearVelocity(Vector2D());

	if (abs(body_->GetAngularVelocity()) < 0.5)
		body_->SetAngularVelocity(0);

	o->setPosition(nextPos - (Vector2D(visualSize_.x/2, visualSize_.y/2)));
	o->setRotation(body_->GetAngle() * 180 / M_PI);
}

const b2Vec2 PhysicObject::getOrigin() {
	return origin_;
}

b2Body * PhysicObject::getBody() {
	return body_;
}

void PhysicObject::setSensor(bool sensor) {
	body_->GetFixtureList()->SetSensor(sensor);
}

bool PhysicObject::isSensor() {
	return body_->GetFixtureList()->IsSensor();
}

// The category bits are all set to 0 by default (no group)
// The mask bits are all set to 1 by default (collides with everything)
void PhysicObject::setCollisions(int16 groupIndex, uint16 category, uint16 mask) {
	b2Filter data;
	data.groupIndex = groupIndex;
	data.categoryBits = category;
	data.maskBits = mask;

	body_->GetFixtureList()->SetFilterData(data);
}
