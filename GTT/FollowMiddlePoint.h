#pragma once
#include "LogicComponent.h"
#include "Game.h"

class FollowMiddlePoint : public LogicComponent
{
public:
	FollowMiddlePoint(GameObject* obj1, GameObject* obj2, cameraType cam1, cameraType cam2, float speed=0.9, float perc=0.5);
	virtual ~FollowMiddlePoint();
	virtual void update(GameObject *o, Uint32 deltaTime) override;

private:
	GameObject* obj1_;
	cameraType cam1_;
	GameObject* obj2_;
	cameraType cam2_;
	float perc_;//cercania del punto intermedio a el obj1 de 0 a 1
	float speed_;//velocidad a la que se acerca la camara al objetivo de 0 a 1
};

