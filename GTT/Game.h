#pragma once
#include "SDL.h"
#include <Box2D/Box2D.h>
#include "CameraType.h"
#include "Camera.h"
#include "SoundManager.h"
#include "GameStateMachine.h"
#include "CustomContactListener.h"
#include "Animation.h"
#include "Container.h"

using namespace std;
typedef unsigned int uint;

class Game {

	//hide copyBuilder and 	assignment operator
	Game(Game&) = delete;
	Game& operator=(const Game&) = delete;

	static unique_ptr<Game> instance_; //ptr instance class


public:

	//Builder
	Game();
	virtual ~Game();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new Game());
		}
	}
	//get singleton class
	inline static Game* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}


	void run();
	bool exitGame();


	//main methods
	void handleEvents(Uint32 deltaTime);
	void update(Uint32 deltaTime);
	void render(Uint32 deltaTime);

	//get Game SDL attributes
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

	int getWindowWidth();
	int getWindowHeight();
	int getCameraHeight();
	int getCameraWidth();

	//get Game private attributes
	b2World* getWorld();
	SoundManager* getSoundManager();
	Camera* getCamera(cameraType cT);
	GameStateMachine* getGameStateMachine();
	bool getCloseToShop () { return canEnterShop_; }

	// state setters
	void setState(string state);
	void setGameEnd () { exit_ = true; }
	void setCloseToShop (bool close) { canEnterShop_ = close; }

	//pausa
	bool getPause() { return pause; }

	void init();

private:
	void end();

	int winWidth_ = WIN_WIDTH;
	int winHeight_ = WIN_HEIGHT;

	const int cameraWidth = CAMERA_WIDHT;
	const int cameraHeight = CAMERA_HEIGHT;

	//SDL Elements
	SDL_Renderer *renderer_;
	SDL_Window *window_;

	//Phsysics
	b2World* world_;

	//Media
	map<cameraType, Camera*> cameras_;

	//states
	GameStateMachine* gmStMachine_;
	bool exit_ = false;
	bool canEnterShop_ = false;

	// Delta time and physics time management
	double accumulator_;
	double step_ = 1.0f / 60.0f;
	int velIterations_ = 8, posIterations_ = 3;

	//pausa
	bool pause;
};