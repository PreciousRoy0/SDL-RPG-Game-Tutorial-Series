
#include <iostream>
#include "Console_Screen.h"
#include "Console_GameStateManager.h"

#include "MainMenuState.h"
#include "MainGameState.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "TertisBlock.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));

	TheConsoleScreen::Pointer()->SetSize(Size(23, 24));
	TheConsoleGameStateManager::Pointer()->SetState(TheMainGameState::Pointer());
	TheConsoleGameStateManager::Pointer()->Run();

	return 0;
}