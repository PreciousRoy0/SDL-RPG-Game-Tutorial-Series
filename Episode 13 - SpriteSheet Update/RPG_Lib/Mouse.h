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
	static void HandelEvent(SDL_Event* mouseEvent);

	static void MouseWheel(SDL_MouseWheelEvent* wheel);
	static void MouseButton(SDL_MouseButtonEvent* button);
	static void MouseMotion(SDL_MouseMotionEvent* motion);


public:

	static MouseState GetState();
};
