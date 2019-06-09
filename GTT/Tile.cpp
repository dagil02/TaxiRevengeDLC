#include "Tile.h"

Tile::Tile(Texture* texture, SDL_Rect* dest, SDL_Rect* clip, uint32_t id) {
	// GameObject defaults
	setPosition(Vector2D(dest->x, dest->y));
	setWidth(dest->w);
	setHeight(dest->h);

	// Sprite
	sprite_ = new Sprite(texture);
	sprite_->setClipRect(clip);
	addRenderComponent(sprite_);

	// Tile
	id_ = id;
}


Tile::~Tile() {
	delete sprite_; sprite_ = nullptr;
}