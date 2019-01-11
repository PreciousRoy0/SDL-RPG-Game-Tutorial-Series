#pragma once

#include <vector>
#include <string>
#include "MenuItem.h"
#include "Rectangle.h"

class Menu
{
	std::string m_Name = "";
	std::vector<MenuItem> m_MenuItems;
	Rectangle2d m_Border;
	int m_SelectedIndex = 0;

	void FindSelectedIndex();
	int GetMenuWidth();
	void UpdateSelection();

protected:
	void Reset();
	void SetMenuName(std::string name);
	void AddMenuItem(MenuItem item);

public:

	void Initialize();
	void Update();
};
