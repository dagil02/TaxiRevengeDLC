#pragma once

#include "Phrases.h"
#include "Text.h"
#include "Container.h"
#include <memory>



class DialoguesManager :
	public Container
{
	
public:
	DialoguesManager();
	~DialoguesManager();
	void evento(vector <string> phrases);
	void update(int deltaTime);


private:
	
	int time_;
	Text* txt_;
	bool displaying_;
	int maxTime_;
	Font* font_;
	SDL_Color color_;
	Vector2D pos_;
	int w_, h_;
	int timeDialogues_ = 10000;
};

