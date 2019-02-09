#pragma once

#include "IEvent.h"

class MouseUpEvent : public IEvent
{

public:
	int x = 0;
	int y = 0;

};