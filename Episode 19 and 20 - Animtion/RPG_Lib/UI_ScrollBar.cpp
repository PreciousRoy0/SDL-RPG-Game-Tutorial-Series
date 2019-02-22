#include "UI_ScrollBar.h"
#include "ScrollEvent.h"

void UI_ScrollBar::OnMouseDownEvent(void* sender, IEvent * ev)
{
	m_MouseDown = true;
}

void UI_ScrollBar::OnMouseUpEvent(void* sender, IEvent * ev)
{
	m_MouseDown = false;
}

int UI_ScrollBar::GetValue()
{
	return m_CurrentValue;
};

void UI_ScrollBar::SetValue(int value)
{
	if (value > (int)m_MaxValue)
		m_CurrentValue = m_MaxValue;
	else
		m_CurrentValue = value;
}

void UI_ScrollBar::SetMaxValue(int value)
{
	m_MaxValue = value;
	if (m_CurrentValue > (int)m_MaxValue)
		m_CurrentValue = (int)m_MaxValue;
}

void UI_ScrollBar::Initialize()
{
	OnMouseDown.AddListener(Bind<UI_ScrollBar>(&UI_ScrollBar::OnMouseDownEvent, this));
	OnMouseUp.AddListener(Bind<UI_ScrollBar>(&UI_ScrollBar::OnMouseUpEvent, this));
}

void UI_ScrollBar::Update(KeyboardState & keystate, MouseState & mouseState)
{
	IUIControl::Update(keystate, mouseState);

	if (m_MouseDown)
	{
		m_CurrentValue = FindNerestPoint();

		if (m_CurrentValue < 0)
			m_CurrentValue = 0;

		if (m_CurrentValue > (int)m_MaxValue)
			m_CurrentValue = m_MaxValue;

		ScrollEvent* ev = new ScrollEvent();
		ev->ScrollValue = m_CurrentValue;
		OnScroll.SetEvent(this, ev);
	}
}