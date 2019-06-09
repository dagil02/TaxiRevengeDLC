#include "SoundManager.h"


unique_ptr<SoundManager> SoundManager::instance_ = nullptr;

SoundManager::SoundManager() {

	Mix_ChannelFinished(&SoundManager::channelDone); //dont touch

	// Load the music files from the resources sheet
	for (auto music : MUSIC) {
		loadMusic(music.second, music.first);
	}
	
	// Load the sound files from the resources sheet
	for (auto sound : SOUND) {
		loadSound(sound.second, sound.first);
	}
}

SoundManager::~SoundManager() {
	for (auto music : loadedMusic_) {
		Mix_FreeMusic(music.second);
		music.second = nullptr;
	}
	loadedMusic_.clear();

	for (auto sound : loadedSounds_) {
		Mix_FreeChunk(sound.second);
		sound.second = nullptr;
	}
	loadedSounds_.clear();
}



int SoundManager::setAlloctaedChannels(int n)
{
	return Mix_AllocateChannels(n);	
}

// NO NEED TO USE THIS DIRECTLY,
// USE THE RESOURCES SHEET INSTEAD !!!
bool SoundManager::loadSound(string path, soundId id) {
	loadedSounds_[id] = Mix_LoadWAV(path.c_str());
	return loadedSounds_[id] != nullptr;
}

//secundary method
int SoundManager::playSound_Ch(int channel, soundId id, int loops) {
	return Mix_PlayChannel(channel, loadedSounds_[id], loops);
}
//primary method
int SoundManager::playSound(soundId id, int loops) {
	return Mix_PlayChannel(-1, loadedSounds_[id], loops);
}

void SoundManager::pauseSound(int channel) {
	Mix_Pause(channel);
}

void SoundManager::resumeSound(int channel) {
	Mix_Resume(channel);
}



int SoundManager::stopSound(int channel)
{
	return Mix_HaltChannel(channel);
}


bool SoundManager::isSoundPlaying(int channel) {
	return Mix_Playing(channel);
}

bool SoundManager::soundExists(soundId id) {
	return loadedSounds_.find(id) != loadedSounds_.end();
}

bool SoundManager::loadMusic(string path, musicId id) {
	loadedMusic_[id] = Mix_LoadMUS(path.c_str());

	return loadedMusic_[id] != nullptr;
}

void SoundManager::playMusic(musicId id, int loops) {
	Mix_PlayMusic(loadedMusic_[id], loops);
}

void SoundManager::pauseMusic() {
	Mix_PauseMusic();
}

void SoundManager::resumeMusic() {
	Mix_ResumeMusic();
}

bool SoundManager::isMusicPlaying() {
	return Mix_PlayingMusic();
}

bool SoundManager::musicExists(musicId id) {
	return loadedMusic_.find(id) != loadedMusic_.end();
}


void SoundManager::setVolumeSound(int& channel, const int& v)
{
	Mix_Volume(channel, v);
}

int SoundManager::getVolumeSound(int & channel, const int & v)
{
	return Mix_Volume(channel, v);
}

int SoundManager::getMIX_MAX_VOLUME()
{
	return MIX_MAX_VOLUME;

}

void SoundManager::channelDone(int channel) {
	ChannelStoppedPlaying e = ChannelStoppedPlaying(instance_.get(), channel);
	instance_.get()->broadcastEvent(e);
}
