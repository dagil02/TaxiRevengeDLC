#include "TaxiSoundManagerCP.h"
#include "Game.h"
#include "SoundManager.h"
#include "Car.h"


TaxiSoundManagerCP::TaxiSoundManagerCP(Car * v)
{
	//ptr and registrer observer
	v_ = v;
	s_ = Game::getInstance()->getSoundManager();
	s_->registerObserver(this);

	DEBUG_ = false; //write in console var values

	//edit default var values
	Channels_.insert(std::pair<string, int>("Start", 1));
	Channels_.insert(std::pair<string, int>("Regular", 2));
	Channels_.insert(std::pair<string, int>("Aceleration", 3));
	Channels_.insert(std::pair<string, int>("Deceleration", 4));
	Channels_.insert(std::pair<string, int>("Fast", 5));
	Channels_.insert(std::pair<string, int>("BackForward", 6));
	Channels_.insert(std::pair<string, int>("shoot", 7)); //all shoots
	Channels_.insert(std::pair<string, int>("damage", 0)); //impact Damage


	ch_3KeyDown = ch_3KeyUp = ch_5KeyUp = ch_6_KeyDown = ch_6_KeyUp = keyBackDown_ = false;

	ch_2_Vol_ = VOL_CHANNEL_2;
	ch_3_Vol_ = VOL_CHANNEL_3;
	ch_6_Vol_ = VOL_CHANNEL_6;

	//init SoundManager
	start();

}

void TaxiSoundManagerCP::start()
{
	//play first sound
	if (s_ != nullptr)
	{
		s_->playSound_Ch(Channels_["Start"], TAXI_START, 0);
		cout << "Play start sound" << endl;
	}
}

void TaxiSoundManagerCP::update(GameObject * o, Uint32 deltaTime)
{

	//Stop Sounds Management
	//if have considerable velocity and Taxi_acelerate is playing
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() >= v_->GetMaxSpeed() && (s_->isSoundPlaying(Channels_["Aceleration"]))) {
		s_->stopSound(Channels_["Aceleration"]);
		if (DEBUG_)
			cout << "Vel. Max. Aceleration: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;

	}
	//if velocity is slow and deceleration is playing
	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < (v_->GetMaxSpeed() * POR_VEL_MIN_) && (s_->isSoundPlaying(Channels_["Deceleration"]))) {
		s_->stopSound(Channels_["Deceleration"]);

		if (DEBUG_)
			cout << "Vel.Min.Aceleration: " << v_->GetPhyO()->getBody()->GetLinearVelocity().Length() << endl;
	}
	//is velocity is fast and backForward is playing and forward keyUp is true
	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() <= (v_->GetMaxSpeed() * POR_VEL_MIN_2_) && (s_->isSoundPlaying(Channels_["BackForward"])) && !keyBackDown_) {
		keyBackDown_ = false;
		s_->stopSound(Channels_["BackForward"]);
	}


	//----------------------------------------------------//

	//Volume Management
	//increase the volume of the acceleration until max aceleration velocity
	if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() < (v_->GetMaxSpeed() * POR_VEL_MIN_) && (s_->isSoundPlaying(Channels_["Aceleration"]))) {

		if (ch_3_Vol_ < s_->getMIX_MAX_VOLUME()) {
			ch_3_Vol_ += 4;
			s_->setVolumeSound(Channels_["Aceleration"], ch_3_Vol_);
		}
		if (DEBUG_)
			cout << "Volume of " << Channels_["Aceleration"] << ": " << ch_3_Vol_ << endl;
	}
	else if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() > (v_->GetMaxSpeed() * POR_VEL_MIN_2_) && (s_->isSoundPlaying(Channels_["Deceleration"]))) {
		if (ch_4_Vol_ >= 20) {
			ch_4_Vol_ -= 6;
			s_->setVolumeSound(Channels_["Deceleration"], ch_4_Vol_);
		}
		if (DEBUG_)
			cout << "Volume of " << Channels_["Deceleration"] << ": " << ch_4_Vol_ << endl;
	}
	else if ((s_->isSoundPlaying(Channels_["BackForward"]))) {
		if (ch_6_Vol_ < s_->getMIX_MAX_VOLUME()) {
			ch_6_Vol_ += 10;
			s_->setVolumeSound(Channels_["BackForward"], ch_6_Vol_);
		}
	}

}

