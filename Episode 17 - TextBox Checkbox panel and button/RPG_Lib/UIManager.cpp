#include "UIManager.h"

#include "Keyboard.h"
#include "Mouse.h"

void UIManager::Update()
{
	KeyboardState keystate = Keyboard::GetState();
	MouseState mouseState = Mouse::GetState();

	for (IUIControl* c : Controls)
	{
		c->Update(keystate, mouseState);
	}
}

void UIManager::Draw()
{
	for (IUIControl* c : Controls)
	{
		c->Draw();
	}
}
