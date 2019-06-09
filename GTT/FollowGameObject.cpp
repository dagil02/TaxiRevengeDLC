#include "FollowGameObject.h"



FollowGameObject::FollowGameObject(GameObject* objectToFollow, FollowAnchor anch, Vector2D offset) {
	objectToFollow_ = objectToFollow;
	offset_ = offset;
	anch_ = anch;
}

FollowGameObject::~FollowGameObject() {
	objectToFollow_ = nullptr;
}


void FollowGameObject::update(GameObject * o, Uint32 deltaTime) {
	if (anch_ == CENTER)
		o->setPosition(Vector2D(objectToFollow_->getCenter().x - o->getWidth() / 2 + offset_.x, objectToFollow_->getCenter().y - o->getHeight() / 2 + offset_.y));
	else if (anch_ == MIDDLETOP)
		o->setPosition(Vector2D(objectToFollow_->getCenter().x - o->getWidth() / 2 + sin(objectToFollow_->getRotation() / 180.0*M_PI) * objectToFollow_->getHeight()/2 + offset_.x,
			objectToFollow_->getCenter().y - o->getHeight() / 2 + -cos(objectToFollow_->getRotation() / 180.0*M_PI) * objectToFollow_->getHeight()/2 +  offset_.y));

}
