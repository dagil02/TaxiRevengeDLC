#include "PauseMenu.h"



PauseMenu::PauseMenu()
{
	menu_ = new Animation();
	this->addRenderComponent(menu_);
	registerObserver(this);
}


PauseMenu::~PauseMenu()
{
}

bool PauseMenu::receiveEvent(Event & e)
{
	switch (e.type_)
	{
	case PAUSE:
		pausa = static_cast<PauseEvent&>(e).pausa_;
		if (pausa) menu_->loadAnimation("../Assets/sprites/menuPausa.png");
		else menu_ = new Animation();
		std::cout << "se recibe evento" << std::endl;
		break;

	default:
		break;
	}
	return true;
}
