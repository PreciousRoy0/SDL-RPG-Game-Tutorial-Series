#include "CheckBox.h"
#include "AssetManager.h"
#include "SDL_TileSheet.h"
#include "UIManager.h"
#include "SDL_ScreenHandeler.h"

void CheckBox::OnFontChangedEvent(void* sender, IEvent *)
{
	m_Label->SetFont(m_Font);
}

void CheckBox::OnTextChangeEvent(void* sender, IEvent *)
{
	m_Label->SetText(m_Text);
}

void CheckBox::OnLocationChangeEvent(void* sender, IEvent *)
{
	//needs to be tested
	Vector2 loc;
	loc.X += m_Size.Width + 4;
	loc.Y += (int)((m_Size.Width * 0.5f) - (m_Font->MeasureString(m_Text).Height * 0.5f));

	m_Label->SetLocation(loc);
}


void CheckBox::Initialize()
{
	UI_CheckBox::Initialize();

	m_Label = m_Manager->CreateControl<UI_Lable>();
	AddControl(m_Label);

	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";

	m_Label->OnMouseClick.AddListener(Bind<CheckBox>(&CheckBox::OnMouseClickEvent, this));
	OnTextChanged.AddListener(Bind<CheckBox>(&CheckBox::OnTextChangeEvent, this));
	OnLocationChanged.AddListener(Bind<CheckBox>(&CheckBox::OnLocationChangeEvent, this));
	OnFontChanged.AddListener(Bind<CheckBox>(&CheckBox::OnFontChangedEvent, this));
}

void CheckBox::Draw()
{
	Vector2 p = GetDrawLocation();

	if (IsChecked())
		m_UiSheet->Draw(183, p);
	else
		m_UiSheet->Draw(153, p);

	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));

	IUIControl::Draw();
}

