#pragma once
#include "Container.h"
#include "Sprite.h"
#include "Animation.h"
#include "MouseClickIC.h"



class Button : public Container {

public:
	Button();
	virtual ~Button ();

	//CallBackOnClick *callback = nullptr;
	
	Animation* getButtonAnimation();
	void setButtonAnimation(Animation* anm);

	MouseClickIC* getMouseClickIC();
	void setMouseClickIC(MouseClickIC* mCIc);
	void setClickSound(soundId = (soundId)-1);

	void setIndex(int i);
	int getIndex();

	Animation* getButtonAnimacion();

	const soundId getSoundId();


private:
	Sprite* buttonSprite_ = nullptr;
	Animation* buttonAnimation_ = nullptr;
	MouseClickIC* mouseClickIC_ = nullptr;

	soundId clickSound_;

	int index_;
};

