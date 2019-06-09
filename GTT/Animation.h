#pragma once

#include <string>
#include "Texture.h"
#include "RenderComponent.h"
#include "CameraType.h"

using namespace std;

class Camera;

class Animation : public RenderComponent {
public:
	Animation();
	virtual ~Animation();

	// Animation
	bool loadAnimation(string path, string name = "-1", int columns = 1, int rows = 1);
	bool animationExists(string name);

	bool isAnyAnimationPlaying();
	bool isAnimationPlaying(string name);

	string getCurrentAnimation();

	bool playAnimation(string name, float speed = true, bool loop = true);
	bool stopAnimation();
	bool pauseAnimation();
	bool resumeAnimation();

	virtual void render(GameObject* o, Uint32 deltaTime) override;
	
	void setCamera(cameraType cam);

	void setAnimation(string s);



private:


	cameraType cam_ = GAME_CAMERA;
	SDL_Rect* destRect;

	map<string, pair<Texture*, SDL_Rect*>> animations;
	string currentAnim = "-1";
	int currentFrame = 0;
	double elapsedTime = 0;
	int animationRows = 1, animationColumns = 1;

	const float speedMultiplier = 1000;
	float animationSpeed = 1;
	bool paused = false;
	bool animationLoop = true;

	void renderAnimation(GameObject *o, Uint32 deltaTime);
	void resetAnimationValues();

};