#include "Observable.h"
#include "Observer.h"
#include <iostream>

Observable::Observable() {

}

Observable::~Observable() {
	observers.clear();
}

void Observable::registerObserver(Observer * o) {
	int index;
	if (!isRegistered(o, index))
		observers.push_back(o);
}

bool Observable::removeObserver(Observer *o) {
	int index;
	if (isRegistered(o, index)) {
		observers.erase(observers.begin() + index);
		return true;
	}

	return false;
}

bool Observable::isRegistered(Observer * o, int &index) {
	vector<Observer*>::iterator it = find(observers.begin(), observers.end(), o);
	index = it - observers.begin();

	return it != observers.end();
}

void Observable::cleanObservers() {
	observers.clear();
}

void Observable::broadcastEvent(Event& e) {
	for (auto observer:observers) {
		if (!observer->receiveEvent(e))
			break;
	}
}
