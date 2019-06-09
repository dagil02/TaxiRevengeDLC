#pragma once
#include "Container.h"
#include <SDL_mixer.h>
#include "Observable.h"

class SoundManager: public Observable {

	//hide copyBuilder and 	assignment operator
	SoundManager(SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	static unique_ptr<SoundManager> instance_; //ptr instance class

public:

	//Builder
	SoundManager();
	virtual ~SoundManager();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new SoundManager());
		}
	}
	//get singleton class
	inline static SoundManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}
		
	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	//Methods to define how many channels we can use
	int setAlloctaedChannels(int n);

	// DON'T USE THIS DIRECTLY,
	// USE THE RESOURCES SHEET INSTEAD !!!
	bool loadSound(string path, soundId id);
	bool loadMusic(string path, musicId id);

	// Returns the channel in which the sound will be played
	int playSound_Ch(int channel, soundId id, int loops); //secundary
	int playSound(soundId id, int loops);//primary


	//pause and resume de specific channel
	void pauseSound(int channel);
	void resumeSound(int channel);

	int stopSound(int channel);
	bool isSoundPlaying(int channel);
	bool soundExists(soundId id);
	

	void playMusic(musicId id, int loops);
	void pauseMusic();
	void resumeMusic();
	bool isMusicPlaying();
	bool musicExists(musicId id);

	//Mix_Volume sets the volume of a channel specified. The amount passed to volume can be between 0 and MIX_MAX_VOLUME which equals 128.
	void setVolumeSound(int& channel, const int& v);
	//channel -1: set volume in all channels
	//especified -1 in volume parameter for return current volume value of channel
	int getVolumeSound(int& channel, const int& v = -1);

	int getMIX_MAX_VOLUME();


private:
	
	map<musicId, Mix_Music*> loadedMusic_;
	map<soundId, Mix_Chunk*> loadedSounds_;

	static void channelDone(int channel);

};

