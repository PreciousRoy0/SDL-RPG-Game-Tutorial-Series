#include "TextBox.h"
#include "SDL_ScreenHandeler.h"
#include "UIManager.h"
#include "AssetManager.h"

void TextBox::SetBG(bool bg)
{
	m_BG = bg;
}

void TextBox::Initialize()
{
	UI_TextBox::Initialize();
	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";
}

void TextBox::Draw()
{
	if (m_BG && m_UiSheet)
	{
		Vector2 p = GetDrawLocation();

		p.Y -= ((32 - m_Size.Height) / 2) + 4;
		p.X -= 6;

		m_UiSheet->Draw(93, p);
		m_UiSheet->Draw(94, RectangleF((float)(p.X + 32), (float)(p.Y), (float)(m_Size.Width + 10 - 64), (float)(32)));
		m_UiSheet->Draw(95, Vector2F((float)(p.X + m_Size.Width + 10) - 32, (float)p.Y));
	}

	if (m_Manager->GetDebugMode())
	{
		Vector2 p = GetDrawLocation();
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));
	}

	UI_TextBox::Draw();
}
