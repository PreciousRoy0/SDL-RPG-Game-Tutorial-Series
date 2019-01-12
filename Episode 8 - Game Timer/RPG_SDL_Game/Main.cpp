// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "SDL_ScreenHandeler.h"
#include "SDL_GameStateManager.h"

#include "SDL_Image.h"
#include "SDL_SpriteSheet.h"
#include "SDL_Timer.h"

class TestState : public IGameState
{
	friend Singleton<TestState>;
	TestState() {}

	SDL_Image img;
	SDL_SpriteSheet spr;
	Vector2F location;

public:
	virtual void Update() override
	{
		location.X += SDL_Timer::GetDT() * 100;
	}

	virtual void Draw() override
	{
		img.Draw(Vector2(40, 40));
		spr.Draw(23, location);
	}

	virtual void DeInitialize() override
	{
	}

	virtual void Initialize()
	{
		img.Load("Media/PRoy.jpg");
		spr.Load("Media/tilemap_packed.png", Size(16,16));
		location = {10, 300};
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