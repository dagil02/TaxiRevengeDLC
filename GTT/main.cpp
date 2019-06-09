#pragma once

// Visual Leak Detector library:
// uncomment the include to check for memory leaks
//#include <vld.h>

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

#include "Game.h"

using namespace std;

typedef unsigned int uint;

int main(int argc, char* argv[]) {
	Game::getInstance()->initInstance(); //initInstance() only once
	Game::getInstance()->run();
	Game::destroyInstance();

	return 0;
}