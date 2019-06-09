#pragma once

#include <vector>
#include <map>

#include "Container.h"
#include "Tile.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>

class TileMap : public Container {
public:
	TileMap(string path);
	virtual ~TileMap();

	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event) override;
	virtual void update(Uint32 deltaTime) override;
	virtual void render(Uint32 deltaTime) override;

private:
	SDL_Rect chunk;

	// Reads the already parsed tmx map and
	// creates the correspondent GameObjects
	void tmxToScene();

	// Helper functions to process each object layer
	bool processObject(string layerName, const tmx::Object &object);
	bool processCollision(const tmx::Object &object);
	bool processPlayer(const tmx::Object &object);
	bool processGas(const tmx::Object &object);
	bool processNodes(const tmx::Object &object, string layerName);
	bool processSpawns(const tmx::Object &object);

	tmx::Map tmxMap_;
	PhysicObject* phyO_;
	Sprite *mapSprite_;

	int test;
};


