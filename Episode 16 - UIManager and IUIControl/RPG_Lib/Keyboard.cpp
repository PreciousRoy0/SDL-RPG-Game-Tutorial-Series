#include "Keyboard.h"
#include <SDL.h>

void Keyboard::HandelEvent(SDL_KeyboardEvent * keyevent)
{
	Keys c = Keys::SPACE;

	/* We are only worried about SDL_KEYDOWN and SDL_KEYUP events */
	switch (keyevent->type)
	{
	case SDL_KEYDOWN:
		GetState().m_KeyData[(Keys)keyevent->keysym.sym] = KeyState::Pressed;
		GetState().m_RepeateKeyData[(Keys)keyevent->keysym.sym] = KeyState::Pressed;
		break;

	case SDL_KEYUP:
		GetState().m_KeyData[(Keys)keyevent->keysym.sym] = KeyState::Released;
		GetState().m_RepeateKeyData[(Keys)keyevent->keysym.sym] = KeyState::Released;
		break;
	}
}

void Keyboard::PreUpdate()
{
	GetState().m_RepeateKeyData.clear();
}

Keyboard::Keyboard()
{
	int temp = SDL_GetModState();
	int cap = temp & KMOD_CAPS;
	int num = temp & KMOD_NUM;

	if (cap == KMOD_CAPS)
		m_State.m_KeyData[Keys::CAPSLOCK] = KeyState::Pressed;

	if (num == KMOD_NUM)
		m_State.m_KeyData[Keys::NUMLOCK] = KeyState::Pressed;
}

KeyboardState& Keyboard::GetState()
{
	static Keyboard k;
	return k.m_State;
}
