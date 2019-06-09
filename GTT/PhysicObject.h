#pragma once
#include "LogicComponent.h"
#include <Box2D/Box2D.h>
#include "Game.h"

class PhysicObject :public LogicComponent
{
public:
	PhysicObject(b2BodyType type, int w, int h, int x, int y, bool createFixture = true);
	virtual ~PhysicObject();
	virtual void update(GameObject* o, Uint32 deltaTime);

	const b2Vec2 getOrigin();
	b2Body* getBody();

	void setSensor(bool sensor);
	bool isSensor();

	void setCollisions(int16 groupIndex = 0, uint16 category = 0x0000, uint16 mask = 0xFFFF);

private:
	b2Body* body_;
	b2BodyDef bodyDef_;
	Vector2D visualSize_;
	Vector2D origin_;

	b2FixtureDef fixtureDef_;
	b2PolygonShape shape_;
};

