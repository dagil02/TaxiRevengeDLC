#pragma once
#include "Container.h"
#include "Observer.h"


class Money : public Container, public Observable, public Observer {
public:
	static Money* getInstance();

	inline static void destroyInstance() {
		delete singleton_; singleton_ = nullptr;
	}

	virtual bool receiveEvent(Event& e) override;

	void setCurrentMoney(int money);
	void addMoney(int money);
	int getCurrentMoney();
	int getMinMoney();


private:
	static Money *singleton_;

	Money();
	virtual ~Money();

	int minimumMoney_ = 0;
	int currentMoney_;
};

