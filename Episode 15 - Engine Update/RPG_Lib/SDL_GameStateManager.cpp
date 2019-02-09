#include "SDL_GameStateManager.h"

#include <SDL.h>
#include "EventPoller.h"
#include "SDL_EventHandeler.h"
#include "SDL_ScreenHandeler.h"
#include "SDL_Timer.h"
#include "Keyboard.h"
#include "Mouse.h"

void SDL_GameStateManager::HandelEvent(SDL_WindowEvent* winEvent)
{
	switch (winEvent->event) {
	case SDL_WINDOWEVENT_SHOWN:
		SDL_Log("Window %d shown", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_HIDDEN:
		SDL_Log("Window %d hidden", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_EXPOSED:
		SDL_Log("Window %d exposed", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_MOVED:
		SDL_Log("Window %d moved to %d,%d",
			winEvent->windowID, winEvent->data1,
			winEvent->data2);
		break;
	case SDL_WINDOWEVENT_RESIZED:
		SDL_Log("Window %d resized to %dx%d",
			winEvent->windowID, winEvent->data1,
			winEvent->data2);
		break;
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		SDL_Log("Window %d size changed to %dx%d",
			winEvent->windowID, winEvent->data1,
			winEvent->data2);
		break;
	case SDL_WINDOWEVENT_MINIMIZED:
		SDL_Log("Window %d minimized", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_MAXIMIZED:
		SDL_Log("Window %d maximized", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_RESTORED:
		SDL_Log("Window %d restored", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_ENTER:
		SDL_Log("Mouse entered window %d",
			winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_LEAVE:
		SDL_Log("Mouse left window %d", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_FOCUS_GAINED:
		SDL_Log("Window %d gained keyboard focus",
			winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
		SDL_Log("Window %d lost keyboard focus",
			winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_CLOSE:
		SDL_Log("Window %d closed", winEvent->windowID);
		TheSDLGameStateManager::Pointer()->SetState(nullptr);
		break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
	case SDL_WINDOWEVENT_TAKE_FOCUS:
		SDL_Log("Window %d is offered a focus", winEvent->windowID);
		break;
	case SDL_WINDOWEVENT_HIT_TEST:
		SDL_Log("Window %d has a special hit test", winEvent->windowID);
		break;
#endif
	default:
		SDL_Log("Window %d got unknown event %d",
			winEvent->windowID, winEvent->event);
		break;
	}
}

void SDL_GameStateManager::Update()
{
	//game timer
	SDL_Timer::UpdateTimer();
	//events
	Keyboard::PreUpdate();
	Mouse::PreUpdate();
	TheSDLEventHandeler::Pointer()->PoolEvents();

	GameStateManager::Update();
	TheEventPoller::Pointer()->CheckEvents();
}

void SDL_GameStateManager::Draw()
{
	GameStateManager::Draw();
	TheSDLScreenHandeler::Pointer()->Flip();
}
