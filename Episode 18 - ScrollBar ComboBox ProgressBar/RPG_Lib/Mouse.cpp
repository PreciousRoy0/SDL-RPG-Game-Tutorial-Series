#include "Mouse.h"

#include <SDL.h>

MouseState Mouse::m_State;

void Mouse::MouseMotion(SDL_MouseMotionEvent* motion)
{
	m_State.Location.X = motion->x;
	m_State.Location.Y = motion->y;

	m_State.ReletiveLocation.X = motion->xrel;
	m_State.ReletiveLocation.Y = motion->yrel;
}

void Mouse::MouseButton(SDL_MouseButtonEvent* button)
{
	KeyState kstate = (KeyState)button->state;

	switch (button->button)
	{
	case SDL_BUTTON_LEFT:
		m_State.Left = kstate;
		break;

	case SDL_BUTTON_MIDDLE:
		m_State.Middle = kstate;
		break;

	case SDL_BUTTON_RIGHT:
		m_State.Right = kstate;
		break;

	case SDL_BUTTON_X1:
		m_State.X1 = kstate;
		break;

	case SDL_BUTTON_X2:
		m_State.X2 = kstate;
		break;
	}
}

void Mouse::MouseWheel(SDL_MouseWheelEvent* wheel)
{
	m_State.Wheel.X = wheel->x;
	m_State.Wheel.Y = wheel->y;
}

void Mouse::HandelEvent(SDL_Event* mouseEvent)
{
	switch (mouseEvent->type)
	{
	case SDL_MOUSEMOTION:
		MouseMotion(&mouseEvent->motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		MouseButton(&mouseEvent->button);
		break;
	case SDL_MOUSEWHEEL:
		MouseWheel(&mouseEvent->wheel);
		break;
	}
}

MouseState Mouse::GetState()
{
	return m_State;
}
