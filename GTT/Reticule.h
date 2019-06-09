#pragma once
#include "Container.h"
#include "Animation.h"
#include "CursorLC.h"



class Reticule : public Container 
{

	//hide copyBuilder and 	assignment operator
	Reticule(Reticule&) = delete;
	Reticule & operator=(const Reticule &) = delete;

	static unique_ptr<Reticule> instance_; //ptr instance class


public:
	//Builder
	Reticule();
	virtual ~Reticule();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new Reticule());
		}
	}
	//get singleton class
	inline static Reticule* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	virtual void ChangeReticule(string ret);
	virtual string GetCurrentSprite();
	virtual void render(Uint32 deltaTime);

private:	
	map<string, string> animations_;
	Animation* animC_;
	CursorLC* cursorC_;
};

