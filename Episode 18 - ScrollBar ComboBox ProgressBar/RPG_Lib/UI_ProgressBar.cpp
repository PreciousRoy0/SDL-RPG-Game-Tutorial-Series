#include "UI_ProgressBar.h"

int UI_ProgressBar::GetPercentage()
{
	return (int)((100.f * m_Current) / m_Max);
}

std::string UI_ProgressBar::GetPresentageS()
{
	return std::string(std::to_string(GetPercentage()) + "%");
}

void UI_ProgressBar::SetValue(int value)
{
	if (value <= (int)m_Max)
	{
		m_Current = value;
		OnValueChanged.SetEvent(this, nullptr);
	}
}