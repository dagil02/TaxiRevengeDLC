#include "Vehicle.h"

#include "AimAtCursorAC.h"
#include "Reticule.h"
#include "InputMovement.h"

#include "Turret.h"
#include "ReloadInputComponent.h"
#include "ShootIC.h"
#include "GameManager.h"

#include "EnemyManager.h"

unique_ptr<Vehicle> Vehicle::instance_ = nullptr;

Vehicle::Vehicle() {
	currentTurret_ = 0;
	zombie_ = false; 
	//alive_ = true;
}

Vehicle::~Vehicle() {
	delete shIC_; shIC_ = nullptr;
	delete control_; control_ = nullptr;
	delete shopIC_; shopIC_ = nullptr;
	delete smLC_; smLC_ = nullptr;
	delete reIC_; reIC_ = nullptr;
	delete changeWeaponIC_; changeWeaponIC_ = nullptr;

	for (int i = 0; i < MAXTURRETS; i++) {
		if (turrets_[i] != nullptr) {
			delete turrets_[i];
			turrets_[i] = nullptr;
		}
	}
}


ReloadInputComponent * Vehicle::GetReloadIC()
{
	return reIC_;
}

ShootIC * Vehicle::GetShootIC()
{
	return shIC_;
}



void Vehicle::EquipTurret(Turret * turret)
{
	turrets_[1] = turrets_[0];
	turrets_[0] = turret;
	turrets_[0]->AttachToVehicle(this);
	turrets_[0]->registerObserver(smLC_); //register for capture events_Type in TaxiSoundManagerCP

	/*int i = 0;
	while (i < MAXTURRETS && turrets_[i] != nullptr)
		i++;
	if (i < MAXTURRETS) {
		currentTurret_ = i;
		turrets_[currentTurret_] = turret;
		Reticule::getInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
		turrets_[currentTurret_]->AttachToVehicle(this);
		turrets_[currentTurret_]->registerObserver(smLC_); //register for capture events_Type in TaxiSoundManagerCP
	}
	else {
		delete turrets_[0];
		turrets_[0] = nullptr;
		EquipTurret(turret);
	}*/

}

void Vehicle::ChangeTurret()
{
	turrets_[currentTurret_]->CancelReload();
	currentTurret_ = (currentTurret_ + 1) % MAXTURRETS;
	while (turrets_[currentTurret_] == nullptr) {
		currentTurret_ = (currentTurret_ + 1) % MAXTURRETS;
	}
	Reticule::getInstance()->ChangeReticule(turrets_[currentTurret_]->GetReticule());
	shIC_->ChangeInputMode(turrets_[currentTurret_]->isAutomatic());
	turrets_[currentTurret_]->ResetChargeProgress();
}

Turret * Vehicle::getCurrentTurret()
{
	return turrets_[currentTurret_];
}

void Vehicle::DamageBost(int t)
{
	turrets_[currentTurret_]->upgradeShoot(t);
}

void Vehicle::SpeedBost()
{
	acceleration_ += 10;
}

void Vehicle::handleInput(Uint32 time, const SDL_Event & event)
{
	Container::handleInput(time, event);
	if(turrets_[currentTurret_]!=nullptr) turrets_[currentTurret_]->handleInput(time, event);
}

void Vehicle::update(Uint32 time) {
	Container::update(time);
	
	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->update(time);

	if (alive_ && health_->getHealth() <= 0) {
		//zombie_ = true; //estable el flag
		alive_ = false;
		deathTime_ = SDL_GetTicks();
	}
	if (!alive_ && SDL_GetTicks() - deathTime_ >= 500) {
		Respawn();
	}
	if (acceleration_ > 0.8f) acceleration_ -= 0.2f;
}

