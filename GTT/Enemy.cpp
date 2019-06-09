#include "Enemy.h"
#include "Reticule.h"
#include "Vehicle.h"
#include "Turret.h"
#include "EnemyAim.h"
#include "SoundManager.h"
#include "GameManager.h"
#include "TaxiSoundManagerCP.h"
#include "Money.h"


Enemy::Enemy(VehicleInfo r, NodeMap* nmap, vector<Node*> route, Vector2D pos, WeaponInfo weapon){
	this->setWidth(r.width);
	this->setHeight(r.height);

	position_ = pos;

	zombie_ = false; 
	alive_ = true;
	bodyReadyToDestroy_ = false;


	// Sprite
	sprite_ = new Animation();
	sprite_->loadAnimation(r.idlePath, "default");
	sprite_->loadAnimation(r.diePath, "enemyDie", 4, 2);
	sprite_->loadAnimation(r.impDamagePath, "hitDamage", 3); //las filas y columnas tienen que pasar por const Globales
	sprite_->setAnimation("default");
	//sprite_->playAnimation("enemyDie", 24.0f, true);

	this->addRenderComponent(sprite_);

	// Health
	health_ = new Health(r.HP);
	addLogicComponent(health_);

	//Movement
	speed_ = r.AIspeed;

	//Reward
	reward_ = r.reward;

	// Physics
	phyO_ = new PhysicObject(b2_kinematicBody, width_, height_, position_.x, position_.y);
	phyO_->setCollisions(0, ENEMY_CATEGORY);
	phyO_->getBody()->SetUserData(this);
	addLogicComponent(phyO_);

	//IA
	pursuitRange_ = r.pursuitRange;
	follow_ = new IAFollow(GetPhyO(), this, nmap, speed_);
	patrol_ = new IApatrol(GetPhyO(), this, nmap, speed_, route);
	addLogicComponent(patrol_);
	followmode_ = false;

	turret_ = new Turret(weapon);
	turret_->AttachToVehicle(this);
}

Enemy::~Enemy() {
	delete follow_; follow_ = nullptr;
	delete patrol_; patrol_ = nullptr;
	delete turret_; turret_ = nullptr;
}


void Enemy::Damage(double damage)
{
	health_->damage(damage);
	sprite_->playAnimation("hitDamage", 30.0f, false);
	if (health_->getHealth() <= 0 && !bodyReadyToDestroy_) { 
		GameManager::getInstance()->addKill();
		GameManager::getInstance()->decreaseEnemyCount();
		SoundManager::getInstance()->playSound_Ch(0, ENEMY_DIE, 0); //channel 0 for not interrupt other sounds
		//Send reward
		Money::getInstance()->addMoney(reward_);
		//Heal Player
		Vehicle::getInstance()->getHealthComponent()->heal(health_->getMaxHealth()*0.5);

		sprite_->playAnimation("enemyDie", 10.0f, false);
		bodyReadyToDestroy_ = true;
		turret_->setActive(false);
		turret_->setActive(false);
		zombie_ = true; //lanza el flag para que en el update se desactiven la l�gica de patruya
	}
}

void Enemy::Die()
{	
	setActive(false);
}

void Enemy::update(Uint32 deltaTime)
{
	if (active_) {
		if (bodyReadyToDestroy_) {
			delLogicComponent(phyO_);
			delete phyO_;
			phyO_ = nullptr;
		}


		if (!zombie_) {
			
				if (followmode_ != taxiOnRange()) {
					followmode_ = !followmode_;
					if (followmode_) {
						delLogicComponent(patrol_);
						addLogicComponent(follow_);
						follow_->Restart();
					}
					else {
						delLogicComponent(follow_);
						addLogicComponent(patrol_);
						patrol_->Restart();
					}
				}
				//Aim
				if (taxiOnRange()) {
					double disX = Vehicle::getInstance()->getCenter().x - getCenter().x;
					double disY = Vehicle::getInstance()->getCenter().y - getCenter().y;
					double degrees = acos(-disY / (sqrt(pow(disX, 2) + pow(disY, 2))));

					turret_->setRotation(degrees * 180.0 / M_PI);
					if (disX < 0)
						turret_->setRotation(-turret_->getRotation());
				}
				
			Car::update(deltaTime);
			if (turret_ != nullptr) {
				turret_->update(deltaTime);
			}
		}

		if (!sprite_->isAnimationPlaying("enemyDie") && zombie_) { 
			alive_ = false; 
		}

		if (!alive_) {
			Die();
		}

	}
}

void Enemy::render(Uint32 deltaTime)
{
	Car::render(deltaTime);

	if (turret_ != nullptr) {
		turret_->render(deltaTime);
	}
}

int Enemy::getDistanceFromTaxi()
{
	return (Vehicle::getInstance()->getCenter() - getCenter()).Length();
}

Turret * Enemy::getTurret()
{
	return turret_;
}

bool Enemy::taxiOnRange()
{
	return getDistanceFromTaxi()<=pursuitRange_;
}

IAMovementBehaviour * Enemy::getIABehaviour()
{
	if (followmode_)
		return follow_;
	return patrol_;
}
