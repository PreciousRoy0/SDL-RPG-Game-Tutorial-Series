#pragma once

#include "IUIControl.h"
#include "UI_Lable.h"

class UI_CheckBox : public IUIControl
{
	bool m_Checked = false;

protected:
	void OnMouseClickEvent(void* sender, IEvent* e);

public:
	virtual void Initialize() override;

	//Occurs when the check box checked state is changed
	EventListener OnChecked;

	void SetChecked(bool checked);
	bool IsChecked();

	virtual void Draw() = 0; //override and implement your own draw function
};