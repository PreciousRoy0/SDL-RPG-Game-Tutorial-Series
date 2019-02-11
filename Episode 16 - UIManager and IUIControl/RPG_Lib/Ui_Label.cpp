#include "UI_Lable.h"
#include "SDL_ScreenHandeler.h"
#include "UIManager.h"

void UI_Lable::OnTextChangedEvent(void* sender, IEvent * ev)
{
	if (!m_Font)
	{
		printf("m_Font = null\n");
		return;
	}

	m_Size = m_Font->MeasureString(m_Text);
	OnSizeChanged.SetEvent(this, nullptr);
}

void UI_Lable::OnFontChangedEvent(void*, IEvent * ev)
{
	m_Size = m_Font->MeasureString(m_Text);
}

void UI_Lable::Draw()
{
	if (!m_Visable)
		return;

	Vector2 p = GetDrawLocation();

	if (!m_FixedSize)
		m_Font->DrawString(m_Text, Vector2F(p));
	else
		m_Font->DrawString(m_Text, RectangleF(p, m_Size));

	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));
}