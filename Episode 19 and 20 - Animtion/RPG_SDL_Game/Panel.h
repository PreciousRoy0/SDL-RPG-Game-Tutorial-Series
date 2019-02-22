#pragma once

#include "UI_Panel.h"
#include "SDL_TileSheet.h"

class Panel : public UI_Panel
{
	SDL_TileSheet* m_UiSheet;
	bool m_BG = false;

public:

	void SetBG(bool bg);
	virtual void Initialize() override;

	virtual void Update(KeyboardState& keystate, MouseState& mouseState) override;

	virtual void Draw() override;
};