#pragma once

#include "KeyState.h"
#include "Vector2.h"

enum class MouseButtons
{
	None,
	Left,
	Right,
	Middle,
	XButton1,
	XButton2
};

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
