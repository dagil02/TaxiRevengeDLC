#include "IAFollow.h"
#include "Vehicle.h"
#include "EnemyManager.h"

IAFollow::IAFollow(PhysicObject * ph, GameObject * o, NodeMap * districtMap, int patrolSpeed, double followDistance) 
	:IAMovementBehaviour(ph, o, districtMap, patrolSpeed)
{
	followDistance_ = followDistance;
	edgeFollow_ = false;
}

void IAFollow::update(GameObject * o, Uint32 deltaTime)
{
	if (followDistance_ == -1 || getDistanceToTaxi() <= followDistance_) {
		if (!started_) {
			Node* a;
			Node* b;
			districtMap_->getBetweenNodes(a, b, o_->getCenter());
			//go to node that is connected to the enemy and nearest to the target
			if (b != nullptr && (b->position_ - Vehicle::getInstance()->getCenter()).Length() <= (a->position_ - Vehicle::getInstance()->getCenter()).Length()) {
				goTo(b);
			}
			else {
				goTo(a);
			}

			if (arrivedAtNode()) {
				route_ = AssignRoute(nextNode_, districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter()));
				routeProgress_ = 0;
				started_ = true;
			}
		}
		else {
			if (arrivedAtNode()) {
				
				phyO_->getBody()->SetLinearVelocity(Vector2D(0, 0));
				if (route_.empty() || route_.back() != districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter())) {
					route_ = AssignRoute(nextNode_, districtMap_->getNearestConnectedNode(Vehicle::getInstance()->getCenter()));
					routeProgress_ = 0;
				}
				if (!route_.empty() && routeProgress_ < route_.size()) {
					goTo(route_[routeProgress_]);
					routeProgress_++;
				}
			}
			if (TargetOnCurrentEdge()) {
				edgeFollow_ = true;
				if(getDistanceToTaxi() < FOLLOW_STOP_RANGE) {
					phyO_->getBody()->SetLinearVelocity(Vector2D());
				}
				else {
					Vector2D direction_ = Vehicle::getInstance()->getCenter() - o_->getCenter();
					direction_.Normalize();
					if (direction_.x != 0 || direction_.y != 0) {
						float angle = atan2f(-direction_.x, direction_.y);
						angle += 90.0 / 180.0*M_PI;
						phyO_->getBody()->SetTransform(phyO_->getBody()->GetPosition(), angle);
					}
					phyO_->getBody()->SetLinearVelocity(Vector2D(direction_.x * speed_, direction_.y * speed_));
				}
			}
			else {
				if (edgeFollow_) started_ = false;
				edgeFollow_ = false;
			}
		}
	}
	else {
		started_ = false;
		phyO_->getBody()->SetLinearVelocity(Vector2D());
	}
	
}

IAFollow::~IAFollow()
{
}

double IAFollow::getDistanceToTaxi()
{
	return (Vehicle::getInstance()->getCenter() - o_->getCenter()).Length();
}

bool IAFollow::TargetOnCurrentEdge()
{
	Node*a;
	Node*b;
	Node* A;
	Node* B;
	Vector2D taxipos = Vehicle::getInstance()->getCenter();
	districtMap_->getBetweenNodes(a, b, taxipos);
	districtMap_->getBetweenNodes(A, B, o_->getCenter());

	
	return(a == A && b == B || a == B && b == A || (a!=nullptr && (a->position_.x >= o_->getCenter().x - TILE_SIZE && a->position_.x <= o_->getCenter().x + TILE_SIZE
		&& a->position_.y >= o_->getCenter().y - TILE_SIZE && a->position_.y <= o_->getCenter().y + TILE_SIZE)) || (b!=nullptr && (b->position_.x >= o_->getCenter().x - TILE_SIZE && b->position_.x <= o_->getCenter().x + TILE_SIZE
			&& b->position_.y >= o_->getCenter().y - TILE_SIZE && b->position_.y <= o_->getCenter().y + TILE_SIZE)));
}
