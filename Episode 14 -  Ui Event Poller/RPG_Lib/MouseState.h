#pragma once

#include "KeyState.h"
#include "Vector2.h"

class MouseState
{
public:

	KeyState Left;
	KeyState Middle;
	KeyState Right;
	KeyState X1;
	KeyState X2;

	Vector2 Location;
	Vector2 ReletiveLocation;
	Vector2 Wheel;
};
