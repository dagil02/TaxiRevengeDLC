#pragma once
#include "Vector2D.h"

class Observable;
class b2Body;

enum event_type {
	GAME_START,
	GAME_END,

	HEALTH_CHANGED,
	MONEY_CHANGED,
	RESPAWNED,
	PAUSE,

	//Vehicle sound management
	STARTED_MOVING_FORWARD,
	STOPPED_MOVING_FORWARD,
	BACK_MOVING_FORWARD,
	STOPPED_BACK_MOVING_FORWARD,

	CHANNEL_STOPPED_PLAYING,

	EVENTS_LENGTH,

	TRIGGER_EVENT,
	//Buttons management
	CLICK_BUTTON,
	OVER_OBJECT,
	NOT_OVER_OBJECT,

	//Proyectile Sounds management
	TAXI_SHOOT,

	//Taxi Animations
	TURN_LEFT,
	TURN_RIGHT,
	TURN_DEFAULT,
	STOP_BACKFORWARD,
	IMPACT_DAMAGE
};

struct Event {
	Event(Observable *sender, event_type type) {
		this->type_ = type;
		this->sender_ = sender;
	}

	event_type type_;
	Observable* sender_;
};

struct HealthChangedEvent : public Event {
	HealthChangedEvent(Observable* sender, int currentHealth, int previousHealth, int maxHealth) :
		Event(sender, HEALTH_CHANGED){
		this->currentHealth_ = currentHealth;
		this->previousHealth_ = previousHealth;
		this->maxHealth_ = maxHealth;
	}

	int currentHealth_;
	int previousHealth_;
	int maxHealth_;
};

struct PauseEvent : public Event {
	PauseEvent(Observable* sender,bool pausa) :
		Event(sender, PAUSE) {
		this->pausa_ = pausa;
		
	}

	bool pausa_;
};

struct MoneyChangedEvent : public Event {
	MoneyChangedEvent(Observable* sender, int currentMoney, int previousMoney) :
		Event(sender, MONEY_CHANGED) {
		this->currentMoney_ = currentMoney;
		this->previousMoney_ = previousMoney;
	}

	int currentMoney_;
	int previousMoney_;
};

struct TriggerEvent : public Event {
	TriggerEvent(Observable* sender, b2Body* detected, bool leaving) :
		Event(sender, TRIGGER_EVENT) {
		detected_ = detected;
		leaving_ = leaving;
	}

	b2Body* detected_;
	bool leaving_;
};
struct ChannelStoppedPlaying : public Event {
	ChannelStoppedPlaying(Observable* sender, int channel) : Event(sender, CHANNEL_STOPPED_PLAYING) {
		channel_ = channel;
	}

	int channel_;
};

struct MouseClickLeft : public Event {
	MouseClickLeft(Observable* sender, int button) : Event(sender, CLICK_BUTTON) {
		button_ = button;
	}

	int button_;
};

struct MouseOverObj : public Event {
	MouseOverObj(Observable* sender, int objIndex) : Event(sender, OVER_OBJECT) {
		objIndex_ = objIndex;
	}
	int objIndex_;
};

struct NotMouseOverObj : public Event {
	NotMouseOverObj(Observable* sender, int objIndex) : Event(sender, NOT_OVER_OBJECT) {
		objIndex_ = objIndex;
	}
	int objIndex_;
};

struct TaxiShootEvent : public Event {
	TaxiShootEvent(Observable* sender, int sID) : Event(sender, TAXI_SHOOT) {
		shootId_ = sID;
	}
	int shootId_;
};




