#pragma once

#include "IUIControl.h"

class UI_Lable : public IUIControl
{
	void OnTextChangedEvent(void* sender, IEvent* ev);
	void OnFontChangedEvent(void* sender, IEvent * ev);

public:
	UI_Lable(UIManager* manager)
	{
		m_Manager = manager;
		OnTextChanged.AddListener(Bind<UI_Lable>(&UI_Lable::OnTextChangedEvent, this));
		OnFontChanged.AddListener(Bind<UI_Lable>(&UI_Lable::OnFontChangedEvent, this));
	};

	virtual void Draw() override;
};