#pragma once
#include "IUIControl.h"
#include "SDL_TileSheet.h"
#include "UI_Button.h"
#include "UI_Lable.h"

class Button : public UI_Button
{
	SDL_TileSheet* m_UiSheet;
	int m_Icon = -1;

	UI_Lable* m_Label;
	bool ButtonState = false;

	void OnTextChangeEvent(void* sender, IEvent*);
	void OnFontChangeEvent(void* sender, IEvent*);
	void OnLocationChangeEvent(void* sender, IEvent*);
	void OnButtonTypeChangedEvent(void* sender, IEvent*);

	void OnMouseDownEvent(void* sender, IEvent*);
	void OnMouseUpEvent(void* sender, IEvent*);

	virtual void Draw() override;

public:

	virtual void Initialize() override;
	void SetIcon(int icon) { m_Icon = icon; }
};