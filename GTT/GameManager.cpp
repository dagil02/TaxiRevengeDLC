#include "GameManager.h"

unique_ptr<GameManager> GameManager::instance_ = nullptr;


GameManager::GameManager()
{
	initTime = SDL_GetTicks() / 1000;
}


GameManager::~GameManager()
{
}

void GameManager::update(Uint32 deltaTime)
{
	time = (SDL_GetTicks() -initTime) / 1000;
	//cout << time << "  " << hits << endl;
}

void GameManager::calculatePuntuation()
{
	int p = (((kills * 100000) / (hits)) / time )* 100;
	cout<<" * Score: ____" << p << "____"<< endl;
}

