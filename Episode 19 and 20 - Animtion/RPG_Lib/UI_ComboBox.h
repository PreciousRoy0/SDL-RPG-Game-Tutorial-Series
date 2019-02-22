#pragma once

#include "IUIControl.h"

class UI_ComboBox : public IUIControl
{
protected:
	std::vector<std::string> m_Items;

public:
	virtual void AddItem(std::string item);
	virtual void RemoveItem(std::string item);

	virtual void Draw() = 0; //override and implement your own draw function
};