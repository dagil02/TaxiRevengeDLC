#include "InputMovement.h"
#include "Money.h"

InputMovement::InputMovement(KeysScheme k, Vehicle* v)
{
	k_ = k;
	v_ = v;

	targetDamping = DFLT_DAMPING;
	targetLateralVelocity = DFLT_LATERAL_VELOCITY;

	targetMaxSpeed = v_->GetMaxSpeed();
	v_->GetPhyO()->getBody()->SetAngularDamping(DFLT_ANG_DAMPING);
}


InputMovement::~InputMovement()
{
}

void InputMovement::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN)
		if (event.key.keysym.sym == SDLK_l)
			Money::getInstance()->addMoney(100);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == k_.forward) {
			forwardPressed_ = true;
			Event e(this, STARTED_MOVING_FORWARD);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.backwards) { 
			backwardPressed_ = true;
			//sound event
			Event e(this, BACK_MOVING_FORWARD);
			broadcastEvent(e);

			//animation event
			Event e_anm(this, STOP_BACKFORWARD);
			broadcastEvent(e_anm);
		}

		if (event.key.keysym.sym == k_.turnRight) { 
			rightTurnPressed_ = true; 
			Event e(this, TURN_RIGHT);	
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.turnLeft) { 
			leftTurnPressed_ = true; 
			Event e(this, TURN_LEFT);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = true;
	}
	else if (event.type == SDL_KEYUP) {	
		if (event.key.keysym.sym == k_.forward) {
			forwardPressed_ = false;
			Event e(this, STOPPED_MOVING_FORWARD);
			broadcastEvent(e);
		}
		if (event.key.keysym.sym == k_.backwards) { 
			backwardPressed_ = false; 
			//sound event
			Event e(this, STOPPED_BACK_MOVING_FORWARD);
			broadcastEvent(e);
			//animation event
			Event e_anm(this, TURN_DEFAULT);
			broadcastEvent(e_anm);
		}

		if (event.key.keysym.sym == k_.turnRight || event.key.keysym.sym == k_.turnLeft) {
			Event e(this, TURN_DEFAULT);
			broadcastEvent(e);
			if (event.key.keysym.sym == k_.turnRight) rightTurnPressed_ = false;
			if (event.key.keysym.sym == k_.turnLeft) leftTurnPressed_ = false;
		}
		if (event.key.keysym.sym == SDLK_SPACE) handBrakePressed_ = false;
	}
}

void InputMovement::update(GameObject * o, Uint32 deltaTime)
{
	b2Body* body = Vehicle::getInstance()->GetPhyO()->getBody();
	Vector2D currentDir = Vector2D(cos(body->GetAngle()), sin(body->GetAngle()));
	Vector2D vel = body->GetLinearVelocity();

	// Check the difference beetween car and speed direction to see
	// if it's going forward
	bool isGoingForward = abs(currentDir.Angle(vel)) < M_PI / 2;

	// Forward and backward acceleration
	if (forwardPressed_ && !backwardPressed_ && body->GetLinearVelocity().Length() < (targetMaxSpeed)) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(impulse, body->GetWorldCenter(), true);
	}
	else if (backwardPressed_ && !forwardPressed_ && !handBrakePressed_ &&
			 (body->GetLinearVelocity().Length() < v_->GetMaxBackwardSpeed()
			  || isGoingForward)) {
		Vector2D impulse = body->GetMass() * v_->GetAcceleration() * currentDir;
		body->ApplyLinearImpulse(-1 * impulse, body->GetWorldCenter(), true);
	}

	// Handle rotation
	steeringWheel();

	// Handbrake
	if (!handBrakePressed_) {
		targetDamping = DFLT_DAMPING;
		if (targetLateralVelocity > DFLT_LATERAL_VELOCITY)
			targetLateralVelocity -= (HBRK_LATERAL_RECOVER * deltaTime / 100);
		else
		targetLateralVelocity = HBRK_LATERAL_VELOCITY;
		targetMaxSpeed = v_->GetMaxSpeed();
	}
	else {
		targetDamping = HBRK_DAMPING;
		targetLateralVelocity = HBRK_LATERAL_VELOCITY;
		targetMaxSpeed -= deltaTime * HBRK_SPEED_DECAY;
	}
	// Update frictions
	updateFriction();
}

void InputMovement::steeringWheel() {
	b2Body* body = Vehicle::getInstance()->GetPhyO()->getBody();

	float turnSpeed = 0;
	if (backwardPressed_) {
		if (!forwardPressed_ && !handBrakePressed_) {
			if (leftTurnPressed_) turnSpeed = 1.4 * v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 1.4 * -v_->GetTurnSpeed();
		}
	}
	else {
		if (handBrakePressed_) {
			if (leftTurnPressed_) turnSpeed = -2* v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 2* v_->GetTurnSpeed();
		}
		else {
			if (leftTurnPressed_) turnSpeed = -1.4 * v_->GetTurnSpeed();
			else if (rightTurnPressed_) turnSpeed = 1.4 * v_->GetTurnSpeed();
		}
	}

	if (turnSpeed != 0) {
		turnSpeed *= body->GetLinearVelocity().Length() / v_->GetMaxSpeed();
		body->SetAngularVelocity(turnSpeed);
	}
}

Vector2D InputMovement::getLateralVelocity() {
	b2Body* body = Vehicle::getInstance()->GetPhyO()->getBody();
	Vector2D normal = body->GetWorldVector(Vector2D(0, 1));
	return b2Dot(normal, body->GetLinearVelocity()) * normal;
}

void InputMovement::updateFriction() {
	b2Body* body = Vehicle::getInstance()->GetPhyO()->getBody();

	body->SetLinearDamping(targetDamping);

	double lateralImpulseModifier = 1 - targetLateralVelocity;
	Vector2D lateralImpulse = lateralImpulseModifier * body->GetMass() * getLateralVelocity().Multiply(-1);
	body->ApplyLinearImpulse(lateralImpulse, body->GetWorldCenter(), false);
} 

bool InputMovement::isMoving() {
	if (abs(Vehicle::getInstance()->GetPhyO()->getBody()->GetLinearVelocity().Length()) > 0)
		return true;
	else 
		return false;
}