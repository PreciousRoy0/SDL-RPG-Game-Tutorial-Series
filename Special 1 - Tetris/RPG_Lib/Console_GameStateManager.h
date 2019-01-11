#pragma once

#include "GameStateManager.h"


class Console_GameStateManager : public GameStateManager 
{
	Console_GameStateManager() {}
	friend Singleton<Console_GameStateManager>;

public:

	virtual void Update() override;
	virtual void Draw() override;
};

typedef Singleton<Console_GameStateManager> TheConsoleGameStateManager;