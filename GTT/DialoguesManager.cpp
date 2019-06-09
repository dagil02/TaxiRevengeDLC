#include "DialoguesManager.h"



DialoguesManager::DialoguesManager()
{
	time_ = 0;
	displaying_ = false;
	maxTime_ = 0;
	
	pos_ = Vector2D(500, 800);
	setPosition(pos_);
	font_ = new Font(FONT_COOLFONT, 60);
	color_ = SDL_Color();
	color_.r = 255; color_.g = 255; color_.b = 255;
	txt_ = new Text(font_, "", color_);
	
	txt_->setCamera(UI_CAMERA);
	addRenderComponent(txt_);
	txt_->setAutoPos(true);
	txt_->setAutoSize(false);
	txt_->setSize(600, 80);
	//evento(muerte);
}




DialoguesManager::~DialoguesManager() {
	delete txt_; txt_ = nullptr;
	delete font_; font_ = nullptr;
}

void DialoguesManager::evento(vector <pair<string, string>> phrases)
{
	if (!displaying_) {
		
		int random = rand() % phrases.size();
		if (english) txt_->setText(phrases[random].second);
		else txt_->setText(phrases[random].first); 
		displaying_ = true;
		maxTime_ = timeDialogues_;
	}
}

void DialoguesManager::update(int deltaTime)
{
	if (displaying_) {

		time_ += deltaTime;
		if (time_ > maxTime_) {
			txt_->setText(" ");
			displaying_ = false;
			maxTime_ = 0;
			time_ = 0;
		}
	}
}
