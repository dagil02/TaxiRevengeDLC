#pragma once

#include "LogicComponent.h"

enum FollowAnchor {
	CENTER,
	MIDDLETOP
};

class FollowGameObject :public LogicComponent
{
public:
	FollowGameObject(GameObject* objectToFollow, FollowAnchor anch = CENTER, Vector2D offset = Vector2D(0,0));
	~FollowGameObject();

	virtual void update(GameObject *o, Uint32 deltaTime) override;

private:
	GameObject* objectToFollow_;
	Vector2D offset_;
	FollowAnchor anch_;
};

