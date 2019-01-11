#pragma once

#include "Singleton.h"
#include "Size.h"
#include "Point.h"
#include "Rectangle.h"
#include "Console_Color.h"

class Console_Screen : public UnCopyable
{
	Console_Screen();
	friend Singleton<Console_Screen>;

	HANDLE m_ConsoleHandle = NULL;
	CONSOLE_CURSOR_INFO     m_CursorInfo;
	Size m_Size;

public:

	void SetSize(Size screensize);
	Size& GetSize();

	void SetColor(ConsoleColor Color);

	void SetCursorPosition(Point point);
	void SetDrawRect(Rectangle2d rect);
};


typedef Singleton<Console_Screen> TheConsoleScreen;