#pragma once

#include <vector> 
#include "IUIControl.h"

class UIManager
{
	bool m_DebugMode = false;

	friend class IUIControl;
	IUIControl* HasFocus = nullptr;
	void SetFocus(IUIControl* controle)
	{
		if (!controle)
			return;

		if (HasFocus)
			HasFocus->m_HasFocus = false;

		HasFocus = controle;

		controle->m_HasFocus = true;
	}

public:
	std::vector<IUIControl*> Controls;

	void SetDebugMode(bool mode) { m_DebugMode = mode; }
	bool GetDebugMode() { return m_DebugMode; }

	void Update();
	void Draw();
};