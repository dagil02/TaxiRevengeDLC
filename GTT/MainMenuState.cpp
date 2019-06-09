#include "MainMenuState.h"
#include "Reticule.h"
#include "Game.h"


MainMenuState::MainMenuState()
{
	//inicialiacion id sonidos - se usa para gestionar el SoundManager desde MouseClickIC
	Sound_NewGameButton_ = CLIC_BUTTON_NEWGAME;
	DEBUG_ = false;
}


MainMenuState::~MainMenuState() {
	delete mainBackground_; mainBackground_ = nullptr;
	delete Taxi_; Taxi_ = nullptr;
	delete Taxi_anm; Taxi_anm = nullptr;
	delete Title_; Title_ = nullptr;
	delete Title_anm; Title_anm = nullptr;

	for (auto button : buttons_) {
		delete button.second; button.second = nullptr;
	}
	buttons_.clear();
}

void MainMenuState::start()
{
	s_ = Game::getInstance()->getSoundManager();
	int i; //recoge el valor del index si el elemento está en el vector
	if (!s_->isRegistered(this, i))
		s_->registerObserver(this);
	


	Game::getInstance()->getCamera(GAME_CAMERA)->setZoom(1.0, false);
	Game::getInstance()->getCamera(UI_CAMERA)->setZoom(1.0, false);


	//MAIN MENU TITLE
	setBackground ();

	//BUTTONS
	setButtons ();

	//build and set private components
	setComponents ();

	
	//Container to GameObj list
	stage_.push_back(mainBackground_);
	stage_.push_back(buttons_["newGameButton"]);
	stage_.push_back(buttons_["exitButton"]);
	stage_.push_back(Reticule::getInstance());
	stage_.push_back(Taxi_);
	stage_.push_back(Title_);

	//insert channels in map (max 8)
	Channels_.insert(std::pair<string, int>("Start", 1));

	//Play Sound start
	s_->playMusic(MAIN_THEME_MUSIC, -1); //MainTitle Theme
}

void MainMenuState::end()
{
	s_->removeObserver(this);
	s_ = nullptr;
}

void MainMenuState::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(false);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(false);

	GameState::update(deltaTime);
}

bool MainMenuState::receiveEvent(Event & e)
{
	switch (e.type_)
	{

	case CLICK_BUTTON: {
		MouseClickLeft  MouseClickLeft_ = static_cast<MouseClickLeft&>(e);

		if (MouseClickLeft_.button_ == buttons_["newGameButton"]->getIndex()) {
			buttons_["newGameButton"]->getButtonAnimacion()->playAnimation(NEW_GAME_BUTTON[clickButton].name, 24.0f, true);
			s_->pauseMusic();
			s_->stopSound(Channels_["Start"]);
			Game::getInstance()->setState(NAME_MAIN_STATE);
		}

		else if (MouseClickLeft_.button_ == buttons_["exitButton"]->getIndex())
			Game::getInstance()->setGameEnd();

		break;
	}
	case NOT_OVER_OBJECT: {
		NotMouseOverObj NotMouseOverObj_ = static_cast<NotMouseOverObj&>(e);

			if (NotMouseOverObj_.objIndex_ == buttons_["newGameButton"]->getIndex())
				buttons_["newGameButton"]->getButtonAnimacion()->stopAnimation();

			else if (NotMouseOverObj_.objIndex_ == buttons_["exitButton"]->getIndex())
				buttons_["exitButton"]->getButtonAnimacion()->stopAnimation();		
		break;
	}

	case OVER_OBJECT: {
		MouseOverObj MouseOverObj_ = static_cast<MouseOverObj&>(e);

		if (!s_->isSoundPlaying(Channels_["NG"])) {
			if (MouseOverObj_.objIndex_ == buttons_["newGameButton"]->getIndex())
				buttons_["newGameButton"]->getButtonAnimacion()->setAnimation(NEW_GAME_BUTTON[overButton].name);

			else if (MouseOverObj_.objIndex_ == buttons_["exitButton"]->getIndex())
				buttons_["exitButton"]->getButtonAnimacion()->setAnimation(EXIT_BUTTON[overButton].name);
		}

		break;
	}


	default:
		break;
	}
	return true;
}

void MainMenuState::setBackground () {
	mainBackground_ = new Container();
	mainBackground_->setPosition(Vector2D(MAIN_TITLE.pos.x, MAIN_TITLE.pos.y));
	mainBackground_->setWidth(Game::getInstance()->getCameraWidth());
	mainBackground_->setHeight(Game::getInstance()->getCameraHeight());
	//animation
	Animation* mainTitleAnm_ = new Animation();
	mainTitleAnm_->loadAnimation(MAIN_TITLE.idlePath, MAIN_TITLE.name, MAIN_TITLE.frAnm.cols, MAIN_TITLE.frAnm.rows);
	mainBackground_->addRenderComponent(mainTitleAnm_);
	mainTitleAnm_->setAnimation(MAIN_TITLE.name);
}

