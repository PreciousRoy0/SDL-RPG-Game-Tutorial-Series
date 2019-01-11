#pragma once

#include "Singleton.h"

class Console_InputHandeler : public UnCopyable
{
	Console_InputHandeler() {};
	friend Singleton <Console_InputHandeler>;

public:
	void HandelKeyEvent();

};

typedef Singleton <Console_InputHandeler> TheConsoleInputHandeler;