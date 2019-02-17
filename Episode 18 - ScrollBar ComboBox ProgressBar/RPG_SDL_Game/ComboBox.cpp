#include "ComboBox.h"
#include "AssetManager.h"
#include "SDL_ScreenHandeler.h"
#include "SelectedIndexChangedEvent.h"
#include "UIManager.h"

#include "MouseEvent.h"

void ComboBox::OnCBSizeChanded(void* sender, IEvent* ev)
{
	m_Button->SetLocation(Vector2(m_Size.Width - m_Button->GetSize().Width, 0));
	m_TextLable->SetLocation(Vector2F(10, (m_Size.Height * 0.5f) - (m_TextLable->GetSize().Height * 0.5f) + 1));
	m_Panel->SetLocation(Vector2(0, m_Size.Height));
	UpdatePanelSize();
	m_ScrollBar->SetLocation(Vector2(m_Size.Width - m_Button->GetSize().Width, m_Size.Height));
	m_ScrollBar->SetSize(Size(m_Button->GetSize().Width, m_Size.Height * 5));

	Vector2 center = Vector2F(10, (m_Size.Height * 0.5f) - (m_TextLable->GetSize().Height * 0.5f) + 4);
	m_Lable1->SetLocation(center);
	m_Lable2->SetLocation(Vector2(center.X, (m_Size.Height * 1) + center.Y));
	m_Lable3->SetLocation(Vector2(center.X, (m_Size.Height * 2) + center.Y));
	m_Lable4->SetLocation(Vector2(center.X, (m_Size.Height * 3) + center.Y));
	m_Lable5->SetLocation(Vector2(center.X, (m_Size.Height * 4) + center.Y));
}

void ComboBox::UpdatePanelSize()
{
	if (m_Items.size() <= 5)
	{
		int height = m_Size.Height * m_Items.size();
		m_Panel->SetSize(Size(m_Size.Width, height));
	}
	else
		m_Panel->SetSize(Size(m_Size.Width - m_Button->GetSize().Width, m_Size.Height * 5));
}

void ComboBox::UpdateLableVisable()
{
	if (m_Items.size() >= 1)
		m_Lable1->SetVisable(true);
	else
		m_Lable1->SetVisable(false);

	if (m_Items.size() >= 2)
		m_Lable2->SetVisable(true);
	else
		m_Lable2->SetVisable(false);

	if (m_Items.size() >= 3)
		m_Lable3->SetVisable(true);
	else
		m_Lable3->SetVisable(false);

	if (m_Items.size() >= 4)
		m_Lable4->SetVisable(true);
	else
		m_Lable4->SetVisable(false);

	if (m_Items.size() >= 5)
		m_Lable5->SetVisable(true);
	else
		m_Lable5->SetVisable(false);
}

void ComboBox::UpdateLableText()
{
	if (m_Items.size() <= 5)
		for (int i = 0; i < (int)m_Items.size(); i++)
		{
			m_Panel->GetControls()[i]->SetText(m_Items[i]);
		}
	else
	{
		int pos = m_ScrollBar->GetValue();
		for (int i = 0; i < 5; i++)
		{
			m_Panel->GetControls()[i]->SetText(m_Items[i + pos]);
		}
	}
}

void ComboBox::OnCBFontChanded(void* sender, IEvent *)
{
	//m_TextLable->SetFont(m_Font);
	//m_Lable1->SetFont(m_Font);
	//m_Lable2->SetFont(m_Font);
	//m_Lable3.SetFont(m_Font);
	//m_Lable4.SetFont(m_Font);
	//m_Lable5.SetFont(m_Font);

	m_TextLable->SetFont(m_Font);
	m_Button->SetFont(m_Font);
	m_Panel->SetFont(m_Font);
	m_ScrollBar->SetFont(m_Font);
	m_Lable1->SetFont(m_Font);
	m_Lable2->SetFont(m_Font);
	m_Lable3->SetFont(m_Font);
	m_Lable4->SetFont(m_Font);
	m_Lable5->SetFont(m_Font);
}

