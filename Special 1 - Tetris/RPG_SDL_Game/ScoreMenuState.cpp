#include "ScoreMenuState.h"

#include "MainMenuState.h"

void ScoreMenuState::Initialize()
{
	SetMenuName("Options Menu");
	Menu::Reset();

	AddMenuItem(MenuItem("Back", TheMainMenuState::Pointer(), true));

	Menu::Initialize();
}

void ScoreMenuState::Update()
{
	Menu::Update();
}

void ScoreMenuState::Draw()
{

}

void ScoreMenuState::DeInitialize()
{

}


