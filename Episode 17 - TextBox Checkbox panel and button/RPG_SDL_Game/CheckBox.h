#pragma once
#include "UI_CheckBox.h"
class SDL_TileSheet;

class CheckBox : public UI_CheckBox
{
	SDL_TileSheet* m_UiSheet;

	UI_Lable* m_Label;

	void OnFontChangedEvent(void* sender, IEvent*);
	void OnTextChangeEvent(void* sender, IEvent*);
	void OnLocationChangeEvent(void* sender, IEvent*);

public:

	virtual void Initialize() override;
	virtual void Draw() override;
};
