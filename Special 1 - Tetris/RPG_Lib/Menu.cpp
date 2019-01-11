#include "Menu.h"

#include "Console_Screen.h"
#include "Console_GameStateManager.h"
#include "Keyboard.h"

void Menu::Reset()
{
	m_MenuItems.clear();
}

void Menu::SetMenuName(std::string name)
{
	m_Name = name;
}

void Menu::AddMenuItem(MenuItem item)
{
	m_MenuItems.push_back(item);
}

void Menu::FindSelectedIndex()
{
	for (size_t i = 0; i < m_MenuItems.size(); i++)
	{
		if (m_MenuItems[i].m_Selected == true)
		{
			m_SelectedIndex = i;
			break;
		}
	}
}

int Menu::GetMenuWidth()
{
	int w = m_Name.size() + 2;

	for (size_t i = 0; i < m_MenuItems.size(); i++)
	{
		int num = m_MenuItems[i].GetText().size() + 2;
		if (num > w)
			w = num;
	}

	return w;
}

void Menu::UpdateSelection()
{
	for (size_t i = 0; i < m_MenuItems.size(); i++)
	{
		if (m_MenuItems[i].Selected())
			TheConsoleScreen::Pointer()->SetColor(ConsoleColor::ConsoleBGColor_White);
		Point p(((m_Border.Width - m_MenuItems[i].GetText().size()) / 2) + m_Border.X, m_Border.Y + 3 + i);
		TheConsoleScreen::Pointer()->SetCursorPosition(p);
		printf(m_MenuItems[i].GetText().c_str());
		TheConsoleScreen::Pointer()->SetColor(ConsoleColor::ConsoleTextColor_White);
	}
}

void Menu::Initialize()
{
	system("CLS");
	FindSelectedIndex();
	Size screenSize = TheConsoleScreen::Pointer()->GetSize();
	
	m_Border.Width = GetMenuWidth() + 2;
	m_Border.X = (screenSize.Width - m_Border.Width) / 2;
	m_Border.Height = m_MenuItems.size() + 4;
	m_Border.Y = (screenSize.Height - m_Border.Height) / 2;

	TheConsoleScreen::Pointer()->SetDrawRect(m_Border);

	Point p(((m_Border.Width - m_Name.size()) / 2) + m_Border.X, m_Border.Y + 1);
	TheConsoleScreen::Pointer()->SetCursorPosition(p);
	printf(m_Name.c_str());

	UpdateSelection();
}

void Menu::Update()
{
	Keyboard keyboard = Keyboard::GetState();
	
	if (keyboard.KeyPressed(Keys::UP))
	{
		m_SelectedIndex--;
		if (m_SelectedIndex < 0)
			m_SelectedIndex = 0;

		m_MenuItems[m_SelectedIndex + 1].m_Selected = false;
		m_MenuItems[m_SelectedIndex].m_Selected = true;

		UpdateSelection();
	}
	else if (keyboard.KeyPressed(Keys::DOWN))
	{
		m_SelectedIndex++;
		if (m_SelectedIndex > m_MenuItems.size() - 1)
			m_SelectedIndex = m_MenuItems.size() - 1;

		m_MenuItems[m_SelectedIndex - 1].m_Selected = false;
		m_MenuItems[m_SelectedIndex].m_Selected = true;

		UpdateSelection();
	}
	else if (keyboard.KeyPressed(Keys::ENTER))
	{
		TheConsoleGameStateManager::Pointer()->SetState(m_MenuItems[m_SelectedIndex].m_State);
	}
}
