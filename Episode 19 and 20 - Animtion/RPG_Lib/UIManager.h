#pragma once

#include <vector> 
#include "IUIControl.h"

class UIManager
{
	friend class IUIControl;
	bool m_DebugMode = false;

	IUIControl* HasFocus = nullptr;
	void SetFocus(IUIControl* controle)
	{
		if (HasFocus)
			HasFocus->m_HasFocus = false;

		HasFocus = controle;

		controle->m_HasFocus = true;
	}

public:
	std::vector<IUIControl*> Controls;

	template<class C>
	C* CreateControl()
	{
		C* c = new C;
		c->m_Manager = this;
		c->Initialize();
		return c;
	}

	void SetDebugMode(bool mode) { m_DebugMode = mode; }
	bool GetDebugMode() { return m_DebugMode; }
	void Update();
	void Draw();
};