#include "UI_ComboBox.h"

void UI_ComboBox::AddItem(std::string item)
{
	m_Items.push_back(item);
}

void UI_ComboBox::RemoveItem(std::string item)
{
	auto loc = std::find(m_Items.begin(), m_Items.end(), item);
	if (loc != m_Items.end())
	{
		m_Items.erase(loc);
		//recalculate index of selected item ?
	}
}