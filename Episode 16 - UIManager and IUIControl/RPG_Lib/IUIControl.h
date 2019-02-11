#pragma once
#include <vector>

#include "UIParameters.h"
#include "EventListener.h"
#include "KeyState.h"
#include "SDL_Time.h"
class KeyboardState;
#include "MouseState.h"
class UIManager;


class IUIControl : public UIParameters
{
protected:
	UIManager* m_Manager;

	//store mouse event states
	bool		m_MouseOver = false;
	bool		m_MouseDown = false;
	bool		m_MouseMove = false;
	Vector2		m_LastPosition;
	int			m_Clicks = 0;
	SDL_Timer	m_DoubleClickTimer = (500);//500ms for 2 clicks for now...
	KeyState	m_MouseLeft = KeyState::Released;
	KeyState	m_MouseMiddle = KeyState::Released;
	KeyState	m_MouseRight = KeyState::Released;
	KeyState	m_MouseX1 = KeyState::Released;
	KeyState	m_MouseX2 = KeyState::Released;
	MouseButtons m_ButtonDown = MouseButtons::None;

	std::vector<IUIControl*> m_Controls;
	IUIControl*	m_Parent = nullptr;

	// dont forget to call bace class
	virtual void Update(KeyboardState& keystate, MouseState& mouseState);
	virtual void Draw();

	Vector2 GetDrawLocation();

public:
	friend class UIManager;

	//global vars other shared settings are inherated

	IUIControl* GetParent();
	void AddControl(IUIControl* control);
	void RemoveControl(IUIControl* control);
	std::vector<IUIControl*> GetControls();

	//Occurs when the mouse pointer enters the control rect.
	EventListener OnMouseEnter;
	//Occurs when the mouse pointer leaves the control rect.
	EventListener OnMouseLeave;
	//Occurs when the mouse pointer is over the control and a mouse button is pressed.
	EventListener OnMouseDown;
	//Occurs when the mouse pointer is over the control and a mouse button is released.
	EventListener OnMouseUp;
	//Occurs when the mouse pointer is moved over the control.
	EventListener OnMouseMove;
	//Occurs when the control is clicked by the mouse.
	EventListener OnMouseClick;
	//Occurs when a mouse button is clicked two or more times.
	EventListener OnMouseDoubleClick;
	//Occurs when the scrollbar is scrolled
	EventListener OnMouseScroll;

	virtual ~IUIControl() = 0 {};
};