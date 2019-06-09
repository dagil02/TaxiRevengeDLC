#include "Button.h"



//spriteSheet
Button::Button()
{
	mouseClickIC_ = new MouseClickIC();
	mouseClickIC_->setButton(this);
	addInputComponent(mouseClickIC_);
}


Button::~Button () {
	if (buttonSprite_ != nullptr) { delete buttonSprite_; buttonSprite_ = nullptr; }
		
	if (buttonAnimation_ !=nullptr){ delete buttonAnimation_; buttonAnimation_ = nullptr; }
		
	if (mouseClickIC_ != nullptr) { delete mouseClickIC_; mouseClickIC_ = nullptr; }
	
}

Animation * Button::getButtonAnimacion()
{
	return buttonAnimation_;
}

Animation * Button::getButtonAnimation()
{
	return buttonAnimation_;
}

void Button::setButtonAnimation(Animation * anm)
{
	buttonAnimation_ = anm;
}

MouseClickIC * Button::getMouseClickIC()
{
	return mouseClickIC_;
}

void Button::setMouseClickIC(MouseClickIC * mCIc)
{
	mouseClickIC_ = mCIc;
}

void Button::setClickSound(soundId sound)
{
	clickSound_ = sound;
}

void Button::setIndex(int i)
{
	index_ = i;
}

int Button::getIndex()
{
	return index_;
}


const soundId Button::getSoundId()
{
	if (clickSound_ != (int)-1)
		return clickSound_;
	else
		return (soundId)-1;
}
