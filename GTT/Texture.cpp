#include "Texture.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

Texture::Texture() :
	texture_(nullptr), renderer_(nullptr), width_(0), height_(0) {
}

Texture::Texture(SDL_Renderer* renderer, string fileName) :
	texture_(nullptr), width_(0), height_(0) {
	loadFromImg(renderer, fileName);
}

Texture::Texture(SDL_Renderer* renderer, string text, Font& font, const SDL_Color color) :
	texture_(nullptr), width_(0), height_(0) {
	loadFromText(renderer, text, font, color);
}

Texture::~Texture() {
	close();
}

int Texture::getWidth() {
	return width_;
}

int Texture::getHeight() {
	return height_;
}

void Texture::close() {
	if (texture_ != nullptr) {
		SDL_DestroyTexture(texture_); // delete current texture
		texture_ = nullptr;
		width_ = 0;
		height_ = 0;
	}
}

bool Texture::loadFromImg(SDL_Renderer* renderer, string fileName) {
	const char *file = fileName.c_str ();
	texture_ = IMG_LoadTexture(renderer, fileName.c_str());
	SDL_QueryTexture(texture_, NULL, NULL, &width_, &height_);
	renderer_ = renderer;
	return texture_ != NULL;
}

bool Texture::loadFromText(SDL_Renderer* renderer, string text, Font& font,
	const SDL_Color color) {
	SDL_Surface* textSurface = font.renderText(text, color);
	if (textSurface != nullptr) {
		close();
		texture_ = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (texture_ != nullptr) {
			width_ = textSurface->w;
			height_ = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	else {
		cout << "Couldn't create text: " << text << endl;
	}
	renderer_ = renderer;
	return texture_ != nullptr;
}

void Texture::render(int x, int y) const {
	render(renderer_, x, y);
}

void Texture::render(SDL_Renderer* renderer, int x, int y) const {
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = width_;
	dest.h = height_;
	render(renderer, dest);
}

void Texture::render(const SDL_Rect& dest, SDL_Rect* clip) const {
	render(renderer_, dest, clip);
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest,
	SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopy(renderer, texture_, clip, &dest);
	}
}

void Texture::render(const SDL_Rect& dest, double angle, SDL_Rect* clip) const {
	render(renderer_, dest, angle, clip);
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& dest, double angle,
	SDL_Rect* clip) const {
	if (texture_) {
		SDL_Rect default_clip = { 0, 0, width_, height_ };
		if (clip == nullptr) {
			clip = &default_clip;
		}
		SDL_RenderCopyEx(renderer, texture_, clip, &dest, angle, nullptr,
			SDL_FLIP_NONE);
	}
}

bool Texture::isReady() {
	return texture_ != nullptr;
}
