#include "EnterShopIC.h"
#include "Game.h"

EnterShopIC::EnterShopIC () {
}


EnterShopIC::~EnterShopIC () {
}

void EnterShopIC::handleInput (GameObject * o, Uint32 deltaTime, const SDL_Event & event) {
	if (Game::getInstance ()->getCloseToShop ()) {
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_g) {
				Game::getInstance ()->getGameStateMachine ()->fromMainStateToGasMainMenu ();
			}
		}
	}
}
