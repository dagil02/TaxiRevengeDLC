#include "FollowMiddlePoint.h"
#include "Reticule.h"

FollowMiddlePoint::FollowMiddlePoint(GameObject * obj1, GameObject * obj2, cameraType cam1, cameraType cam2,float speed, float perc)
{
	obj1_ = obj1;
	obj2_ = obj2;
	perc_ = perc;
	cam1_ = cam1;
	cam2_ = cam2;
	speed_ = speed;
}

FollowMiddlePoint::~FollowMiddlePoint()
{
}

void FollowMiddlePoint::update(GameObject * o, Uint32 deltaTime)
{
	Vector2D object1pos = Vector2D(obj1_->getCenter().x, obj1_->getCenter().y);
	Vector2D object2pos = Vector2D(obj2_->getCenter().x, obj2_->getCenter().y);
	if (cam1_ == UI_CAMERA) {
		object1pos = Vector2D(obj1_->getCenter().x + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().x, obj1_->getCenter().y + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().y);

	}
	if (cam2_ == UI_CAMERA) {
		object2pos = Vector2D(obj2_->getCenter().x + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().x, obj2_->getCenter().y + Game::getInstance()->getCamera(GAME_CAMERA)->getPosition().y);
	}
	Vector2D middlepoint = Vector2D(object1pos.x + (object2pos.x - object1pos.x) * perc_, object1pos.y + (object2pos.y - object1pos.y) * perc_);
	Vector2D a = Vector2D((o->getPosition().x + (middlepoint.x - o->getCenter().x) *speed_*deltaTime/100),
		(o->getPosition().y + (middlepoint.y - o->getCenter().y)*speed_*deltaTime/100));
	o->setPosition(Vector2D(a.x , a.y));
}