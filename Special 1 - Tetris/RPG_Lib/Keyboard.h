#pragma once
class Console_InputHandeler;
class Console_GameStateManager;

#include <map>
#include "KeyState.h"

enum class Keys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77,
	SPACE = 32,
	ENTER = 13,
	ESCAPE = 27
};

class Keyboard
{
	friend Console_InputHandeler;
	friend Console_GameStateManager;
	static Keyboard m_keyboard;

	std::map<Keys, KeyState> m_Keys;

	void Reset();
	void SetKeyState(short Key);
public:

	static Keyboard& GetState() { return m_keyboard; };

	bool KeyPressed(Keys key);
};
