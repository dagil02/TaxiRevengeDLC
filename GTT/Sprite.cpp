#include "Sprite.h"
#include "Game.h"
#include <iostream>

Sprite::Sprite(string path, int w, int h, int x, int y) {
	texture_ = new Texture(Game::getInstance()->getRenderer(), path);
	rect_ = new SDL_Rect();
	rect_->h = h; rect_->w = w; rect_->x = x; rect_->y = y;
}

Sprite::Sprite(Texture * texture, int w, int h, int x, int y) {
	texture_ = texture;
	rect_ = new SDL_Rect();
	rect_->h = h; rect_->w = w; rect_->x = x; rect_->y = y;
}

Sprite::~Sprite() {
	texture_->close();
	delete texture_; texture_ = nullptr;
	delete rect_; rect_ = nullptr;
	delete clip_; clip_ = nullptr;
}

void Sprite::setClipRect(SDL_Rect * clip) {
	clip_ = clip;
}

const SDL_Rect * Sprite::getRect()
{
	return rect_;
}

Texture * Sprite::getTexture() {
	return texture_;
}

void Sprite::setAutoPos(bool autoPos) {
	autoPos_ = autoPos;
}

void Sprite::setAutoSize(bool autoSize) {
	autoSize_ = autoSize;
}

void Sprite::setPos(int x, int y) {
	rect_->x = x;
	rect_->y = y;
}

void Sprite::setSize(int w, int h) {
	rect_->w = w;
	rect_->h = h;
}

const SDL_Rect * Sprite::getClipRect() {
	return clip_;
}

void Sprite::render(GameObject * o, Uint32 deltaTime) {
	if (autoPos_) {
		rect_->x = o->getPosition().x;
		rect_->y = o->getPosition().y;
	}

	if (autoSize_) {
		rect_->w = o->getWidth();
		rect_->h = o->getHeight();
	}

	Game::getInstance()->getCamera(cam_)->renderTexture(texture_, *rect_, clip_, o->getRotation());
}

void Sprite::render(Vector2D pos, int w, int h)
{
	if (autoPos_) {
		rect_->x = pos.x;
		rect_->y = pos.y;
	}

	if (autoSize_) {
		rect_->w = w;
		rect_->h = h;
	}

	Game::getInstance()->getCamera(cam_)->renderTexture(texture_, *rect_, clip_,0);
}

void Sprite::setCamera(cameraType cam) {
	cam_ = cam;
}

cameraType Sprite::getCameraType() {
	return cam_;
}

Camera * Sprite::getCamera() {
	return Game::getInstance()->getCamera(cam_);
}
