#pragma once

#include "KeyboardState.h"
struct SDL_KeyboardEvent;

class Keyboard
{
	static KeyboardState m_State;

	friend class SDL_EventHandeler;
	static void HandelEvent(SDL_KeyboardEvent* keyevent);

public:
	static KeyboardState GetState();
};

