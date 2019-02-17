#pragma once
#include "IEvent.h"
#include "IUIControl.h"

class CheckedEvent : public IEvent
{
public:
	bool CheckedState = false;

	CheckedEvent() {}

	CheckedEvent(bool checkedState) : CheckedState(checkedState)
	{

	}
};
