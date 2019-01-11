#pragma once

#include "IGameState.h"
#include "Menu.h"

class OptionsState : public IGameState, public Menu
{
	OptionsState() {}
	friend Singleton<OptionsState>;

public:
	virtual void Update() override;

	virtual void Draw() override;

	virtual void DeInitialize() override;

	virtual void Initialize();

};

typedef Singleton<OptionsState> TheOptionsState;