void ComboBox::OnDropDownButton(void* sender, IEvent *)
{
	DropDownState = !DropDownState;
	if (DropDownState)
	{
		m_Button->SetIcon(274);
		AddControl(m_Panel);
		if (m_Items.size() > 5)
			AddControl(m_ScrollBar);

		UpdateLableVisable();
		UpdateLableText();
	}
	else
	{
		m_Button->SetIcon(275);
		RemoveControl(m_Panel);
		if (m_Items.size() > 5)
			RemoveControl(m_ScrollBar);
	}
}

void ComboBox::OnPanelMouseScroll(void* sender, IEvent * ev)
{
	if (m_Items.size() > 5)
	{
		MouseEvent* e = new MouseEvent();
		e->State = (*(MouseEvent*)ev).State;
		m_ScrollBar->OnMouseScroll.SetEvent(this, e);
	}
}

void ComboBox::OnScrollBarScroll(void* sender, IEvent *)
{
	UpdateLableText();
}

void ComboBox::OnLableClick(void* sender, IEvent * ev)
{
	UI_Lable* label = (UI_Lable*)sender;
	MouseEvent* e = new MouseEvent();
	e->State = (*(MouseEvent*)ev).State;
	e->Button = (*(MouseEvent*)ev).Button;

	int selectedIndex = 0;

	for (int i = 0; i < (int)m_Panel->GetControls().size(); i++)
	{
		if (m_Panel->GetControls()[i] == label)
		{
			selectedIndex = i + m_ScrollBar->GetValue();
			break;
		}
	}

	m_SelectedIndex = selectedIndex;
	m_TextLable->SetText(m_Items[m_SelectedIndex]);
	OnDropDownButton(this, nullptr);

	SelectedIndexChangedEvent* sev = new SelectedIndexChangedEvent();
	sev->SelectedIndex = selectedIndex;
	OnSelectedIndexChanged.SetEvent(this, sev);
}


void ComboBox::Initialize()
{
	UI_ComboBox::Initialize();
	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";


	if (m_Button)
	{
		m_Button = m_Manager->CreateControl<Button>();
		m_TextLable = m_Manager->CreateControl<UI_Lable>();
		m_Panel = m_Manager->CreateControl<Panel>();
		m_ScrollBar = m_Manager->CreateControl<VScrollBar>();
		m_Lable1 = m_Manager->CreateControl<UI_Lable>();
		m_Lable2 = m_Manager->CreateControl<UI_Lable>();
		m_Lable3 = m_Manager->CreateControl<UI_Lable>();
		m_Lable4 = m_Manager->CreateControl<UI_Lable>();
		m_Lable5 = m_Manager->CreateControl<UI_Lable>();
	}

	//control bindings
	OnSizeChanged.AddListener(Bind<ComboBox>(&ComboBox::OnCBSizeChanded, this));
	OnFontChanged.AddListener(Bind<ComboBox>(&ComboBox::OnCBFontChanded, this));

	//helper control setup
	m_TextLable->SetText("ComboBox");
	m_TextLable->OnFontChanged.AddListener(Bind<ComboBox>(&ComboBox::OnCBSizeChanded, this));
	m_Button->SetButtonType(ButtonType::ICON_ONLY);
	m_Button->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnDropDownButton, this));
	m_Button->SetIcon(275);
	m_Panel->OnMouseScroll.AddListener(Bind<ComboBox>(&ComboBox::OnPanelMouseScroll, this));
	m_ScrollBar->SetValue(0);
	m_ScrollBar->OnScroll.AddListener(Bind<ComboBox>(&ComboBox::OnScrollBarScroll, this));

	m_Lable1->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnLableClick, this));
	m_Lable2->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnLableClick, this));
	m_Lable3->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnLableClick, this));
	m_Lable4->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnLableClick, this));
	m_Lable5->OnMouseClick.AddListener(Bind<ComboBox>(&ComboBox::OnLableClick, this));

	//add controls
	AddControl(m_TextLable);
	AddControl(m_Button);

	m_Panel->AddControl(m_Lable1);
	m_Panel->AddControl(m_Lable2);
	m_Panel->AddControl(m_Lable3);
	m_Panel->AddControl(m_Lable4);
	m_Panel->AddControl(m_Lable5);
}

void ComboBox::AddItem(std::string item)
{
	UI_ComboBox::AddItem(item);

	UpdateLableText();
	if (m_Items.size() > 5)
		m_ScrollBar->SetMaxValue(m_Items.size() - 5);
}

