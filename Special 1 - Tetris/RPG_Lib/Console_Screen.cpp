#include "Console_Screen.h"
#include <iostream>

Console_Screen::Console_Screen()
{
	m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
	m_CursorInfo.bVisible = false;
	SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
}

void Console_Screen::SetSize(Size screensize)
{
	m_Size = screensize;

	_COORD coord;
	coord.X = screensize.Width;
	coord.Y = screensize.Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = screensize.Height - 1;
	Rect.Right = screensize.Width - 1;

	SetConsoleWindowInfo(m_ConsoleHandle, TRUE, &Rect);            // Set Window Size 
	bool t = SetConsoleScreenBufferSize(m_ConsoleHandle, coord);            // Set Buffer Size 
}

Size& Console_Screen::GetSize()
{
	return m_Size;
}

void Console_Screen::SetColor(ConsoleColor Color)
{
	SetConsoleTextAttribute(m_ConsoleHandle, (WORD)Color);
}

void Console_Screen::SetCursorPosition(Point point)
{
	COORD coord;
	coord.X = point.X;
	coord.Y = point.Y;

	if (!SetConsoleCursorPosition(m_ConsoleHandle, coord))
	{
		throw "i went poopie";
	}

}

void Console_Screen::SetDrawRect(Rectangle2d rect)
{
	char lTop = 201;
	char rTop = 187;
	char verticl = 186;
	char lBottom = 200;
	char rBottom = 188;
	char horizontal = 205;

	for (size_t r = rect.Y; r < (rect.Y + rect.Height) + 2; r++)
	{
		for (size_t c = rect.X; c < (rect.X + rect.Width) + 2; c++)
		{
			Point p;
			p.Y = r;
			p.X = c;
			char toprint = lTop;

			//Top left right
			if (r == rect.Y && c == rect.X)
				toprint = lTop;
			else if (r == rect.Y && c == (rect.X + rect.Width) + 1)
				toprint = rTop;

			//bottom left right
			else if (r == (rect.Y + rect.Height) + 1 && c == rect.X)
				toprint = lBottom;
			else if (r == (rect.Y + rect.Height) + 1 && c == (rect.X + rect.Width) + 1 )
				toprint = rBottom;
			
			//horizontal
			else if (r == rect.Y || r == (rect.Y + rect.Height)+1)
				toprint = horizontal;

			//vertical
			else if (c == rect.X || c == (rect.X + rect.Width)+ 1)
				toprint = verticl;
			else
				continue;

			SetCursorPosition(p);
			char cc[]{ toprint, '\0' };
			printf(cc);
		}
	}

}
