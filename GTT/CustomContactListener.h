#pragma once
#include <Box2D/Box2D.h>
#include <vector>
#include <functional>

using namespace std;

typedef function<void (b2Contact* contact)> contactCallback;

class CustomContactListener : public b2ContactListener {
public:
	static CustomContactListener* getInstance();
	inline static void destroyInstance() {
		delete singleton_; singleton_ = nullptr;
	}

	// DO NOT CALL, THIS IS ONLY USED BY BOX2D TO FIRE EVENTS
	virtual void BeginContact(b2Contact* contact) override {
		for (auto cb : beginCallbacks_)
			cb(contact);
	}

	// DO NOT CALL, THIS IS ONLY USED BY BOX2D TO FIRE EVENTS
	virtual void EndContact(b2Contact* contact) override {
		for (auto cb : endCallbacks_)
			cb(contact);
	}

	// Returns the id assigned to the callback (used later
	// if you need to remove the callback)
	int addBeginCallback(const contactCallback &cb);

	// Returns the id assigned to the callback (used later
	// if you need to remove the callback)
	int addEndCallback(const contactCallback &cb);

	// Returns whether the callback with the given id could be deleted
	bool removeBeginCallback(int id);

	// Returns whether the callback with the given id could be deleted
	bool removeEndCallback(int id);

private:
	static CustomContactListener *singleton_;

	CustomContactListener() {};
	~CustomContactListener() {};

	vector<contactCallback> beginCallbacks_;
	vector<contactCallback> endCallbacks_;
};

