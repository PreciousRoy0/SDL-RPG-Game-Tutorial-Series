#pragma once

#include "MouseState.h"
union SDL_Event;
struct SDL_MouseWheelEvent;
struct SDL_MouseButtonEvent;
struct SDL_MouseMotionEvent;

class Mouse
{
	static MouseState m_State;

	friend class SDL_EventHandeler;
	friend class SDL_GameStateManager;
	static void HandelEvent(SDL_Event* mouseEvent);

	static void MouseWheel(SDL_MouseWheelEvent* wheel);
	static void MouseButton(SDL_MouseButtonEvent* button);
	static void MouseMotion(SDL_MouseMotionEvent* motion);

	//sets certain valus back to default.
	static void PreUpdate()
	{
		m_State.Wheel.X = 0;
		m_State.Wheel.Y = 0;
	}

public:

	static MouseState GetState();
};
