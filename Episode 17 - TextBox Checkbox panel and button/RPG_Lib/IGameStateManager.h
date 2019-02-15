#pragma once
#include "GameStateManager.h"

class IGameStateManager : public GameStateManager
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;;
};