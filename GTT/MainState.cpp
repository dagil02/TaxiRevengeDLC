#include "MainState.h"

#include "Turret.h"
#include "ReloadingDisplay.h"
#include "AmmoDisplay.h"

//singleton
#include "Vehicle.h"
#include "ProyectilePool.h"
#include "Reticule.h"
#include "NodeMapsManager.h"
#include "EnemyManager.h"
#include "GameManager.h"
#include "ShopManager.h"

MainState::MainState(){}

MainState::~MainState() {
	delete tilemap_; tilemap_ = nullptr;
	delete cameraFollow_; cameraFollow_ = nullptr;
}

//start is called when GameStateMachine change state
void MainState::start() {
	// Taxi	
	Vehicle::getInstance()->initAtributtes(THECOOLERTAXI, DEFAULT_KEYS);
	Vehicle::getInstance()->EquipTurret(new Turret(GUN));

	// Tilemap
	tilemap_ = new TileMap(PATH_LEVEL_1);

	NodeMapsManager::getInstance()->ReadNodeMapsInfo();
	EnemyManager::getInstance()->ReadEnemyInfo();

	//Reticule
	Reticule::getInstance()->setPosition(Vehicle::getInstance()->getPosition());

	//Camera logic
	cameraFollow_ = new FollowMiddlePoint(Vehicle::getInstance(), Reticule::getInstance(), GAME_CAMERA, UI_CAMERA, 0.7, 0.25);
	Game::getInstance()->getCamera(GAME_CAMERA)->addLogicComponent(cameraFollow_);

	// Camera positionin
	Vector2D cameraPos = Vehicle::getInstance()->getPosition();
	cameraPos -= Vector2D(Game::getInstance()->getCamera(GAME_CAMERA)->getWidth() / 2,
		Game::getInstance()->getCamera(GAME_CAMERA)->getHeight() / 2);
	Game::getInstance()->getCamera(GAME_CAMERA)->setPosition(cameraPos);
	
	// UI
	
	Vehicle::getInstance()->getHealthComponent()->registerObserver(UI::getInstance());

	//pushBack GameObj to list
	stage_.push_back(tilemap_);
	stage_.push_back(Vehicle::getInstance());
	stage_.push_back(EnemyManager::getInstance());
	stage_.push_back(GameManager::getInstance());
	stage_.push_back(ShopManager::getInstance());

	stage_.push_back(UI::getInstance());
	stage_.push_back(ProyectilePool::getInstance());
	stage_.push_back(Reticule::getInstance());

	GameManager::getInstance()->setEnemyCount(EnemyManager::getInstance()->GetEnemyCount());

	 stage_.push_back(new DamageUpgrade(50, 50, 194 * 32, 123 * 32));
	 stage_.push_back(new DamageUpgrade(50, 50, 82 * 32, 108 * 32));
	 stage_.push_back(new DamageUpgrade(50, 50, 103 * 32, 57 * 32));
	 stage_.push_back(new DamageUpgrade(50, 50, 160 * 32, 70 * 32));
	 stage_.push_back(new SpeedUpgrade(50, 50, 102 * 32, 109 * 32));
	 stage_.push_back(new SpeedUpgrade(50, 50, 221 * 32, 116 * 32));
	 stage_.push_back(new SpeedUpgrade(50, 50, 103 * 32, 93 * 32));
	 stage_.push_back(new SpeedUpgrade(50, 50, 40 * 32, 98 * 32));
	 stage_.push_back(new FuelUpgrade(50, 50, 66 * 32, 116 * 32));
	 stage_.push_back(new FuelUpgrade(50, 50, 30 * 32, 95 * 32));
	 stage_.push_back(new FuelUpgrade(50, 50, 81 * 32, 55 * 32));
	 stage_.push_back(new FuelUpgrade(50, 50, 213 * 32, 121 * 32)); 
}

void MainState::end()
{
	EnemyManager::getInstance()->deactivateIA();
}


void MainState::update(Uint32 deltaTime) {
	Game::getInstance()->getCamera(GAME_CAMERA)->setCentered(true);
	Game::getInstance()->getCamera(UI_CAMERA)->setCentered(true); 
	GameState::update(deltaTime);
}


