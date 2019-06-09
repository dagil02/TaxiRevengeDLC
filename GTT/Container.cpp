#include "Container.h"

Container::Container() : 
	inputComp_(), logicComp_(), renderComp_() {
}

Container::~Container() {
}

void Container::handleInput(Uint32 deltaTime, const SDL_Event& event) {
	if (!active_)
		return;

	for (InputComponent* ic : inputComp_) {
		ic->handleInput(this, deltaTime, event);
	}
}

void Container::update(Uint32 deltaTime) {
	if (!active_)
		return;

	for (LogicComponent* pc : logicComp_) {
		pc->update(this, deltaTime);
	}
}

void Container::render(Uint32 deltaTime) {
	if (!active_)
		return;

	for (RenderComponent* rc : renderComp_) {
		rc->render(this, deltaTime);
	}
}

void Container::addInputComponent(InputComponent* ic) {
	inputComp_.push_back(ic);
}

void Container::addLogicComponent(LogicComponent* lc) {
	logicComp_.push_back(lc);
}

void Container::addRenderComponent(RenderComponent* rc) {
	renderComp_.push_back(rc);
}

bool Container::hasInputComponent(InputComponent * ic) {
	std::vector<InputComponent*>::iterator position = std::find(
		inputComp_.begin(), inputComp_.end(), ic);

	return position != inputComp_.end();
}

bool Container::hasLogicComponent(LogicComponent *lc) {
	std::vector<LogicComponent*>::iterator position = std::find(
		logicComp_.begin(), logicComp_.end(), lc);

	return position != logicComp_.end();
}

bool Container::hasRenderComponent(RenderComponent * rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
		renderComp_.begin(), renderComp_.end(), rc);

	return position != renderComp_.end();
}

void Container::delInputComponent(InputComponent* ic) {
	std::vector<InputComponent*>::iterator position = std::find(
		inputComp_.begin(), inputComp_.end(), ic);
	if (position != inputComp_.end())
		inputComp_.erase(position);
}

void Container::delLogicComponent(LogicComponent* pc) {
	std::vector<LogicComponent*>::iterator position = std::find(
		logicComp_.begin(), logicComp_.end(), pc);
	if (position != logicComp_.end())
		logicComp_.erase(position);
}

void Container::delRenderComponent(RenderComponent* rc) {
	std::vector<RenderComponent*>::iterator position = std::find(
		renderComp_.begin(), renderComp_.end(), rc);
	if (position != renderComp_.end())
		renderComp_.erase(position);
}
