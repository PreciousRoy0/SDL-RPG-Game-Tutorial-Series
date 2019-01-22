#include "SDL_EventHandeler.h"

#include <SDL.h>
#include "SDL_GameStateManager.h"

#include "Keyboard.h"
#include "Mouse.h"

void SDL_EventHandeler::PoolEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT:
			TheSDLGameStateManager::Pointer()->HandelEvent(&event.window);
			break;

		case SDL_KEYDOWN:
		case SDL_KEYUP:
			Keyboard::HandelEvent(&event.key);
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
			Mouse::HandelEvent(&event);
			break;
		}
	}
}
