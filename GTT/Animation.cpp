#include "Animation.h"
#include "Camera.h"
#include "Game.h"

Animation::Animation() {
	destRect = new SDL_Rect();
	destRect->w = destRect->h = 100;
	destRect->x = destRect->y = 0;

}

Animation::~Animation() {
	for (auto animation:animations) {
		delete animation.second.first;
		delete animation.second.second;
	}
	animations.clear();

	delete destRect; destRect = nullptr;
}

// Animation frames are played in order from left to right,
// top to bottom, with the given speed
bool Animation::loadAnimation(string path, string name, int columns, int rows) {

	if (path != "-1") {
		Texture* animTexture = new Texture(Game::getInstance()->getRenderer(), path);

		SDL_Rect* animRect = new SDL_Rect();
		animRect->h = animTexture->getHeight() / rows;
		animRect->w = animTexture->getWidth() / columns;
		animRect->x = animRect->y = 0;

		if (animRect->w > 0 && animRect->h > 0) {
			animations[name] = pair<Texture*, SDL_Rect*>(animTexture, animRect);
			return true;
		}
	}

	return false;
}

bool Animation::playAnimation(string name, float speed, bool loop) {
	if (animationExists(name)) {
		currentAnim = name;
		animationSpeed = speed;
		animationLoop = loop;

		resetAnimationValues();

		animationColumns = animations[name].first->getWidth() / animations[name].second->w;
		animationRows = animations[name].first->getHeight() / animations[name].second->h;

		return true;
	}

	return false;
}

bool Animation::isAnyAnimationPlaying() {
	return currentAnim != "default";

}

// Checks whether the given animation is currently
// playing
bool Animation::isAnimationPlaying(string name) {
	return currentAnim == name;
}

string Animation::getCurrentAnimation()
{
	return currentAnim;
}


// Pauses the current animation
bool Animation::pauseAnimation()
{
	if (isAnyAnimationPlaying()) {
		paused = true;
		return true;
	}

	return false;
}

// Resumes a paused animation, returns true if
// the animation was paused, false otherwise
bool Animation::resumeAnimation()
{
	if (isAnyAnimationPlaying() && paused) {
		paused = false;
		return true;
	}

	return false;
}

void Animation::render(GameObject * o, Uint32 deltaTime) {
	// Rendering
	if (currentAnim != "-1") {
		renderAnimation(o, deltaTime);
	}
}

// Stops the current animation, returns true if
// any animation is playing, false otherwise
bool Animation::stopAnimation() {
	if (isAnyAnimationPlaying()) {
		currentAnim = "default";
		return true;
	}

	return false;
}

bool Animation::animationExists(string name) {
	return animations.count(name) > 0;
}

void Animation::renderAnimation(GameObject* o, Uint32 deltaTime) {
	if (elapsedTime > currentFrame * speedMultiplier / animationSpeed) {
		currentFrame++;

		if (currentFrame >= animationColumns * animationRows) {
			if (animationLoop)
				resetAnimationValues();
			else {
				if (!playAnimation("default")) {
					currentAnim = "-1";
					return;
				}
			}
		}
	}
	
	Texture* animTexture = animations[currentAnim].first;
	SDL_Rect* animRect = animations[currentAnim].second;

	if (!animationExists(currentAnim) || animTexture == nullptr || animRect == nullptr)
		return;

	animRect->x = currentFrame % animationColumns * animRect->w;
	animRect->y = trunc(currentFrame / animationColumns) * animRect->h;

	destRect->x = o->getPosition().x;
	destRect->y = o->getPosition().y;
	destRect->w = o->getWidth();
	destRect->h = o->getHeight();
	
	Game::getInstance()->getCamera(cam_)->renderTexture(animTexture, *destRect, animRect, o->getRotation());

	if (isAnyAnimationPlaying() && !paused) elapsedTime += deltaTime;
}


void Animation::resetAnimationValues() {
	paused = false;
	elapsedTime = 0;
	currentFrame = 0;
}

void Animation::setCamera(cameraType cam) {
	cam_ = cam;
}

void Animation::setAnimation(string s)
{
	currentAnim = s;
}
