#include "IApatrol.h"
#include "PhysicObject.h"
#include "Vehicle.h"
#include "EnemyManager.h"

IApatrol::IApatrol(PhysicObject * ph, GameObject* o, NodeMap * districtMap, int patrolSpeed, vector<Node*> route): IAMovementBehaviour(ph, o, districtMap, patrolSpeed)
{
	patrol_ = route;
}

void IApatrol::update(GameObject* o, Uint32 deltaTime)
{
	if (!started_) {
		goTo(districtMap_->getNearestConnectedNode(o->getCenter()));
		patrolProgress_ = -1;
		routeProgress_ = 0;
		started_ = true;
	}
	else {
		if (arrivedAtNode()) {
			int i;
			if (patrolProgress_ ==-1 && isPatrolNode(i)) {
				patrolProgress_ = (i + 1) % patrol_.size();
				
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_]);
				routeProgress_ = 0;
			}
			else if(patrolProgress_==-1) {
				patrolProgress_++;
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_]);
				routeProgress_ = 0;
			}
			else if(atNextPatrolNode()) {
				patrolProgress_ = (patrolProgress_ + 1) % patrol_.size();
				route_ = AssignRoute(nextNode_, patrol_[patrolProgress_]);
				routeProgress_ = 0;
			}
			if (routeProgress_ < route_.size()) {
				goTo(route_[routeProgress_]);
				routeProgress_++;
			}
			
		}
		else {
			if (EnemyManager::getInstance()->EnemyAtPos(nextNode_->position_, o_) && (o_->getCenter() - nextNode_->position_).Length() <= 32 * 3) {
				phyO_->getBody()->SetLinearVelocity(Vector2D());
			}
			else {
				goTo(nextNode_);
			}
		}
	}

	//if(nextNode_!=nullptr)
		//cout << nextNode_->id_ << endl;
}

IApatrol::~IApatrol()
{
}

bool IApatrol::isPatrolNode(int& a)
{
	for (int i = 0; i < patrol_.size(); i++) {
		if (nextNode_ == patrol_[i]) {
			a = i;
			return true;
		}
	}
	return false;
}

bool IApatrol::atNextPatrolNode()
{
	return nextNode_==patrol_[patrolProgress_];
}

