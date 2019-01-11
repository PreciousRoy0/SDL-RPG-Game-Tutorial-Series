#include "MainMenuState.h"

#include "Keyboard.h"
#include <iostream>

#include "MainGameState.h"
#include "ScoreMenuState.h"
#include "OptionsState.h"

void MainMenuState::Initialize()
{
	SetMenuName("Main Menu");
	Menu::Reset();
	AddMenuItem(MenuItem("New Game", TheMainGameState::Pointer(), true));
	AddMenuItem(MenuItem("Score", TheScoreMenuState::Pointer()));
	AddMenuItem(MenuItem("Options", TheOptionsState::Pointer()));
	AddMenuItem(MenuItem("Exit", nullptr));

	Menu::Initialize();
}

void MainMenuState::Update()
{
	Menu::Update();
}

void MainMenuState::Draw()
{
}

void MainMenuState::DeInitialize()
{
}


