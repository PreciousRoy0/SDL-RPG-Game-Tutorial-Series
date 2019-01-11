// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "SDL_ScreenHandeler.h"

int main(int argc, char* argv[])
{
	SDL_ScreenHandeler* handeler = TheSDLScreenHandeler::Pointer();
	handeler->Initialize("SDL RPG Game", Size(1024, 768));
	handeler->SetBackBufferColor(SDL_Color{ 100, 149, 237, 255 });

	while (true)
	{
		handeler->Flip();
	}

	return 0;
}