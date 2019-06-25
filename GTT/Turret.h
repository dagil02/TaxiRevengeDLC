#pragma once
#include "Container.h"
#include"FollowGameObject.h"
#include "Vehicle.h"
#include "ProyectilePool.h"
#include <stack>
#include "Observable.h"
#include "EnemyShoot.h"

class Animation;
class ShootComponent;
class AimComponent;


//clase abstracta, padre de los diferentes tipos de torreta
class Turret : public Container, public Observable
{
public:
	Turret(WeaponInfo w);
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);
	virtual void AttachToVehicle(Car* car);
	virtual void Shoot();
	virtual void AIShoot();
	virtual void Reload();
	virtual void PerfectReload();
	virtual void CancelReload();
	virtual void InitiateReload();
	virtual void upgradeShoot();
	virtual int GetCadence();
	virtual int GetAmmo();
	virtual int GetMaxAmmo();
	virtual double GetReloadPercentage();
	virtual double GetPerfReloadSeg();
	virtual double GetPerfReloadIni();
	virtual void ResetChargeProgress();
	virtual string GetReticule();
	virtual bool isReloading();
	virtual bool isAutomatic();
	virtual ~Turret();

	virtual int getCrrActionShoot();





protected:
	vector<double> magazine_;//cargador representado como una pila
	double animSpeed_;
	int maxAmmo_;//capacidad del cargador
	int cadence_;//cadencia de disparo
	int reloadTime_;//tiempo de recarga al vaciar el cargador
	int reloadpressedTime_;//momento en el que se pulso el boton de recarga
	int lastTimeShot_;//momento en el que se disparo la ultima bala
	int chargeTime_;//tiempo que tarda en cargar una bala mas potente
	int chargeprogress_;//tiempo desde que se dejo de usar la torreta (recargar o disparar)
	double perfRelSeg_;//segmento del tiempo de recarga en el que entra en accion la recarga perfecta (en tanto por 1)
	double perfRelIni_;//momento dentro del tiempo de recarga en el que empieza el segmento de recarga perfecta (en tanto por 1)
	bool reloading_;//indica si se esta recargando en el momento
	bool boostTime_;//indica si el jugador se encuentra en el momento de la mejora de disparo
	bool charged_;//indica si esta cargado el disparo
	bool automatic_;//indica si la torreta es de disparo automatico
	int chargedShotDelay_;//tiempo de espera añadido a la cadencia para poder disparar otra bala tras un disparo cargado
	string path_;//direccion del sprite de la torreta
	string animationpath_;
	string reticulesprite_="";
	ShootComponent* shC_;//codigo de disparo (en que forma dispara)
	ShootComponent* SPshC_;//codigo de disparo (disparo cargado)
	FollowGameObject* followC_;
	Animation* animC_;
	Car* car_;//coche al que esta pegada la torreta

	ProyectileInfo normalB;
	int defaultNormalDMG_;
	ProyectileInfo specialB;
	int defaultSpecialDMG_;
	int crr_ActionShoot_; //sound management in ShootIC

	FollowGameObject *followObject_;
	Container sparkleEffect_;
	Animation* sparkleanim_;
	Container shotEffect_;
	Animation* shotanim_;
	EnemyShoot *enemyShoot_;

};

