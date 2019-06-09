#pragma once
#include "LogicComponent.h"
#include "SoundManager.h"
#include "Observer.h"

#include <map>

class Car;

class TaxiSoundManagerCP :
	public LogicComponent, public Observer
{
public:
	TaxiSoundManagerCP(Car* v);

	void start();
	virtual void update(GameObject* o, Uint32 deltaTime);
	virtual bool receiveEvent(Event& e);
	virtual ~TaxiSoundManagerCP();

	//void PlaySound(soundId id);
private:
	SoundManager* s_;
	Car* v_;

	//Max SDL_Mixer channels: 8
	map <string, int> Channels_;
	
	int ch_2_Vol_; 
	int ch_3_Vol_;
	int ch_4_Vol_;
	int ch_6_Vol_;

	bool ch_3KeyDown;
	bool ch_3KeyUp;
	bool ch_5KeyUp;
	bool ch_6_KeyDown;
	bool ch_6_KeyUp;

	bool keyBackDown_;

	bool DEBUG_;	

};

