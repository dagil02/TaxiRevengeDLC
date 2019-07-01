#include "DialoguesManager.h"



DialoguesManager::DialoguesManager()
{
	time_ = 0;
	displaying_ = false;
	maxTime_ = 0;
	act_ = 0;
	eventChain_ = false;
	historia_ = 0;
	contHist_ = 0;
	
	pos_ = Vector2D(500, 800);
	setPosition(pos_);
	font_ = new Font(FONT_COOLFONT, 60);
	color_ = SDL_Color();
	color_.r = 255; color_.g = 255; color_.b = 255;
	txt_ = new Text(font_, "", color_);
	
	txt_->setCamera(UI_CAMERA);
	addRenderComponent(txt_);
	txt_->setAutoPos(false);
	txt_->setAutoSize(false);
	txt_->setSize(1000, 50);
	txt_->setPos(150, 600);

	pausa = new Sprite();
	
	
	

	eventoEnCadena(tutorial);
}




DialoguesManager::~DialoguesManager() {
	delete txt_; txt_ = nullptr;
	delete font_; font_ = nullptr;
}

void DialoguesManager::evento(vector <string> phrases)
{
	if (!displaying_ && !eventChain_) {
		
		int random = rand() % phrases.size();
		 txt_->setText(phrases[random]); 
		displaying_ = true;
		maxTime_ = timeDialogues_;
	}
}

void DialoguesManager::update(int deltaTime)
{
	contHist_ += deltaTime;
	if (displaying_ ) {

		time_ += deltaTime;
		if (time_ > maxTime_) {
			txt_->setText(" ");
			displaying_ = false;
			maxTime_ = 0;
			time_ = 0;
			contHist_ = 0;
		}
	}


	else if (eventChain_) {
		time_ += deltaTime;
		if (time_ > maxTime_) {
			act_++;
			if (act_ < phrases_.size()) {
				txt_->setText(phrases_[act_]);
				time_ = 0;
			}
			else {
				act_ = 0;
				txt_->setText(" ");
				eventChain_ = false;
				maxTime_ = 0;
				time_ = 0;
				contHist_ = 0;
			}
			
		}
	}
	else if (historia_< historia.size() && contHist_ > 10000) {
		txt_->setText(historia[historia_]);
		displaying_ = true;
		maxTime_ = timeDialogues_;
		historia_++;
	}
}

void DialoguesManager::eventoEnCadena(vector<string> phrases)
{
	if (!displaying_ && !eventChain_) {
		phrases_ = phrases;
		txt_->setText(phrases[0]);
		eventChain_ = true;
		maxTime_ = timeDialogues_;
	}
}

void DialoguesManager::handleInput(Uint32 deltaTime, const SDL_Event & event)
{
	

	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_p) {  //cambia el estado de la pausa
			pausa = new Sprite("../Assets/sprites/menuPausa.png", 1280, 720);
			pausa->setCamera(UI_CAMERA);
			addRenderComponent(pausa);
			pausa->setAutoPos(false);
			pausa->setAutoSize(false);
			
		}
		else if (event.key.keysym.sym == SDLK_RETURN) {  //cambia el estado de la pausa
			delRenderComponent(pausa);
		}
	}
}
