#pragma once
#include "Vector2D.h"
#include <SDL.h>
#include <map>
#include <vector>
#include "Constants.h"
#include "Observer.h"

using namespace std;

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	bool isActive() const;
	void setActive(bool active);
	bool toggleActive();

	double getWidth() const;
	virtual void setWidth(double width);

	double getHeight() const;
	virtual void setHeight(double height);

	void scale(double s);

	virtual Vector2D getPosition() const;

	// If force is set to true, components such as the physics one
	// should set their positions to this
	virtual void setPosition(const Vector2D &pos, bool force = false);

	double getRotation() const;
	virtual void setRotation(double angle);
	virtual Vector2D getCenter();

	// some GameObjects cannot be initialized in the constructor,
	// for example when we create them using the default constructor
	// and without passing the game. This method is supposed to
	// be called once they are ready to be initialized. The
	// default implementation does nothing.
	virtual void init();

	// abstract methods to be implemented in sub-classes
	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event) = 0;
	virtual void update(Uint32 deltaTime) = 0;
	virtual void render(Uint32 deltaTime) = 0;

protected:
	bool active_;   // indicates if the object is active

	double width_;  // width
	double height_; // height

	Vector2D position_; // position (suppose to be left-top corner)
	double rotation_; // rotation (for the corresponding texture)
};


