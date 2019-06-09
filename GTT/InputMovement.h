#pragma once
#include "Vehicle.h"

class InputMovement : public ControlType
{
public:
	InputMovement(KeysScheme k, Vehicle* v);
	virtual ~InputMovement();

	virtual void handleInput(GameObject* o, Uint32 deltaTime, const SDL_Event& event);
	virtual void update(GameObject* o, Uint32 deltaTime);

private:
	KeysScheme k_;
	Vehicle* v_;
	//Input booleans
	bool forwardPressed_ = false;
	bool backwardPressed_ = false;
	bool rightTurnPressed_ = false;
	bool leftTurnPressed_ = false;
	bool handBrakePressed_ = false;

	float targetLateralVelocity = 0;
	float targetDamping = 1;
	float targetMaxSpeed;

	void steeringWheel();
	bool isMoving();
	Vector2D getLateralVelocity();

	void updateFriction();
};

