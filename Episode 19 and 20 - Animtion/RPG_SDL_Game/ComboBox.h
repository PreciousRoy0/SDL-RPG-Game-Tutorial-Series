#pragma once

#include "SDL_TileSheet.h"
#include "UI_ComboBox.h"
#include "Button.h"
#include "UI_Lable.h"
#include "Panel.h"
#include "VScrollbar.h"

class ComboBox : public UI_ComboBox
{
	SDL_TileSheet* m_UiSheet;

	UI_Lable*	m_TextLable;
	Button*		m_Button;
	Panel*		m_Panel;
	VScrollBar*	m_ScrollBar;
	UI_Lable*	m_Lable1;
	UI_Lable*	m_Lable2;
	UI_Lable*	m_Lable3;
	UI_Lable*	m_Lable4;
	UI_Lable*	m_Lable5;

	int			m_SelectedIndex = 0;
	bool		DropDownState = false;

	void OnCBSizeChanded(void* sender, IEvent*);
	void OnCBFontChanded(void* sender, IEvent*);

	void OnDropDownButton(void* sender, IEvent*);
	void OnPanelMouseScroll(void* sender, IEvent*);
	void OnScrollBarScroll(void* sender, IEvent*);
	void OnLableClick(void* sender, IEvent*);

	void UpdatePanelSize();
	void UpdateLableVisable();
	void UpdateLableText();

public:
	EventListener OnSelectedIndexChanged;

	virtual void Initialize() override;

	virtual void AddItem(std::string item) override;
	virtual void RemoveItem(std::string item) override;

	virtual void Draw() override;
};