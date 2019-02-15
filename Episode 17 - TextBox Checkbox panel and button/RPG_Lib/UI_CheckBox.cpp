#include "UI_CheckBox.h"
#include "EventListener.h"

#include "CheckedEvent.h"

void UI_CheckBox::OnMouseClickEvent(void* sender, IEvent* e)
{
	m_Checked = !m_Checked;
	CheckedEvent* ev = new CheckedEvent;
	ev->CheckedState = m_Checked;
	OnChecked.SetEvent(this, ev);
}

void UI_CheckBox::Initialize()
{
	OnMouseClick.AddListener(Bind<UI_CheckBox>(&UI_CheckBox::OnMouseClickEvent, this));
}

void UI_CheckBox::SetChecked(bool checked)
{
	m_Checked = checked;
	CheckedEvent* ev = new CheckedEvent;
	ev->CheckedState = m_Checked;
	OnChecked.SetEvent(this, ev);
}

bool UI_CheckBox::IsChecked()
{
	return m_Checked;
}
