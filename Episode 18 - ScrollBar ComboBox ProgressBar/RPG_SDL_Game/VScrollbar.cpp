#include "VScrollbar.h"
#include "Mouse.h"

#include "MouseEvent.h"
#include "SDL_ScreenHandeler.h"
#include "AssetManager.h"
#include "ScrollEvent.h"
#include "UIManager.h"

int VScrollBar::FindNerestPoint()
{
	MouseState mouseState = Mouse::GetState();
	Vector2 p = GetDrawLocation();

	RectangleF scrollSize = RectangleF(p, m_Size);
	scrollSize.Height -= 32;
	scrollSize.Y += 16;

	double step = scrollSize.Height / m_MaxValue;
	Vector2 reletiveLocation = mouseState.Location - Vector2(scrollSize.Location());

	return (int)(reletiveLocation.Y / step);
}

void VScrollBar::OnMouseScrollEvent(void* sender, IEvent * ev)
{
	MouseEvent* mev = (MouseEvent*)ev;
	Vector2 p = GetDrawLocation();

	RectangleF scrollSize = RectangleF(p, m_Size);
	scrollSize.Height -= 32;
	scrollSize.Y += 16;

	double step = scrollSize.Height / m_MaxValue;
	Vector2 CurrentLocation = Vector2(scrollSize.Location());

	if (mev->State.Wheel.Y < 0 && m_CurrentValue < (int)m_MaxValue) //down
		m_CurrentValue += 1;
	else if (mev->State.Wheel.Y > 0 && m_CurrentValue > 0)//up
		m_CurrentValue -= 1;

	ScrollEvent* evs = new ScrollEvent();
	evs->ScrollValue = m_CurrentValue;
	OnScroll.SetEvent(this, evs);
}

void VScrollBar::Initialize()
{
	UI_ScrollBar::Initialize();
	m_UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

	if (!m_UiSheet)
		throw "Ui spriteSheet not loaded";

	OnMouseScroll.AddListener(Bind<VScrollBar>(&VScrollBar::OnMouseScrollEvent, this));
}

void VScrollBar::Draw()
{
	Vector2 p = GetDrawLocation();

	m_UiSheet->Draw(273, p);

	m_UiSheet->Draw(303, (RectangleF)Rectangle(p.X, p.Y + 32, m_Size.Width, m_Size.Height - (32 * 2)));

	m_UiSheet->Draw(333, Vector2(p.X, p.Y + m_Size.Height - 32));

	//draw dragger
	RectangleF scrollSize = RectangleF(p, m_Size);
	scrollSize.Height -= 32;
	scrollSize.Y += 16;

	double step = scrollSize.Height / m_MaxValue;
	m_UiSheet->Draw(555, Vector2F(scrollSize.X, (scrollSize.Y - 16) + (step * m_CurrentValue)));

	if (m_Manager->GetDebugMode())
	{
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(p, m_Size), Color(255, 0, 0));
		TheSDLScreenHandeler::Pointer()->DrawRect(Rectangle(scrollSize), Color(255, 0, 0));
	}
}
