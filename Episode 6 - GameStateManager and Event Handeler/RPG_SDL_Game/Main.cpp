// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "SDL_ScreenHandeler.h"
#include "SDL_GameStateManager.h"

class TestState : public IGameState
{
	friend Singleton<TestState>;
	TestState() {}

public:
	virtual void Update() override
	{
	}

	virtual void Draw() override
	{
	}

	virtual void DeInitialize() override
	{
	}

	virtual void Initialize()
	{
	}

};

typedef  Singleton<TestState> TheTestState;

int main(int argc, char* argv[])
{
	TheSDLScreenHandeler::Pointer()->Initialize("SDL RPG Game", Size(1024, 768));
	TheSDLScreenHandeler::Pointer()->SetBackBufferColor(SDL_Color{ 100, 149, 237, 255 });
	TheSDLGameStateManager::Pointer()->SetState(TheTestState::Pointer());
	TheSDLGameStateManager::Pointer()->Run();

	return 0;
}