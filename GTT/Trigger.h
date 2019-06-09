#pragma once
#include "Container.h"
#include "PhysicObject.h"
#include "CustomContactListener.h"

class Trigger :	public Container, public Observable {
public:
	Trigger(int w, int h, int x, int y);
	virtual ~Trigger();

	PhysicObject* getPhysicsObject();

protected:
	PhysicObject* phyO_;

	virtual void beginCallback(b2Contact* contact) = 0;
	virtual void endCallback(b2Contact* contact) = 0;

private:
	void beginCallbackHelper(b2Contact* contact);
	void endCallbackHelper(b2Contact* contact);
};

