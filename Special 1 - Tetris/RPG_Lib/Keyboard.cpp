#include "Keyboard.h"

Keyboard Keyboard::m_keyboard;

void Keyboard::Reset()
{
	m_Keys.clear();
}

void Keyboard::SetKeyState(short Key)
{
	m_Keys.insert(std::pair<Keys, KeyState>((Keys)Key, KeyState::Down));
}

bool Keyboard::KeyPressed(Keys key)
{
	std::map<Keys, KeyState>::iterator ksi = m_Keys.find(key);

	if (ksi != m_Keys.end())
		return true;

	return false;
}
