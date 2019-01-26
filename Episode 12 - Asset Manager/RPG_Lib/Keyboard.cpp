#include "Keyboard.h"
#include <SDL.h>

KeyboardState Keyboard::m_State;

void Keyboard::HandelEvent(SDL_KeyboardEvent * keyevent)
{
	/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
	switch (keyevent->type) 
	{
	case SDL_KEYDOWN:
		m_State.m_KeyData[(Keys)keyevent->keysym.sym] = KeyState::Pressed;
		break;

	case SDL_KEYUP:
		m_State.m_KeyData[(Keys)keyevent->keysym.sym] = KeyState::Released;
		break;
	}
}

KeyboardState Keyboard::GetState()
{
	return m_State;
}
