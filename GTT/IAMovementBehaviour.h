#pragma once
#include "LogicComponent.h"
#include "NodeMap.h"
#include <vector>

class PhysicObject;

class IAMovementBehaviour : public LogicComponent
{
public:
	IAMovementBehaviour(PhysicObject* ph, GameObject* o, NodeMap* districtMap, int patrolSpeed);
	virtual void update(GameObject* o, Uint32 deltaTime)=0;
	virtual ~IAMovementBehaviour();
	void Restart() { started_ = false; }
protected:
	void goTo(Node* n);
	bool arrivedAtNode();
	vector<Node*> AssignRoute(Node* current, Node* destination);

	GameObject* o_;
	PhysicObject* phyO_;
	NodeMap* districtMap_;
	Node* nextNode_;
	vector<Node*> route_;
	int routeProgress_;
	int speed_;
	bool started_;
};

