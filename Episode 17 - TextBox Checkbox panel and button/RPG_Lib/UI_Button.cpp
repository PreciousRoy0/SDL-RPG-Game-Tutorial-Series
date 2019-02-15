#include "UI_Button.h"

ButtonType UI_Button::GetButtonType() const
{
	return mButtonType;
}

void UI_Button::SetButtonType(ButtonType _mButtonType)
{
	mButtonType = _mButtonType;
	OnButtonTypeChanged.SetEvent(this, nullptr);
}