bool Vehicle::receiveEvent(Event & e) {

	switch (e.type_)
	{
	case STARTED_MOVING_FORWARD:
		health_->setDamageOverTime(DMG_OVER_TIME_MOVING, DMG_FREQUENCY);
		break;

	case STOPPED_BACK_MOVING_FORWARD:
		health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
		break;

	case TURN_LEFT:
		if (!sprite_->isAnimationPlaying("hitDamage"))
			sprite_->setAnimation("leftTurn");
		break;

	case TURN_RIGHT:
		if (!sprite_->isAnimationPlaying("hitDamage"))
			sprite_->setAnimation("rightTurn");
		break;

	case TURN_DEFAULT:
		if (!sprite_->isAnimationPlaying("hitDamage"))
			sprite_->setAnimation("default");
		break;

	case STOP_BACKFORWARD:
		if(!sprite_->isAnimationPlaying("hitDamage"))
			sprite_->setAnimation("backStop");
		break;

	case IMPACT_DAMAGE:
		sprite_->playAnimation("hitDamage", 30.0f, false); //play establece anim como currentAnm y al renderizar secciona por frames
		//como loop es false vuelve a la animaci�n por defecto
		Event eV(this, IMPACT_DAMAGE);
		broadcastEvent(eV); //TaxiSoundManager recieved this message
		break;

	}

	return true;
}

void Vehicle::SaveSpawnPoint(Vector2D spawn)
{
	spawnPosition_ = spawn;
}

void Vehicle::Respawn()
{
	GameManager::getInstance()->calculatePuntuation();
	Vehicle::getInstance()->setPosition(spawnPosition_);
	Vector2D v = spawnPosition_;
	Vehicle::getInstance()->GetPhyO()->getBody()->SetTransform(spawnPosition_.Multiply(PHYSICS_SCALING_FACTOR), 0);
	spawnPosition_ = v;
	health_->resetHealth();
	alive_ = true;
}


void Vehicle::render(Uint32 time) {
	Container::render(time);

	if (turrets_[currentTurret_] != nullptr)
		turrets_[currentTurret_]->render(time);
}


float32 Vehicle::GetMaxBackwardSpeed()
{
	return maxBackwardSpeed_;
}

float32 Vehicle::GetAcceleration()
{
	return acceleration_;
}

Vector2D Vehicle::getSpawnPosition () {
	return spawnPosition_;
}


void Vehicle::initAtributtes(VehicleInfo r, KeysScheme k)
{
	this->setWidth(r.width);
	this->setHeight(r.height);

	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "default");
	sprite_->loadAnimation(r.leftTurnPath, "leftTurn");
	sprite_->loadAnimation(r.rightTurnPath, "rightTurn"); 
	sprite_->loadAnimation(r.backTurnPath, "backStop");
	sprite_->loadAnimation(r.impDamagePath, "hitDamage", 4, 3); //las filas y columnas tienen que pasar por const Globales

	this->addRenderComponent(sprite_);
	sprite_->setAnimation("default");

	// Health
	health_ = new Health(r.HP);
	health_->setDamageOverTime(DMG_OVER_TIME, DMG_FREQUENCY);
	addLogicComponent(health_);
	alive_ = true;


	shIC_ = new ShootIC();
	reIC_ = new ReloadInputComponent();
	aimC_ = new AimAtCursorAC();
	changeWeaponIC_ = new ChangeWeaponIC();
	addInputComponent(changeWeaponIC_);


	// Movement
	this->maxSpeed_ = r.velMax;
	this->maxBackwardSpeed_ = r.velBackwardMax;
	this->turnSpeed_ = r.turnSpeed;
	this->acceleration_ = r.acceleration;
	this->normalAcceleration_ = this->acceleration_;

	// Physics
	phyO_ = new PhysicObject(b2_dynamicBody, r.width, r.height, position_.x, position_.y);
	phyO_->setCollisions(0, TAXI_CATEGORY);
	this->addLogicComponent(phyO_);

	// Control
	control_ = new InputMovement(k, this);
	this->addInputComponent(control_);
	this->addLogicComponent(control_);
	control_->registerObserver(this);

	// Shop control
	shopIC_ = new EnterShopIC ();
	this->addInputComponent (shopIC_);

	//Sound
	smLC_ = new TaxiSoundManagerCP(this);
	this->addLogicComponent(smLC_);
	this->registerObserver(smLC_); //taxi es tambi�n un observable.  enviar� los mensajes correspondientes a su comp TaxiSoundManagerCP

	control_->registerObserver(smLC_);

	//turrets
	for (int i = 0; i < MAXTURRETS; i++) {
		turrets_[i] = nullptr;
	}
}