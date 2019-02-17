#pragma once

#include "KeyboardState.h"
struct SDL_KeyboardEvent;

class Keyboard
{
	KeyboardState m_State;

	friend class SDL_EventHandeler;
	friend class SDL_GameStateManager;
	static void HandelEvent(SDL_KeyboardEvent* keyevent);

	//sets certain valus back to default.
	static void PreUpdate();

public:
	Keyboard();

	static KeyboardState& GetState();
};

