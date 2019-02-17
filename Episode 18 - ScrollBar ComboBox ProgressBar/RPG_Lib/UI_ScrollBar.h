#pragma once
#include "IUIControl.h"
#include "EventListener.h"


class UI_ScrollBar : public IUIControl
{
protected:
	unsigned int m_MaxValue = 10;
	int m_CurrentValue = 5;
	bool m_MouseDown = false;

	void OnMouseDownEvent(void* sender, IEvent* ev);
	void OnMouseUpEvent(void* sender, IEvent* ev);
	virtual void OnMouseScrollEvent(void* sender, IEvent*) = 0;

	virtual int FindNerestPoint() = 0;

public:
	int GetValue();
	void SetValue(int value);
	void SetMaxValue(int value);

	//Occurs when the scrollbar is scrolled
	EventListener OnScroll;

	virtual void Initialize() override;

	virtual void Update(KeyboardState& keystate, MouseState& mouseState);
	virtual void Draw() = 0; //override and implement your own draw function
};