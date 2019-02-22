#pragma once
#include "UI_ProgressBar.h"
class SDL_TileSheet;

class ProgressBar : public UI_ProgressBar
{
	SDL_TileSheet* m_UiSheet;
	UI_Lable* m_Label;

	void OnFontChangedEvent(void* sender, IEvent * ev);
	void OnValueChangedEvent(void* sender, IEvent * ev);

	Vector2 GetCenterLableLocation();
	void UpdateLable();

public:

	void ShowText(bool res);

	virtual void Initialize() override;
	virtual void Update(KeyboardState & keystate, MouseState & mouseState) override;
	virtual void Draw() override;
};
