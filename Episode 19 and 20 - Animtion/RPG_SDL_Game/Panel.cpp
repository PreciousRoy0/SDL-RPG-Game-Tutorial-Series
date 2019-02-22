#include "Panel.h"
#include "SDL_ScreenHandeler.h"
#include "UIManager.h"
#include "AssetManager.h"

void Panel::SetBG(bool bg)
{
	m_BG = bg;
}

void Panel::Initialize()
{
	UI_Panel::Initialize();
	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";
}

void Panel::Update(KeyboardState & keystate, MouseState & mouseState)
{
	IUIControl::Update(keystate, mouseState);
}

void Panel::Draw()
{
	if (m_BG && m_UiSheet)
	{
		Vector2 p = GetDrawLocation();

		//top
		m_UiSheet->Draw(60, p);
		m_UiSheet->Draw(61, RectangleF((float)(p.X + 32), (float)(p.Y), (float)(m_Size.Width - 64), (float)(32)));
		m_UiSheet->Draw(62, Vector2F((float)(p.X + m_Size.Width) - 32, (float)p.Y));

		//center
		m_UiSheet->Draw(90, RectangleF((float)p.X, (float)p.Y + 32, 32, (float)(m_Size.Height - 64)));
		m_UiSheet->Draw(91, RectangleF((float)(p.X + 32), (float)(p.Y) + 32, (float)(m_Size.Width - 64), (float)(m_Size.Height - 64)));
		m_UiSheet->Draw(92, RectangleF((float)(p.X + m_Size.Width) - 32, (float)p.Y + 32, 32, (float)(m_Size.Height - 64)));

		//bottom
		m_UiSheet->Draw(120, Vector2F((float)p.X, (float)p.Y + (m_Size.Height - 32)));
		m_UiSheet->Draw(121, RectangleF((float)(p.X + 32), (float)(p.Y) + (m_Size.Height - 32), (float)(m_Size.Width - 64), (float)(32)));
		m_UiSheet->Draw(122, Vector2F((float)(p.X + m_Size.Width) - 32, (float)p.Y + (m_Size.Height - 32)));
	}

	if (m_Manager->GetDebugMode())
	{
		Vector2 p = GetDrawLocation();
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));
	}

	UI_Panel::Draw();
}
