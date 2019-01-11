#pragma once

#include "Singleton.h"

class IGameState
{
public:

	virtual ~IGameState() = 0 {}

	//Gets called when the state first gets set
	virtual void Initialize() = 0;

	virtual void Update() = 0;
	virtual void Draw() = 0;

	//Gets called when the state changes
	virtual void DeInitialize() = 0;
};