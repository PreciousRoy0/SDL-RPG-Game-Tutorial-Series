#pragma once
#include "IEvent.h"

class ScrollEvent : public IEvent
{
public:
	unsigned int ScrollValue = 0;
};
