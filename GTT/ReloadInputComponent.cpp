#include "ReloadInputComponent.h"
#include "Turret.h"


ReloadInputComponent::ReloadInputComponent(SDL_Keycode reloadkey)
{
	reloadkey_ = reloadkey;
}

void ReloadInputComponent::handleInput(GameObject * o, Uint32 deltaTime, const SDL_Event & event)
{
	auto* x = static_cast<Turret*>(o);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == reloadkey_) {
			 x->InitiateReload();
		}
	}
}

ReloadInputComponent::~ReloadInputComponent()
{
}
