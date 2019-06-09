#include "IAMovementBehaviour.h"
#include "PhysicObject.h"

IAMovementBehaviour::IAMovementBehaviour(PhysicObject * ph, GameObject * o, NodeMap * districtMap, int patrolSpeed)
{
	started_ = false;
	phyO_ = ph;
	o_ = o;
	districtMap_ = districtMap;
	speed_ = patrolSpeed;
	nextNode_ = nullptr;
}

IAMovementBehaviour::~IAMovementBehaviour()
{
}

void IAMovementBehaviour::goTo(Node * n)
{
	nextNode_ = n;
	Vector2D direction_ = Vector2D(n->position_.x - o_->getCenter().x, n->position_.y - o_->getCenter().y);
	direction_.Normalize();
	if (direction_.x != 0 || direction_.y != 0) {
		float angle = atan2f(-direction_.x, direction_.y);
		angle += 90.0 / 180.0*M_PI;
		phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
	}
	phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * speed_, direction_.y * speed_));
}

bool IAMovementBehaviour::arrivedAtNode()
{
	return(nextNode_->position_.x <= o_->getCenter().x + 5 && nextNode_->position_.x >= o_->getCenter().x - 5 &&
		nextNode_->position_.y <= o_->getCenter().y + 5 && nextNode_->position_.y >= o_->getCenter().y - 5);
}

vector<Node*> IAMovementBehaviour::AssignRoute(Node * current, Node * destination)
{
	vector<Node*> route;
	vector<Node*> v;
	int minDistance = -1;
	districtMap_->FindRoute(current, destination, route, v, 0, minDistance);
	return route;
}