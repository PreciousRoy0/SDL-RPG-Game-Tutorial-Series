#pragma once

#include "IEvent.h"
#include "Mouse.h"

class MouseEvent : public IEvent
{

public:
	MouseState State;
	MouseButtons Button = MouseButtons::None;

};