void MainMenuState::setButtons () {
	//build
	buttons_["newGameButton"] = new Button();
	buttons_["newGameButton"]->getMouseClickIC()->registerObserver(this);
	buttons_["exitButton"] = new Button();
	buttons_["exitButton"]->getMouseClickIC()->registerObserver(this);

	//set atributtes
	buttons_["newGameButton"]->setPosition(Vector2D(NEW_GAME_BUTTON[defaultAnm].pos.x, NEW_GAME_BUTTON[defaultAnm].pos.y));
	buttons_["newGameButton"]->setWidth(NEW_GAME_BUTTON[defaultAnm].width);
	buttons_["newGameButton"]->setHeight(NEW_GAME_BUTTON[defaultAnm].height);
	buttons_["newGameButton"]->setIndex(1);
	buttons_["exitButton"]->setPosition(Vector2D(EXIT_BUTTON[defaultAnm].pos.x, EXIT_BUTTON[defaultAnm].pos.y));
	buttons_["exitButton"]->setWidth(EXIT_BUTTON[defaultAnm].width);
	buttons_["exitButton"]->setHeight(EXIT_BUTTON[defaultAnm].height);
	buttons_["exitButton"]->setIndex(2);
}

void MainMenuState::setComponents () {
	//sounds
	soundId sound = CLIC_BUTTON_NEWGAME;
	buttons_["newGameButton"]->setClickSound(sound);
	buttons_["exitButton"]->setClickSound();
	//renderC - 
	Animation* newG_Animation = new Animation(); //NEW GAME BUTTON
			//first animation is the last to insert
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[clickButton].idlePath, NEW_GAME_BUTTON[clickButton].name, NEW_GAME_BUTTON[clickButton].frAnm.cols, NEW_GAME_BUTTON[clickButton].frAnm.rows);
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[overButton].idlePath, NEW_GAME_BUTTON[overButton].name, NEW_GAME_BUTTON[overButton].frAnm.cols, NEW_GAME_BUTTON[overButton].frAnm.rows);
	newG_Animation->loadAnimation(NEW_GAME_BUTTON[defaultAnm].idlePath, NEW_GAME_BUTTON[defaultAnm].name, NEW_GAME_BUTTON[defaultAnm].frAnm.cols, NEW_GAME_BUTTON[defaultAnm].frAnm.rows);
	//add and set renderC
	buttons_["newGameButton"]->addRenderComponent(newG_Animation);
	buttons_["newGameButton"]->setButtonAnimation(newG_Animation);
	buttons_["newGameButton"]->getButtonAnimacion()->setAnimation(NEW_GAME_BUTTON[defaultAnm].name);

	Animation* exitG_Animation = new Animation(); //EXIT BUTTON
		//first animation is the last to insert
	exitG_Animation->loadAnimation(EXIT_BUTTON[defaultAnm].idlePath, EXIT_BUTTON[defaultAnm].name, EXIT_BUTTON[defaultAnm].frAnm.cols, EXIT_BUTTON[defaultAnm].frAnm.rows);
	exitG_Animation->loadAnimation(EXIT_BUTTON[overButton].idlePath, EXIT_BUTTON[overButton].name, EXIT_BUTTON[overButton].frAnm.cols, EXIT_BUTTON[overButton].frAnm.rows);
	//add and set renderC
	buttons_["exitButton"]->addRenderComponent(exitG_Animation);
	buttons_["exitButton"]->setButtonAnimation(exitG_Animation);
	buttons_["exitButton"]->getButtonAnimacion()->setAnimation(NEW_GAME_BUTTON[defaultAnm].name);

	//Reticule
	Reticule::getInstance()->ChangeReticule("gun");

	//Taxi
	Taxi_ = new Container();
	Taxi_->setPosition(Vector2D(MAIN_TITLE_TAXI.pos.x, MAIN_TITLE_TAXI.pos.y));
	Taxi_->setWidth(MAIN_TITLE_TAXI.width);
	Taxi_->setHeight(MAIN_TITLE_TAXI.height);
	//animation
	Taxi_anm = new Animation();
	//taxAnm
	Taxi_anm->loadAnimation(MAIN_TITLE_TAXI_ANM.idlePath, MAIN_TITLE_TAXI_ANM.name, MAIN_TITLE_TAXI_ANM.frAnm.cols, MAIN_TITLE_TAXI_ANM.frAnm.rows);
	//default
	Taxi_anm->loadAnimation(MAIN_TITLE_TAXI.idlePath, MAIN_TITLE_TAXI.name, MAIN_TITLE_TAXI.frAnm.cols, MAIN_TITLE_TAXI.frAnm.rows);
	//add and set renderC
	Taxi_->addRenderComponent(Taxi_anm);
	Taxi_anm->setAnimation(MAIN_TITLE_TAXI.name);

	//Title
	Title_ = new Container();
	Title_->setPosition(Vector2D(MAIN_TITLE_TITLE.pos.x, MAIN_TITLE_TITLE.pos.y));
	Title_->setWidth(MAIN_TITLE_TITLE.width);
	Title_->setHeight(MAIN_TITLE_TITLE.height);
	//animation
	Title_anm = new Animation();
	//taxAnm
	Title_anm->loadAnimation(MAIN_TITLE_TITLE.idlePath, MAIN_TITLE_TITLE.name, MAIN_TITLE_TITLE.frAnm.cols, MAIN_TITLE_TITLE.frAnm.rows);
	//add and set renderC
	Title_->addRenderComponent(Title_anm);
	Title_anm->setAnimation(MAIN_TITLE_TITLE.name);
}
