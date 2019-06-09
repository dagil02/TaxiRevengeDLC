#pragma once

#include <vector>

#include "GameObject.h"
#include "InputComponent.h"
#include "LogicComponent.h"
#include "RenderComponent.h"

using namespace std;

class Container : public GameObject {

public:
	Container();
	virtual ~Container();

	virtual void handleInput(Uint32 deltaTime, const SDL_Event& event);
	virtual void update(Uint32 deltaTime);
	virtual void render(Uint32 deltaTime);

	virtual void addInputComponent(InputComponent* ic);
	virtual void addLogicComponent(LogicComponent* lc);
	virtual void addRenderComponent(RenderComponent* rc);

	virtual bool hasInputComponent(InputComponent* ic);
	virtual bool hasLogicComponent(LogicComponent* lc);
	virtual bool hasRenderComponent(RenderComponent* rc);

	virtual void delInputComponent(InputComponent* ic);
	virtual void delLogicComponent(LogicComponent* lc);
	virtual void delRenderComponent(RenderComponent* rc);

private:
	vector<InputComponent*> inputComp_;
	vector<LogicComponent*> logicComp_;
	vector<RenderComponent*> renderComp_;
};