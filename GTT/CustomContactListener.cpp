#include "CustomContactListener.h"

CustomContactListener * CustomContactListener::singleton_ = nullptr;

CustomContactListener * CustomContactListener::getInstance() {
	if (singleton_ == nullptr)
		singleton_ = new CustomContactListener();

	return singleton_;
}

int CustomContactListener::addBeginCallback(const contactCallback &cb) {
	int id = 0;
	for (auto callback : beginCallbacks_) {
		if (callback == NULL) {
			callback = cb;
			break;
		}
		id++;
	}

	if (id == beginCallbacks_.size())
		beginCallbacks_.push_back(cb);

	return id;
}

int CustomContactListener::addEndCallback(const contactCallback &cb) {
	int id = 0;
	for (auto callback : endCallbacks_) {
		if (callback == NULL) {
			callback = cb;
			break;
		}
		id++;
	}

	if (id == endCallbacks_.size())
		endCallbacks_.push_back(cb);

	return id;
}

bool CustomContactListener::removeBeginCallback(int id) {
	if (!beginCallbacks_.empty() && id >= 0 && id < beginCallbacks_.size()) {
		beginCallbacks_[id] = NULL;
		return true;
	}

	return false;
}

bool CustomContactListener::removeEndCallback(int id) {
	if (!endCallbacks_.empty() && id >= 0 && id < endCallbacks_.size()) {
		endCallbacks_[id] = NULL;
		return true;
	}

	return false;
}
