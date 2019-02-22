#include "UI_TextBox.h"

#include "Keyboard.h"
#include "SDL_ScreenHandeler.h"
#include "UIManager.h"

void UI_TextBox::Initialize()
{
	timer.SetInterval(300);
	timer.Start();
}

void UI_TextBox::Update(KeyboardState & keystate, MouseState & mouseState)
{
	IUIControl::Update(keystate, mouseState);// handle events

	if (m_HasFocus)
	{
		std::map<Keys, KeyState> k = keystate.GetPressedRepeatKeys();

		for (auto item : k)
		{
			if (item.first == Keys::BACKSPACE && m_Text.size() > 0 && item.second == KeyState::Pressed)
			{
				m_Text.pop_back();
				OnTextChanged.SetEvent(this, nullptr); //should call text change
				continue;
			}
			else
			{
				char c = (char)item.first;
				m_Text.push_back((char)item.first);

				if (m_FixedSize)
				{
					if (m_Font->MeasureString(m_Text).Width + m_Font->MeasureString("_").Width > (float)m_Size.Width)
					{
						m_Text.pop_back();
						continue;
					}
				}
				OnTextChanged.SetEvent(this, nullptr); //should call text change
			}
		}
	}
}

void UI_TextBox::Draw()
{
	Vector2F p = GetDrawLocation();

	if (m_FixedSize)
		m_Font->DrawString(m_Text, p);
	else
		m_Font->DrawString(m_Text, RectangleF(p, m_Size));

	if (m_HasFocus && timer.IsSet())
		m_Font->DrawString(std::string("_"), Vector2F(p.X + m_Font->MeasureString(m_Text).Width, p.Y));

	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));
}
