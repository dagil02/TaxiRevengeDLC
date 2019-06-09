#include "Camera.h"
#include "Game.h"



Camera::Camera(int width, int height, float zoom) {
	cameraRect_ = new SDL_Rect();
	cameraRect_->w = width_ = width;
	cameraRect_->h = height_ = height;
	cameraRect_->x = cameraRect_->y = 0;

	setZoom(zoom);
}


Camera::~Camera() {
	delete cameraRect_; cameraRect_ = nullptr;
}

void Camera::renderTexture(Texture * texture, SDL_Rect const & dest, SDL_Rect * clip, double angle) {
	SDL_Rect transposedRect = SDL_Rect();
	int width = 0, height = 0;
	SDL_RenderGetLogicalSize(Game::getInstance()->getRenderer(), &width, &height);

	if (!centered) {
		texture->render (dest, angle, clip);
	}
	else {
		// Center the camera rect (in any zoom's been applied)
		cameraRect_->x = position_.x + (width_/2 - cameraRect_->w / 2);
		cameraRect_->y = position_.y + (height_/2 - cameraRect_->h / 2);

		transposedRect.w = (int)(((double)dest.w / (double)cameraRect_->w) * width);
		transposedRect.h = (int)(((double)dest.h / (double)cameraRect_->h) * height);
		transposedRect.x = (double)(dest.x - cameraRect_->x) / ((double)cameraRect_->w / width);
		transposedRect.y = (double)(dest.y - cameraRect_->y) / ((double)cameraRect_->h / height);
		texture->render(transposedRect, angle, clip);
	}

}
	

void Camera::setPosition(const Vector2D &pos, bool force) {
	cameraRect_->x = pos.x;
	cameraRect_->y = pos.y;

	GameObject::setPosition(Vector2D(cameraRect_->x, cameraRect_->y));
}

void Camera::setSize(int w, int h, bool resetZoom) {
	cameraRect_->w = width_ = w;
	cameraRect_->h = height_ = h;

	if (resetZoom) zoom_ = 1;
	else setZoom(zoom_);
}

void Camera::setWidth(double width) {
	setSize(width, height_);
}

void Camera::setHeight(double height) {
	setSize(width_, height);
}

void Camera::setZoom(float zoom, bool center) {
	zoom_ = zoom;
	centered = center;

	cameraRect_->w = (int)(width_ * (1 / zoom_));
	cameraRect_->h = (int)(height_ * (1 / zoom_));

	if (center) {
		cameraRect_->x -= (cameraRect_->w - width_) / 2;
		cameraRect_->y -= (cameraRect_->h - height_) / 2;
	}
	else {
		cameraRect_->x = 0;
		cameraRect_->y = 0;
	}
}

void Camera::setCentered (bool center) {
	centered = center;
}

float Camera::getZoom() {
	return zoom_;
}

bool Camera::getCentered () {
	return centered;
}