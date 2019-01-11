#include "TertisBlock.h"

#include <stdlib.h>     /* srand, rand */

char A_TetrisChar[4] = { 176, 177, 178, 219};

ConsoleColor A_TetrisColor[13] = {
	ConsoleColor::ConsoleTextColor_DarkRed,
	ConsoleColor::ConsoleTextColor_DarkGreen,
	ConsoleColor::ConsoleTextColor_DarkBlue,
	ConsoleColor::ConsoleTextColor_DarkMagenta,
	ConsoleColor::ConsoleTextColor_DarkYellow,
	ConsoleColor::ConsoleTextColor_DarkCyan,
	ConsoleColor::ConsoleTextColor_Red,
	ConsoleColor::ConsoleTextColor_Green,
	ConsoleColor::ConsoleTextColor_Blue,
	ConsoleColor::ConsoleTextColor_Magenta,
	ConsoleColor::ConsoleTextColor_Yellow,
	ConsoleColor::ConsoleTextColor_Cyan,
	ConsoleColor::ConsoleTextColor_White
};

int A_TetrisBlock[7][12] = 
{
	{1,1,1,1,
	 0,0,0,0,
	 0,0,0,0},

	{1,1,0,0,
	 0,1,1,0,
	 0,0,0,0},
	
	{1,1,1,0,
	 0,0,1,0,
	 0,0,0,0},
	
	{1,1,0,0,
	 1,1,0,0,
	 0,0,0,0},
	
	{0,1,1,0,
	 1,1,0,0,
	 0,0,0,0},
	
	{1,1,1,0,
	 1,0,0,0,
	 0,0,0,0},
	
	{0,1,0,0,
	 1,1,1,0,
	 0,0,0,0}
};

void TetrisBlock::NormalizeCords()
{
	for (size_t i = 0; i < m_Blocks.size(); i++)
	{
		PointF pos = GetPosition();
		pos = (pos + m_Blocks[i].m_LocalCord);

		m_Blocks[i].SetPosition(pos);
	}
}

void TetrisBlock::NormalizeCords2()
{
	for (size_t i = 0; i < m_Blocks.size(); i++)
	{
		PointF pos = GetPosition();
		pos = (pos + m_Blocks[i].m_LocalCord);

		m_Blocks[i].SetPosition2(pos);
	}
}

TetrisBlock::TetrisBlock(PointF pos)
{
	m_OldPosition = pos;
	m_Position = pos;
}

int TetrisBlock::RelativeXMin()
{
	int wmin = 10;

	for (int i = 0; i < m_Blocks.size(); i++)
	{
		if (m_Blocks[i].m_LocalCord.X < wmin)
			wmin = m_Blocks[i].m_LocalCord.X;
	}

	return wmin;
}

int TetrisBlock::RelativeXMax()
{
	int wmax = -10;

	for (int i = 0; i < m_Blocks.size(); i++)
	{
		if (m_Blocks[i].m_LocalCord.X > wmax)
			wmax = m_Blocks[i].m_LocalCord.X;
	}

	return wmax;
}

int TetrisBlock::RelativeYMax()
{
	int wmax = -10;

	for (int i = 0; i < m_Blocks.size(); i++)
	{
		if (m_Blocks[i].m_LocalCord.Y > wmax)
			wmax = m_Blocks[i].m_LocalCord.Y;
	}

	return wmax;
}

int TetrisBlock::GetWidth()
{
	int wmin = 10;
	int wmax = -10;
	
	for (int i = 0; i < m_Blocks.size(); i++)
	{
		if (m_Blocks[i].m_LocalCord.X > wmax)
			wmax = m_Blocks[i].m_LocalCord.X;
		if(m_Blocks[i].m_LocalCord.X < wmin)
			wmin = m_Blocks[i].m_LocalCord.X;
	}

	int temp = abs(wmax - wmin);
	return temp;
}

int TetrisBlock::GetHeight()
{
	int h = 1;

	for (int i = 0; i < m_Blocks.size(); i++)
		if (m_Blocks[i].m_LocalCord.Y > h)
			h = m_Blocks[i].m_LocalCord.Y;

	return h;
}

void TetrisBlock::SetPosition(PointF newPos)
{
	m_OldPosition = m_Position;
	m_Position = newPos;

	NormalizeCords();
}

void TetrisBlock::SetPosition2(PointF newPos)
{
	m_OldPosition = newPos;
	m_Position = newPos;

	NormalizeCords();
}

void TetrisBlock::GenerateRandomBlock()
{
	int ran = rand() % 7;
	char c = A_TetrisChar[rand() % 3];
	ConsoleColor co = A_TetrisColor[rand() % 13];
	
	for (size_t i = 0; i < 12; i++)
	{
		if (A_TetrisBlock[ran][i] == 1)
		{
			Block b;
			b.Charecter = c;
			b.Color = co;

			PointF p;
			p.X = i % 4;
			p.Y = i / 4;
			b.m_LocalCord = p;
			
			m_Blocks.push_back(b);
		}
	}
	NormalizeCords2();
}

void TetrisBlock::Rotate()
{
	/*
			tmp.m_Blocks[i].Offset = PointI(
			((0 * Difrance.X) + (-1 * Difrance.Y)),
			((1 * Difrance.X) + (0 * Difrance.Y)));
	*/

	Clear();

	for (int i = m_Blocks.size() - 1; i >= 0; i--)
	{
		m_Blocks[i].m_LocalCord = PointF(
			((0 * m_Blocks[i].m_LocalCord.X) + (-1 * m_Blocks[i].m_LocalCord.Y)),
			((1 * m_Blocks[i].m_LocalCord.X) + (0 * m_Blocks[i].m_LocalCord.Y)));
	}

	NormalizeCords();
}

bool TetrisBlock::Colliding(Block b)
{
	for (int i = 0; i < m_Blocks.size(); i++)
	{
		if (Point(b.m_Position) == Point(m_Blocks[i].m_Position))
			return true;
	}

	return false;
}

void TetrisBlock::Draw(bool force)
{
	if (force) {}

	else if (Point(m_Position.X, m_Position.Y) == Point(m_OldPosition.X, m_OldPosition.Y))
		return;

	Clear();

	for (int i = m_Blocks.size()- 1; i >= 0; i--)
	{
		m_Blocks[i].Draw(false);
	}
}

void TetrisBlock::Clear()
{
	for (int i = m_Blocks.size() - 1; i >= 0; i--)
	{
		m_Blocks[i].Clear();
	}
}

std::vector<Block> TetrisBlock::Destroy()
{
	return m_Blocks;
}