bool TaxiSoundManagerCP::receiveEvent(Event & e)
{
	switch (e.type_)
	{

	case IMPACT_DAMAGE:
		s_->playSound_Ch(Channels_["damage"], TAXI_IMPACT_DAMAGE, 0);
		break;


	case STARTED_MOVING_FORWARD: {

		if (!(s_->isSoundPlaying(Channels_["Aceleration"])))
		{
			ch_3KeyDown = true;

			if (s_->isSoundPlaying(Channels_["Regular"]))
				s_->stopSound(Channels_["Regular"]); //stop regular engine sound

			else if (s_->isSoundPlaying(Channels_["Deceleration"]))
				s_->stopSound(Channels_["Deceleration"]); //stop regular engine sound	

			else if (s_->isSoundPlaying(Channels_["BackForward"]))
				s_->stopSound(Channels_["BackForward"]); //stop backforward sound
		}
		break;
	}


								 //----------------------------------------------------//

	case STOPPED_MOVING_FORWARD: {
		if (s_->isSoundPlaying(Channels_["Aceleration"])) {
			ch_3KeyUp = true;
			ch_3KeyDown = false;
			s_->stopSound(Channels_["Aceleration"]);
		}

		else if (s_->isSoundPlaying(Channels_["Fast"])) {
			ch_5KeyUp = true;
			s_->stopSound(Channels_["Fast"]);
		}
		break;
	}


								 //----------------------------------------------------//

	case BACK_MOVING_FORWARD: {
		keyBackDown_ = true;

		//cuando se pulsa freno y que suene Frenada, puede estar sonando: aceleracion, maxVelEngine, Deceleration
		if (!(s_->isSoundPlaying(Channels_["BackForward"]))) {
			ch_6_KeyDown = true;

			if (s_->isSoundPlaying(Channels_["Aceleration"])) {
				s_->stopSound(Channels_["Aceleration"]);
			}

			else if (s_->isSoundPlaying(Channels_["Deceleration"])) {
				s_->stopSound(Channels_["Deceleration"]);
			}

			else if (s_->isSoundPlaying(Channels_["Fast"])) {
				s_->stopSound(Channels_["Fast"]);
			}

			else
				ch_6_KeyDown = false;
		}
		break;
	}


							  //----------------------------------------------------//

	case STOPPED_BACK_MOVING_FORWARD: {
		keyBackDown_ = false;
		break;
	}
	


									  //callback receive from SoundManager when channel is stopped
	case CHANNEL_STOPPED_PLAYING: {
		ChannelStoppedPlaying channelEvent = static_cast<ChannelStoppedPlaying&>(e);
		if (DEBUG_)
			cout << "Channel " << channelEvent.channel_ << " stopped playing." << endl;

		//channel 1 = start car sound
		if (channelEvent.channel_ == 1) {
			s_->playSound_Ch(Channels_["Regular"], TAXI_IDLE, -1);
			s_->setVolumeSound(Channels_["Regular"], ch_2_Vol_);
		}

		//channel 2 = regular engine sound
		else if (channelEvent.channel_ == 2) {
			s_->playSound_Ch(Channels_["Aceleration"], TAXI_ACCELERATE_01, -1); //play engine aceleration sound
			s_->setVolumeSound(Channels_["Aceleration"], ch_3_Vol_);
			ch_3KeyDown = false;
		}

		//channel 3 = engine aceleration 
		else if (channelEvent.channel_ == 3) {
			if (ch_3KeyUp) {
				//deceleration sound
				if (v_->GetPhyO()->getBody()->GetLinearVelocity().Length() >= (v_->GetMaxSpeed() * POR_VEL_MIN_3_))
				{
					s_->playSound_Ch(Channels_["Deceleration"], TAXI_DECELERATE_10, -1);
					ch_4_Vol_ = ch_3_Vol_; //recoge el valor del estado de aceleraci�n actual
					s_->setVolumeSound(Channels_["Deceleration"], ch_4_Vol_);
				}
				//regular engine sound
				else {
					s_->playSound_Ch(Channels_["Regular"], TAXI_IDLE, -1);
					s_->setVolumeSound(Channels_["Regular"], ch_2_Vol_);
				}
				//reset default var values
				ch_3KeyUp = false;
				ch_3_Vol_ = 68; //el valor por defecto que ponerlo como sonst global
			}
			//BackForward
			else if (ch_6_KeyDown) {
				s_->playSound_Ch(Channels_["BackForward"], TAXI_BACK_MOVING_FORWARD, 0);
				s_->setVolumeSound(Channels_["BackForward"], ch_6_Vol_);
				ch_6_KeyDown = false;
			}
			//max speed
			else {
				s_->playSound_Ch(Channels_["Fast"], TAXI_FASTDRIVE, -1);
				s_->setVolumeSound(Channels_["Fast"], s_->getMIX_MAX_VOLUME());
			}
		}

		//channel 4 = engine decelerate 
		else if (channelEvent.channel_ == 4) {
			if (ch_3KeyDown) {
				s_->playSound_Ch(Channels_["Aceleration"], TAXI_ACCELERATE_01, -1); //play engine aceleration sound
				s_->setVolumeSound(Channels_["Aceleration"], ch_3_Vol_);
				ch_3KeyDown = false;
			}

			else if (ch_6_KeyDown) {
				s_->playSound_Ch(Channels_["BackForward"], TAXI_BACK_MOVING_FORWARD, 0);
				s_->setVolumeSound(Channels_["BackForward"], ch_6_Vol_);
				ch_6_KeyDown = false;
			}

			else {
				s_->playSound_Ch(Channels_["Regular"], TAXI_IDLE, -1);
				s_->setVolumeSound(Channels_["Regular"], ch_2_Vol_);
			}

		}

		else if (channelEvent.channel_ == 5) {
			if (ch_5KeyUp) {
				ch_3KeyDown = false;
				s_->playSound_Ch(Channels_["Deceleration"], TAXI_DECELERATE_10, -1);
				ch_4_Vol_ = s_->getMIX_MAX_VOLUME(); //recoge el valor del estado de aceleraci�n actual
				s_->setVolumeSound(Channels_["Deceleration"], ch_4_Vol_);
				ch_5KeyUp = false;
			}
			else if (ch_6_KeyDown) {
				s_->playSound_Ch(Channels_["BackForward"], TAXI_BACK_MOVING_FORWARD, 0);
				s_->setVolumeSound(Channels_["BackForward"], ch_6_Vol_);
				ch_6_KeyDown = false;
			}
		}

		else if (channelEvent.channel_ == 6) {
			if (ch_3KeyDown) {
				s_->playSound_Ch(Channels_["Aceleration"], TAXI_ACCELERATE_01, -1); //play engine aceleration sound
				s_->setVolumeSound(Channels_["Aceleration"], ch_3_Vol_);
				ch_3KeyDown = false;
			}

			else {
				s_->playSound_Ch(Channels_["Regular"], TAXI_IDLE, -1);
				s_->setVolumeSound(Channels_["Regular"], ch_2_Vol_);
			}

		}	

		break;
	}

				//----------------------------------------------------//
	case TAXI_SHOOT: {
		TaxiShootEvent TaxiShootEvent_= static_cast<TaxiShootEvent&>(e);
		s_->playSound_Ch(Channels_["shoot"], (soundId)TaxiShootEvent_.shootId_, 0);
		break;
	}

	/*case SAVE_TAXI_POS: {
		for (auto it = Channels_.begin (); it != Channels_.end (); ++it) {
			s_->pauseSound ((*it).second);
		}
	}*/

	default:
		break;

	}
	return true;
}


TaxiSoundManagerCP::~TaxiSoundManagerCP()
{
}
