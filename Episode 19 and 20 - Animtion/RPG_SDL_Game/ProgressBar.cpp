#include "ProgressBar.h"

#include "SDL_ScreenHandeler.h"
#include "AssetManager.h"
#include "SDL_TileSheet.h"
#include "UIManager.h"

Vector2 ProgressBar::GetCenterLableLocation()
{
	Size tmp = m_Label->GetFont()->MeasureString(m_Label->GetText());

	return Vector2((int)((m_Size.Width * 0.5f) - (tmp.Width * 0.5f)), (int)((m_Size.Height * 0.5f) - (tmp.Height * 0.5f)));
}

void ProgressBar::UpdateLable()
{
	if (!m_Font)
		return;

	m_Label->SetText(GetPresentageS());
	m_Label->SetLocation(GetCenterLableLocation());
}

void ProgressBar::OnFontChangedEvent(void* sender, IEvent * ev)
{
	m_Label->SetFont(m_Font);
	UpdateLable();
}

void ProgressBar::OnValueChangedEvent(void* sender, IEvent * ev)
{
	UpdateLable();
}

void ProgressBar::ShowText(bool res)
{
	m_Label->SetVisable(res);
}

void ProgressBar::Initialize()
{
	UI_ProgressBar::Initialize();
	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	m_Label = m_Manager->CreateControl<UI_Lable>();
	AddControl(m_Label);
	OnFontChanged.AddListener(Bind<ProgressBar>(&ProgressBar::OnFontChangedEvent, this));
	OnValueChanged.AddListener(Bind<ProgressBar>(&ProgressBar::OnValueChangedEvent, this));
	UpdateLable();

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";
}

void ProgressBar::Update(KeyboardState & keystate, MouseState & mouseState)
{
	//base draw
	IUIControl::Update(keystate, mouseState);
}

void ProgressBar::Draw()
{
	Vector2F p = GetDrawLocation();

	int percentage = GetPercentage();
	float w = (m_Size.Width / 100.0f) * percentage;

	//draw bar
	if (w < 32)
		m_UiSheet->Draw(816, RectangleF(p.X, p.Y, w, (float)m_Size.Height));
	else
		m_UiSheet->Draw(816, RectangleF(p.X, p.Y, 32, (float)m_Size.Height));

	if (w > 32 && w < m_Size.Width - 32)
		m_UiSheet->Draw(817, RectangleF(p.X + 32, p.Y, w - 34, (float)m_Size.Height));
	else if (w > m_Size.Width - 32)
		m_UiSheet->Draw(817, RectangleF(p.X + 32, p.Y, (float)m_Size.Width - 64, (float)m_Size.Height));

	if (w >= m_Size.Width - 32)
		m_UiSheet->Draw(818, RectangleF((p.X + (float)m_Size.Width) - 32, p.Y, w - ((float)m_Size.Width - 32), (float)m_Size.Height));

	//draw border
	m_UiSheet->Draw(756, RectangleF(p.X, p.Y, 32, (float)m_Size.Height));
	m_UiSheet->Draw(757, RectangleF(p.X + 32, p.Y, (float)m_Size.Width - 64, (float)m_Size.Height));
	m_UiSheet->Draw(758, RectangleF((p.X + (float)m_Size.Width) - 32, p.Y, 32, (float)m_Size.Height));

	if (m_Manager->GetDebugMode())
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));

	//base draw
	IUIControl::Draw();
}
