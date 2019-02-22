#pragma once

#include "IUIControl.h"
#include "Size.h"
#include "UI_Lable.h"

class UI_ProgressBar : public IUIControl
{
protected:
	const unsigned int m_Min = 0;
	unsigned int m_Max = 100;
	unsigned int m_Current = 0;

public:
	EventListener OnValueChanged;

	int GetPercentage();
	std::string GetPresentageS();

	void SetValue(int value);

	virtual void Update(KeyboardState& keystate, MouseState& mouseState) = 0;
	virtual void Draw() = 0;
};