#include "Button.h"
#include "AssetManager.h"
#include "SDL_ScreenHandeler.h"
#include "UIManager.h"

void Button::Initialize()
{
	UI_Button::Initialize();

	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";

	m_Label = m_Manager->CreateControl<UI_Lable>();
	AddControl(m_Label);

	OnTextChanged.AddListener(Bind<Button>(&Button::OnTextChangeEvent, this));
	OnFontChanged.AddListener(Bind<Button>(&Button::OnFontChangeEvent, this));
	OnLocationChanged.AddListener(Bind<Button>(&Button::OnLocationChangeEvent, this));
	OnButtonTypeChanged.AddListener(Bind<Button>(&Button::OnButtonTypeChangedEvent, this));
	m_Label->OnSizeChanged.AddListener(Bind<Button>(&Button::OnLocationChangeEvent, this));

	OnMouseDown.AddListener(Bind<Button>(&Button::OnMouseDownEvent, this));
	OnMouseUp.AddListener(Bind<Button>(&Button::OnMouseUpEvent, this));
}


void Button::OnTextChangeEvent(void* sender, IEvent *)
{
	m_Label->SetText(m_Text);
	OnLocationChangeEvent(this, nullptr);
}

void Button::OnFontChangeEvent(void* sender, IEvent *)
{
	m_Label->SetFont(m_Font);
	OnLocationChangeEvent(this, nullptr);
}

void Button::OnLocationChangeEvent(void* sender, IEvent *)
{
	m_Label->SetLocation(
		Vector2F(((m_Size.Width * 0.5f) - (m_Label->GetSize().Width * 0.5f)),
		((m_Size.Height * 0.5f) - (m_Label->GetSize().Height * 0.5f))));
}

void Button::OnButtonTypeChangedEvent(void* sender, IEvent *)
{
	if (mButtonType == ButtonType::ICON_ONLY)
	{
		SetSize(Size(32, 32));

		//delete the label from the list
		for (int i = 0; i < (int)m_Controls.size(); i++)
		{
			if (m_Controls[i] == m_Label)
			{
				m_Controls.erase(m_Controls.begin() + i);
				break;
			}
		}
	}
}

void Button::OnMouseDownEvent(void* sender, IEvent *)
{
	ButtonState = true;
	m_Label->GetLocation().Y += 4;
}

void Button::OnMouseUpEvent(void* sender, IEvent *)
{
	ButtonState = false;
	m_Label->GetLocation().Y -= 4;
}

void Button::Draw()
{
	Vector2 p = GetDrawLocation();
	//when it is a small button
	if (mButtonType == ButtonType::ICON_ONLY)
	{
		Vector2 IcontLoc = p;
		if (ButtonState)
		{
			m_UiSheet->Draw(153, p);
			IcontLoc.Y += 1;
		}
		else
		{
			m_UiSheet->Draw(362, p);
			IcontLoc.Y -= 1;
		}

		if (m_Icon != -1)
			m_UiSheet->Draw(m_Icon, IcontLoc);
	}
	else if (mButtonType == ButtonType::TEXT_ONLY)
	{
		if (ButtonState)
		{
			//draw button
			m_UiSheet->Draw(33, p);
			m_UiSheet->Draw(34, RectangleF((float)(p.X + 32), (float)(p.Y), (float)(m_Size.Width - 64), (float)(m_Size.Height)));
			m_UiSheet->Draw(35, Vector2F((float)(p.X + m_Size.Width) - 32, (float)p.Y));
		}
		else
		{
			//draw button
			m_UiSheet->Draw(30, p);
			m_UiSheet->Draw(31, RectangleF((float)p.X + 32, (float)p.Y, (float)m_Size.Width - 64, (float)m_Size.Height));
			m_UiSheet->Draw(32, Vector2F((float)(p.X + m_Size.Width) - 32, (float)p.Y));
		}
	}

	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));

	//do base draw call
	IUIControl::Draw();
}

