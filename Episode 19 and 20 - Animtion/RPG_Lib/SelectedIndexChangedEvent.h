#pragma once
#include "IEvent.h"

class SelectedIndexChangedEvent : public IEvent
{

public:
	int SelectedIndex = 0;

};