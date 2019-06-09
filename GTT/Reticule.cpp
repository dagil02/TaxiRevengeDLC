#include "Reticule.h"



unique_ptr<Reticule > Reticule::instance_ = nullptr;

Reticule::Reticule()
{
	//tantos como distintos sprites de reticula;
	animations_["gun"] = "../Assets/sprites/gunreticule.png";
	animations_["shotgun"] = "../Assets/sprites/shotgunreticule.png";
	animations_["machinegun"] = "../Assets/sprites/machinegunreticule.png";
	animations_["sniper"]= "../Assets/sprites/sniperreticule.png";

	animC_ = new Animation();
	cursorC_ = new CursorLC();
	animC_->setCamera(UI_CAMERA);
	addRenderComponent(animC_);
	addLogicComponent(cursorC_);
	for (auto o : animations_) {
		animC_->loadAnimation(o.second, o.first);//carga las distintas animaciones en el componente de render
	}
	
	height_ = 75;
	width_ = 75;
}


Reticule::~Reticule()
{
	delete animC_; animC_ = nullptr;
	delete cursorC_; cursorC_ = nullptr;
}

void Reticule::ChangeReticule(string ret)
{
	if (!animC_->playAnimation(ret)) cout << "ChangeReticule error, reticule: " + ret + " doesnt exist";
	//if (!animC_->playAnimation(ret))
}

string Reticule::GetCurrentSprite()
{
	return animC_->getCurrentAnimation();
}

void Reticule::render(Uint32 deltaTime)
{
	Container::render(deltaTime);
}

