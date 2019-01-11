#pragma once

#include "IGameState.h"
#include "Menu.h"
#include "TertisBlock.h"

#include <vector>

class MainGameState : public IGameState
{
	MainGameState() {}
	friend Singleton<MainGameState>;

	Rectangle2d m_GameBounds;
	Rectangle2d m_NextBox;

	Point m_StartPosition;
	PointF m_NewPosition;
	TetrisBlock m_CurrentBlock = (PointF(6, 2));
	TetrisBlock m_NextBlock = (PointF(18, 3));
	std::vector<Block> m_GameBlocks;

	void StopTetrisBlock();

public:

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void DeInitialize() override;


};

typedef Singleton<MainGameState> TheMainGameState;