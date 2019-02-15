#pragma once

#include "IUIControl.h"
#include "SDL_Time.h"

class UI_TextBox : public IUIControl
{
	SDL_FlipFlopTimer timer;

public:
	virtual void Initialize() override;

	virtual void Update(KeyboardState& keystate, MouseState& mouseState) override;
	virtual void Draw() override;
};