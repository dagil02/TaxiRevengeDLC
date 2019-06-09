#include "Proyectile.h"
#include "Vehicle.h"
#include "BounceImC.h"
#include "ExplosiveImC.h"
#include "ImpactComponent.h"


b2Filter Proyectile::colFilter = b2Filter();

Proyectile::Proyectile():Trigger(0,0,0,0)
{
	delLogicComponent(phyO_);
	delete phyO_;
	phyO_ = nullptr;

	bodyReadyToDestroy_ = false;
	zombie_ = false;
	setActive(false);
	colFilter.groupIndex = BULLETS_GROUP;
}

Proyectile::~Proyectile(){
	if (phyO_ != nullptr) delete phyO_, phyO_ = nullptr;
	if (animC_ != nullptr) delete animC_, animC_ = nullptr;
	if (impC_ != nullptr) delete impC_, impC_ = nullptr;
}

void Proyectile::SetBirth(double birthTime)
{
	birthTime_ = birthTime;
}


void Proyectile::update(Uint32 time)
{
	if (SDL_GetTicks() - birthTime_ >= lifeTime_) {
		DeactivateBullet();
	}
	if (bodyReadyToDestroy_ && !zombie_) {
		delLogicComponent(phyO_);
		delete phyO_;
		phyO_ = nullptr;
		zombie_ = true;
		animC_->playAnimation("collision", 10.0f, false);
	}
	if (zombie_ && !animC_->isAnimationPlaying("collision"))
		setActive(false);
	Container::update(time);
}

void Proyectile::render(Uint32 time)
{
	Trigger::render(time);
}

void Proyectile::ChangeBulletType(ProyectileInfo p, bool isAnEnemy)
{
	if (phyO_ != nullptr) {
		delLogicComponent(phyO_);
		delete phyO_;
		phyO_ = nullptr;
	}
	if (animC_ != nullptr) {
		delRenderComponent(animC_);
		delete animC_;
		animC_ = nullptr;
	}
	if (impC_ != nullptr) {
		delete impC_;
		impC_ = nullptr;
	}

	bodyReadyToDestroy_ = false;
	zombie_ = false;
	width_ = p.width;
	height_ = p.height;
	speed_ = p.speed;
	lifeTime_ = p.lifeTime;
	damage_ = p.damage;

	animC_ = new Animation();

	addRenderComponent(animC_);
	animC_->loadAnimation(p.idlePath, "default");
	animC_->loadAnimation(p.destructionPath, "collision", p.destranimframes);
	animC_->playAnimation("default");

	phyO_ = new PhysicObject(b2_dynamicBody, width_, height_, position_.x, position_.y);

	if(!isAnEnemy)
	phyO_->setCollisions(BULLETS_GROUP, BULLET_CATEGORY, ~(~0xFFFF | TAXI_CATEGORY) );
	else
		phyO_->setCollisions(BULLETS_GROUP, BULLET_CATEGORY, ~(~0xFFFF | ENEMY_CATEGORY));
	phyO_->getBody()->GetFixtureList()->SetRestitution(1.0f);
	isAnEnemy_ = isAnEnemy;

	switch (p.imp) {
	case STANDARD:
		phyO_->getBody()->GetFixtureList()->SetSensor(true);
		impC_ = new ImpactComponent(this);
		break;
	case BOUNCE:
		impC_ = new BounceImC(this);
		break;
	case EXPLOSIVE:
		phyO_->getBody()->GetFixtureList()->SetSensor(true);
		impC_ = new ExplosiveImC(this);
		break;
	default:
		break;
	}
	addLogicComponent(phyO_);
}

void Proyectile::beginCallback(b2Contact * contact)
{
	if(contact!=nullptr)
		if (this != nullptr)
			if (impC_ != nullptr)
				impC_->Impact(contact);
}

void Proyectile::endCallback(b2Contact * contact)
{

}

PhysicObject * Proyectile::GetPhyO()
{
	return phyO_;
}

double Proyectile::GetDamage()
{
	return damage_;
}

double Proyectile::GetSpeed()
{
	return speed_;
}

void Proyectile::DeactivateBullet()
{
	bodyReadyToDestroy_ = true;
}

bool Proyectile::isAnEnemy()
{
	return isAnEnemy_;
}

