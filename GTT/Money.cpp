#include "Money.h"
#include "UI.h"

Money *Money::singleton_ = nullptr;

Money::Money() {
	currentMoney_ = minimumMoney_;
	registerObserver(UI::getInstance());
}


Money::~Money() {

}

Money * Money::getInstance() {
	if (singleton_ == nullptr)
		singleton_ = new Money();

	return singleton_;
}

bool Money::receiveEvent(Event & e) {
	return false;
}

void Money::setCurrentMoney(int money) {
	MoneyChangedEvent e(this, money, currentMoney_);
	broadcastEvent(e);

	currentMoney_ = money > minimumMoney_ ? money : minimumMoney_;

}

void Money::addMoney(int money)
{
	if (currentMoney_ + money > minimumMoney_) 
	{	
		MoneyChangedEvent e(this, currentMoney_ + money, currentMoney_);
		broadcastEvent(e);
		currentMoney_ += money;
	}
}

int Money::getCurrentMoney() {
	return currentMoney_;
}

int Money::getMinMoney() {
	return minimumMoney_;
}
