#pragma once

#include "Block.h"
#include "Point.h"
#include <vector>

class TetrisBlock
{
	PointF m_Position;
	PointF m_OldPosition;
	std::vector<Block> m_Blocks;

	void NormalizeCords();
	void NormalizeCords2();

public:

	TetrisBlock(PointF pos);

	int RelativeXMin();
	int RelativeXMax();
	int RelativeYMax();

	int GetWidth();
	int GetHeight();
	PointF GetPosition() { return m_Position; };
	void SetPosition(PointF newPos);
	void SetPosition2(PointF newPos); //used to move new block
	void GenerateRandomBlock();

	void Rotate();
	bool Colliding(Block b);

	void Draw(bool force = false);
	void Clear();

	std::vector<Block> Destroy();
};
