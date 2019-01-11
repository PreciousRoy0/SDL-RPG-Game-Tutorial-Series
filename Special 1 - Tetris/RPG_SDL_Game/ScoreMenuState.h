#pragma once

#include "IGameState.h"
#include "Menu.h"

class ScoreMenuState : public IGameState, public Menu
{
	ScoreMenuState() {}
	friend Singleton<ScoreMenuState>;

public:

	virtual void Update() override;

	virtual void Draw() override;

	virtual void DeInitialize() override;

	virtual void Initialize();

};

typedef Singleton<ScoreMenuState> TheScoreMenuState;