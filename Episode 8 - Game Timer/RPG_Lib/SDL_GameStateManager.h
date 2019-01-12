#pragma once

#include "IGameStateManager.h"
struct SDL_WindowEvent;

class SDL_GameStateManager : public IGameStateManager
{
	friend Singleton<SDL_GameStateManager>;
	SDL_GameStateManager() {}

	//event steff
	friend class SDL_EventHandeler;
	void HandelEvent(SDL_WindowEvent* winEvent);

public:
	
	virtual void Update() override;
	virtual void Draw() override;
};

typedef	Singleton<SDL_GameStateManager> TheSDLGameStateManager;