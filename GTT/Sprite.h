#pragma once

#include "Texture.h"
#include "RenderComponent.h"
#include "Camera.h"

using namespace std;

class Sprite : public RenderComponent {

public:
	Sprite(string path = "./../Assets/sprites/default.png",
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);

	Sprite(Texture* texture,
		   int w = 100, int h = 100,
		   int x = 0, int y = 0);

	virtual ~Sprite();

	virtual void render(GameObject* o, Uint32 deltaTime) override;
	void render(Vector2D pos,int w, int h);  //render alternativo

	void setCamera(cameraType cam);
	cameraType getCameraType();
	Camera* getCamera();

	void setClipRect(SDL_Rect *clip);
	const SDL_Rect* getRect();
	const SDL_Rect* getClipRect();
	Texture* getTexture();

	void setAutoPos(bool autoPos);
	void setAutoSize(bool autoSize);

	void setPos(int x, int y);
	void setSize(int w, int h);

protected:
	Texture *texture_;
	SDL_Rect *rect_;
	SDL_Rect *clip_ = nullptr;

	bool autoPos_ = true;
	bool autoSize_ = true;

	cameraType cam_ = GAME_CAMERA;
};
