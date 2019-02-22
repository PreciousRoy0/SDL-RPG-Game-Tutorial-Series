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

std::map<Keys, KeyState> KeyboardState::GetPressedRepeatKeys()
{
	std::map<Keys, KeyState> keys (m_RepeateKeyData);

	//for (auto k : m_RepeateKeyData)
	//{
	//	if (k.second == KeyState::Pressed)
	//		keys[k.first] = k.second;
	//}

	return keys;
}

bool KeyboardState::IsKeyDown(Keys key)
{
	if (m_KeyData[key] == KeyState::Pressed)
		return true;

	return false;
}
