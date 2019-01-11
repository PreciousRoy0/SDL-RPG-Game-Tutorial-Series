#include "Console_InputHandeler.h"
#include <conio.h>
#include "Keyboard.h"

void Console_InputHandeler::HandelKeyEvent()
{
	while (_kbhit())
	{
		short kt = _getch();
		Keyboard::GetState().SetKeyState(kt);
	}
}
