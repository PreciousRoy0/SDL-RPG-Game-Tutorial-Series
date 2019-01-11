#include "Block.h"
#include <iostream>
#include "Console_Screen.h"


void Block::SetPosition(PointF newPos)
{
	m_OldPosition = m_Position;
	m_Position = newPos;
}

void Block::SetPosition2(PointF newPos)
{
	m_OldPosition = newPos;
	m_Position = newPos;
}

void Block::Clear()
{
	// Remove old position
	TheConsoleScreen::Pointer()->SetCursorPosition(Point(m_OldPosition.X, m_OldPosition.Y));
	TheConsoleScreen::Pointer()->SetColor(ConsoleColor::ConsoleTextColor_White);
	char c[2] = { ' ', '\0' };
	printf(c);
}

void Block::Draw(bool clear)
{
	if (Point(m_Position.X, m_Position.Y) == Point(m_OldPosition.X, m_OldPosition.Y))
		return;

	if (clear)
		Clear();

	//New block
	TheConsoleScreen::Pointer()->SetCursorPosition(Point(m_Position.X, m_Position.Y));
	TheConsoleScreen::Pointer()->SetColor(Color);
	char c[2] = { Charecter, '\0' };
	printf(c);
	TheConsoleScreen::Pointer()->SetColor(ConsoleColor::ConsoleTextColor_White);
}
