#pragma once

#include "IUIControl.h"

enum ButtonType
{
	ICON_ONLY,
	TEXT_ONLY,
	ICON_AND_TEXT
};

class UI_Button : public IUIControl
{
protected:
	ButtonType mButtonType = ButtonType::TEXT_ONLY;

public:
	EventListener OnButtonTypeChanged;

	ButtonType GetButtonType() const;
	void SetButtonType(ButtonType _mButtonType);
};