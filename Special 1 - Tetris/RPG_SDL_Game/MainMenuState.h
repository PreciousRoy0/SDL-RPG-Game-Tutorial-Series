#pragma once

#include "IGameState.h"
#include "Menu.h"

class MainMenuState : public IGameState, public Menu
{
	MainMenuState() {}
	friend Singleton<MainMenuState>;
	
public:

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DeInitialize() override;

	virtual void Initialize();

};

typedef Singleton<MainMenuState> TheMainMenuState;