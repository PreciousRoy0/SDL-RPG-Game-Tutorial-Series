#include "IUIControl.h"

#include "MousEvent.h"
#include "UIManager.h"

void IUIControl::Update(KeyboardState & keystate, MouseState & mouseState)
{
	if (!m_Visable)
		return;

	Rectangle UIrect = Rectangle(GetDrawLocation(), m_Size);
	//mouse enters
	if (UIrect.Contains(mouseState.Location) && !m_MouseOver)
	{
		//dispach event
		MouseEvent* ev = new MouseEvent();
		ev->State = mouseState;
		printf("Mouse enters\n");

		OnMouseEnter.SetEvent(this, ev);
		m_MouseOver = true;
	}

	//mouse leaves
	else if (UIrect.Contains(mouseState.Location) && m_MouseOver)
	{
		//dispach event
		MouseEvent* ev = new MouseEvent();
		ev->State = mouseState;
		printf("Mouse leaves\n");

		OnMouseLeave.SetEvent(this, ev);
		m_MouseOver = false;
		
		// Cancel mouse down
		if (m_MouseDown)
		{
			m_MouseDown = false;

			m_MouseLeft = KeyState::Released;
			m_MouseMiddle = KeyState::Released;
			m_MouseRight = KeyState::Released;
			m_MouseX1 = KeyState::Released;
			m_MouseX2 = KeyState::Released;

			ev = new MouseEvent();
			ev->State = mouseState;
			ev->Button = m_ButtonDown;
			printf("Cancel mouse down\n");
			OnMouseUp.SetEvent(this, ev);
		}
	}

	//mouse down
	if ((mouseState.Left != m_MouseLeft && mouseState.Left == KeyState::Pressed ||
		mouseState.Middle != m_MouseMiddle && mouseState.Middle == KeyState::Pressed ||
		mouseState.Right != m_MouseRight && mouseState.Right == KeyState::Pressed ||
		mouseState.X1 != m_MouseX1 && mouseState.X1 == KeyState::Pressed ||
		mouseState.X2 != m_MouseX2 && mouseState.X2 == KeyState::Pressed) && m_MouseOver)
	{
		m_MouseLeft = mouseState.Left;
		m_MouseMiddle = mouseState.Middle;
		m_MouseRight = mouseState.Right;
		m_MouseX1 = mouseState.X1;
		m_MouseX2 = mouseState.X2;

		if (mouseState.Left == KeyState::Pressed)
			m_ButtonDown = MouseButtons::Left;
		else if (mouseState.Middle == KeyState::Pressed)
			m_ButtonDown = MouseButtons::Middle;
		else if (mouseState.Right == KeyState::Pressed)
			m_ButtonDown = MouseButtons::Right;
		else if (mouseState.X1 == KeyState::Pressed)
			m_ButtonDown = MouseButtons::XButton1;
		else if (mouseState.X2 == KeyState::Pressed)
			m_ButtonDown = MouseButtons::XButton2;

		//dispach event
		MouseEvent* ev = new MouseEvent();
		ev->State = mouseState;
		ev->Button = m_ButtonDown;
		printf("Mouse down\n");

		OnMouseDown.SetEvent(this, ev);
		m_MouseDown = true;

		m_Manager->SetFocus(this);
	}

	//Double click Timer Occurs when the mouse takes to long for the second hit.
	if (m_MouseOver && m_DoubleClickTimer.TimerHit())
	{
		m_Clicks = 0;
	}

	//mouse up
	if ((mouseState.Left != m_MouseLeft && mouseState.Left == KeyState::Released ||
		mouseState.Middle != m_MouseMiddle && mouseState.Middle == KeyState::Released ||
		mouseState.Right != m_MouseRight && mouseState.Right == KeyState::Released ||
		mouseState.X1 != m_MouseX1 && mouseState.X1 == KeyState::Released ||
		mouseState.X2 != m_MouseX2 && mouseState.X2 == KeyState::Released) && m_MouseOver && m_MouseDown)
	{
		m_MouseLeft = mouseState.Left;
		m_MouseMiddle = mouseState.Middle;
		m_MouseRight = mouseState.Right;
		m_MouseX1 = mouseState.X1;
		m_MouseX2 = mouseState.X2;

		//dispach event
		MouseEvent* ev = new MouseEvent();
		ev->State = mouseState;
		ev->Button = m_ButtonDown;
		printf("Mouse up\n");

		OnMouseUp.SetEvent(this, ev);
		m_MouseDown = false;
		m_Clicks += 1;
		m_DoubleClickTimer.Start(); //start the double click timer

		ev = new MouseEvent();
		ev->State = mouseState;
		ev->Button = m_ButtonDown;
		printf("Mouse click\n");
		OnMouseClick.SetEvent(this, ev);

		//OnMouseDoubleClick Occurs when a mouse button is clicked two or more times.
		if (m_Clicks > 1)
		{
			ev = new MouseEvent();
			ev->State = mouseState;
			ev->Button = m_ButtonDown;
			OnMouseDoubleClick.SetEvent(this, ev);
			m_Clicks = 0;
			printf("Double Click\n");
		}
		m_ButtonDown = MouseButtons::None;
	}

	//mouse scroll
	if ((m_MouseOver || m_HasFocus) &&
		(mouseState.Wheel.Y != 0 ||
		 mouseState.Wheel.X != 0))
	{
		MouseEvent* ev = new MouseEvent();
		ev->State = mouseState;
		printf("Mouse Scroll\n");

		OnMouseScroll.SetEvent(this, ev);
	}

	//OnMouseMove Occurs when the mouse pointer is moved over the control.
	if (m_MouseOver && m_LastPosition != mouseState.Location)
	{
		m_MouseMove = true;
		m_LastPosition = mouseState.Location;
		m_Clicks = 0;

		MouseEvent* ev = new MouseEvent();
		OnMouseMove.SetEvent(this, ev);
	}
	else
		m_MouseMove = false;

	for (IUIControl* c : m_Controls)
	{
		c->Update(keystate, mouseState);
	}
}

void IUIControl::Draw()
{
	if (!m_Visable)
		return;

	for (IUIControl* c : m_Controls)
	{
		c->Draw();
	}
}

Vector2 IUIControl::GetDrawLocation()
{
	Vector2 res = m_Location;

	if (m_Parent)
		res += m_Parent->GetDrawLocation();

	return res;
}

IUIControl * IUIControl::GetParent()
{
	return m_Parent;
}

void IUIControl::AddControl(IUIControl * control)
{
	m_Controls.push_back(control);
	control->m_Parent = this;
}

void IUIControl::RemoveControl(IUIControl * control)
{
	auto res = std::find(m_Controls.begin(), m_Controls.end(), control);
	if (res != m_Controls.end())
	{
		m_Controls.erase(res);
	}
}

std::vector<IUIControl*> IUIControl::GetControls()
{
	return m_Controls;
}
