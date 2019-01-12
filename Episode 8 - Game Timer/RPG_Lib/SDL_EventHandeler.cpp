#include "SDL_EventHandeler.h"

#include <SDL.h>
#include "SDL_GameStateManager.h"

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
		}
	}
}
