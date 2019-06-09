#pragma once

#include "Observable.h"

class Observer {
public:
	Observer();
	virtual ~Observer();

	// Returns false only if it wants to cut off
	// the event broadcasting
	virtual bool receiveEvent(Event& e) = 0;
};

