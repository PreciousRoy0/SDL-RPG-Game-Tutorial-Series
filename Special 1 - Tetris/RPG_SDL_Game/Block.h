#pragma once

#include "Point.h"
#include "Console_Color.h"

class Block
{
	PointF m_LocalCord;

	PointF m_Position;
	PointF m_OldPosition;

	friend class TetrisBlock;
	void UpdateOldPosition(PointF oldPos) { m_OldPosition = oldPos;};

	void SetPosition2(PointF newPos);

public:
	ConsoleColor Color;
	char Charecter;

	PointF GetPosition() { return m_Position; };
	void SetPosition(PointF newPos);

	void Clear();
	void Draw(bool clear = true);
};