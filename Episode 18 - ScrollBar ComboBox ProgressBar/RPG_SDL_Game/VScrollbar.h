#pragma once
#include "UI_ScrollBar.h"
#include "SDL_TileSheet.h"

class VScrollBar : public UI_ScrollBar
{
	SDL_TileSheet* m_UiSheet;

	virtual int FindNerestPoint() override;
	virtual void OnMouseScrollEvent(void* sender, IEvent* ev) override;

public:

	virtual void Initialize() override;

	virtual void Draw() override;
};