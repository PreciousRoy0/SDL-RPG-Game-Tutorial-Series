#pragma once

#include "Singleton.h"
#include "IGameState.h"

class GameStateManager : public UnCopyable
{
protected:
	IGameState* m_CurrentState = nullptr;

	GameStateManager() {}
	friend Singleton<GameStateManager>;

public:
	IGameState* GetState() { return m_CurrentState; }

	void SetState(IGameState* gs);

	virtual void Run();

	virtual void Update();
	virtual void Draw();
};

typedef Singleton<GameStateManager> TheGameStateManager;