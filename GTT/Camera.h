#pragma once

#include "Container.h"
#include "Texture.h"
#include "SDL.h"
#include "Vector2D.h"
#include "CameraType.h"

class Game;

class Camera : public Container {
public:
	Camera(int width, int height, float zoom = 1);
	virtual ~Camera();

	void renderTexture(Texture* texture, SDL_Rect const& dest,
		SDL_Rect* clip = nullptr, double angle = 0);

	// Setters and getters
	virtual void setPosition(const Vector2D &pos, bool force = false) override;
	void setSize(int w, int h, bool resetZoom = false);
	virtual void setWidth(double width) override;
	virtual void setHeight(double height) override;

	void setZoom(float zoom, bool center = true);
	void setCentered (bool center);
	float getZoom();
	bool getCentered ();

private:
	SDL_Rect* cameraRect_;

	float zoom_;
	bool centered = true;
};

