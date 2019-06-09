#pragma once
#include "IAMovementBehaviour.h"

class IApatrol :
	public IAMovementBehaviour
{
public:
	IApatrol(PhysicObject* ph, GameObject* o, NodeMap* districtMap, int patrolSpeed, vector<Node*> route);
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual ~IApatrol();

private:
	bool isPatrolNode(int& a);
	bool atNextPatrolNode();

	vector<Node*> patrol_;
	int patrolProgress_;
};

