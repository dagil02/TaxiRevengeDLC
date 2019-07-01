#include "PauseMenu.h"



PauseMenu::PauseMenu()
{
	int i; 
	if (!isRegistered(this, i))
		registerObserver(this);



	menu_ = new Sprite("../Assets/sprites/menuPausa.png",192,1080);
	background_ = new Container();

	background_->setWidth(GAS_BACKGROUND_W);
	background_->setHeight(GAS_BACKGROUND_H);
	background_->addRenderComponent(menu_);

	stage_.push_back(background_);
	std::cout << "hdbaskjldnaskldñ" << std::endl;
}


PauseMenu::~PauseMenu()
{
}



void PauseMenu::start()
{
}

void PauseMenu::end()
{
}

void PauseMenu::handleInput(Uint32 deltaTime, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_p) {  //cambia el estado de la pausa
			this->active_ = true;
			
		}
		else if (event.key.keysym.sym == SDLK_RETURN) {  //cambia el estado de la pausa
			this->active_ = false;
			
		}
	}
}
