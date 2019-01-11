#include "OptionsState.h"
#include "MainMenuState.h"

void OptionsState::Initialize()
{
	SetMenuName("Options Menu");
	Menu::Reset();

	AddMenuItem(MenuItem("Back", TheMainMenuState::Pointer(), true));

	Menu::Initialize();
}


void OptionsState::Update()
{
	Menu::Update();
}

void OptionsState::Draw()
{
}

void OptionsState::DeInitialize()
{
}

