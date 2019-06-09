#pragma once
#include "IAMovementBehaviour.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IAFollow :
	public IAMovementBehaviour
{
public:
	IAFollow(PhysicObject* ph, GameObject* o, NodeMap* districtMap, int patrolSpeed, double followDistance=-1);
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~IAFollow();

private:
	double followDistance_;
	double getDistanceToTaxi();
	bool TargetOnCurrentEdge();
	bool edgeFollow_;
};

