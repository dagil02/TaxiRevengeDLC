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
	void eventoEnCadena(vector <string> phrases);


private:
	
	int time_;
	Text* txt_;
	bool displaying_;
	int maxTime_;
	Font* font_;
	SDL_Color color_;
	Vector2D pos_;
	int w_, h_;
	int timeDialogues_ = 12000;
	int act_;
	bool eventChain_;
	vector <string> phrases_;
	
	int historia_;
	int contHist_;
};

