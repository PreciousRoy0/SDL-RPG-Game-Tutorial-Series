#include "Console_GameStateManager.h"
#include <conio.h>

#include "Console_InputHandeler.h"
#include "Console_Timer.h"
#include "Keyboard.h"

void Console_GameStateManager::Update()
{
	Console_Timer::UpdateTimer();
	Keyboard::GetState().Reset();
	TheConsoleInputHandeler::Pointer()->HandelKeyEvent();

	GameStateManager::Update();
}

void Console_GameStateManager::Draw()
{
	GameStateManager::Draw();
}
