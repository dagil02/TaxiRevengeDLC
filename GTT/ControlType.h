#pragma once
#include "InputComponent.h"
#include "LogicComponent.h"

class ControlType :
	public InputComponent, public LogicComponent, public Observable
{
public:
	ControlType();
	virtual ~ControlType();
};