void ComboBox::RemoveItem(std::string item)
{
	UI_ComboBox::RemoveItem(item);

	UpdateLableText();
	if (m_Items.size() > 5)
		m_ScrollBar->SetMaxValue(m_Items.size() - 5);
}

void ComboBox::Draw()
{
	Vector2 p = GetDrawLocation();

	//draw button textfield
	m_UiSheet->Draw(240, p);
	m_UiSheet->Draw(241, RectangleF(p.X + 32, p.Y, m_Size.Width - 96, m_Size.Height));
	m_UiSheet->Draw(242, Vector2F((p.X + m_Size.Width) - 64, p.Y));

	if (DropDownState)
	{
		Vector2 panel = m_Panel->GetLocation();

		if (m_Items.size() == 1)
		{
			m_UiSheet->Draw(240, p + panel);
			m_UiSheet->Draw(241, RectangleF(p.X + panel.X + 32, p.Y + panel.Y, m_Size.Width - 64, m_Size.Height));
			m_UiSheet->Draw(242, Vector2F((p.X + panel.X + m_Size.Width) - 32, p.Y + panel.Y));
		}
		else
		{
			if (m_Items.size() < 5) //draw full size
			{
				m_UiSheet->Draw(270, p + panel);
				m_UiSheet->Draw(271, RectangleF(p.X + panel.X + 32, p.Y + panel.Y, m_Size.Width - 64, m_Size.Height));
				m_UiSheet->Draw(272, Vector2F((p.X + panel.X + m_Size.Width) - 32, p.Y + panel.Y));

				for (int i = 1; i < (int)m_Items.size(); i++)
				{
					if (i == 5)
						break;

					if (i == 5 - 1)
					{//Draw end
						m_UiSheet->Draw(330, p + panel + (Vector2(0, m_Size.Height) * i));
						m_UiSheet->Draw(331, RectangleF(p.X + panel.X + 32, p.Y + panel.Y + (m_Size.Height * i), m_Size.Width - 64, m_Size.Height));
						m_UiSheet->Draw(332, Vector2F((p.X + panel.X + m_Size.Width) - 32, p.Y + panel.Y + (m_Size.Height * i)));
					}
					else
					{//draw middle
						m_UiSheet->Draw(300, p + panel + (Vector2(0, m_Size.Height) * i));
						m_UiSheet->Draw(301, RectangleF(p.X + panel.X + 32, p.Y + panel.Y + (m_Size.Height * i), m_Size.Width - 64, m_Size.Height));
						m_UiSheet->Draw(302, Vector2F((p.X + panel.X + m_Size.Width) - 32, p.Y + panel.Y + (m_Size.Height * i)));
					}
				}
			}
			else
			{
				m_UiSheet->Draw(270, p + panel);
				m_UiSheet->Draw(271, RectangleF(p.X + panel.X + 32, p.Y + panel.Y, m_Size.Width - 96, m_Size.Height));
				m_UiSheet->Draw(272, Vector2F((p.X + panel.X + m_Size.Width) - 64, p.Y + panel.Y));

				for (int i = 1; i < (int)m_Items.size(); i++)
				{
					if (i == 5)
						break;

					if (i == 5 - 1)
					{//Draw end
						m_UiSheet->Draw(330, p + panel + (Vector2(0, m_Size.Height) * i));
						m_UiSheet->Draw(331, RectangleF(p.X + panel.X + 32, p.Y + panel.Y + (m_Size.Height * i), m_Size.Width - 96, m_Size.Height));
						m_UiSheet->Draw(332, Vector2F((p.X + panel.X + m_Size.Width) - 64, p.Y + panel.Y + (m_Size.Height * i)));
					}
					else
					{//draw middle
						m_UiSheet->Draw(300, p + panel + (Vector2(0, m_Size.Height) * i));
						m_UiSheet->Draw(301, RectangleF(p.X + panel.X + 32, p.Y + panel.Y + (m_Size.Height * i), m_Size.Width - 96, m_Size.Height));
						m_UiSheet->Draw(302, Vector2F((p.X + panel.X + m_Size.Width) - 64, p.Y + panel.Y + (m_Size.Height * i)));
					}
				}
			}
		}
	}


	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));

	IUIControl::Draw();
}
