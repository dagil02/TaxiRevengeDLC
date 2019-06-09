#pragma once

#include <vector>
#include "Events.h"

using namespace std;

class Observer;

class Observable
{
public:
	Observable();
	virtual ~Observable();

	void registerObserver(Observer* o);
	bool removeObserver(Observer* o);
	bool isRegistered(Observer* o, int &index);
	void cleanObservers();

	void broadcastEvent(Event& e);

protected:
	//void broadcastEvent(Event& e);

private:
	vector<Observer*> observers;
};

