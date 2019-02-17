#include "KeyboardState.h"

std::vector<Keys> KeyboardState::GetPressedKeys()
{
	std::vector<Keys> keys;

	for (auto k : m_KeyData)
	{
		if (k.second == KeyState::Pressed)
			keys.push_back(k.first);
	}

	return keys;
}

std::vector<Keys> KeyboardState::GetPressedRepeatKeys()
{
	std::vector<Keys> keys;

	for (auto k : m_RepeateKeyData)
	{
		if (k.second == KeyState::Pressed)
			keys.push_back(k.first);
	}

	return keys;
}

bool KeyboardState::IsKeyDown(Keys key)
{
	if (m_KeyData[key] == KeyState::Pressed)
		return true;

	return false;
}
