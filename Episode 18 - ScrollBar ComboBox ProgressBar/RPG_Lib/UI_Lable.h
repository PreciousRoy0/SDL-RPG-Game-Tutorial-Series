#pragma once

#include "IUIControl.h"

class UI_Lable : public IUIControl
{
	void OnTextChangedEvent(void* sender, IEvent* ev);
	void OnFontChangedEvent(void* sender, IEvent * ev);

public:
	virtual void Initialize() override;

	virtual void Draw() override;
};