#pragma once
#include <string>
#include "IGameState.h"

class Menu;

class MenuItem
{
	IGameState* m_State = nullptr;
	std::string m_Text = "";
	bool m_Selected = false;

	friend Menu;

public:
	std::string GetText() { return m_Text; };
	bool Selected() { return m_Selected; }

	MenuItem(std::string text, IGameState* targetState, bool selected = false) { m_Text = text; m_State = targetState; m_Selected = selected; }
};
