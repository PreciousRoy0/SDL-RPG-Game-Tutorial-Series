// Example program:
// Using SDL2 to create an application window

#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "SDL_ScreenHandeler.h"
#include "SDL_GameStateManager.h"

#include "SDL_Image.h"
#include "SDL_TileSheet.h"
#include "SDL_SpriteSheet.h"
#include "SDL_Timer.h"
#include "Keyboard.h"
#include "Mouse.h"

#include "XML.h"
#include "SDL_SpriteFont.h"
#include "SDL_TTFFont.h"

#include "AssetManager.h"

#include "EventPoller.h"
#include "UIManager.h"

#include "UI_Lable.h"



class TestState : public IGameState, public UIManager
{
	friend Singleton<TestState>;
	TestState() {}

	SDL_TTFFont font;


	UI_Lable label = (this);

public:


	virtual void Initialize()
	{
		SetDebugMode(true);

		font.Load("Media/kenpixel_blocks.ttf");
		font.SetSize(20);

		label.SetFont(&font);
		label.SetLocation({ 200,200 });
		label.SetText("Hello world");

		Controls.push_back(&label);
	}

	virtual void Update() override
	{
		KeyboardState state = Keyboard::GetState();
		MouseState mState = Mouse::GetState();



		UIManager::Update();
	}

	virtual void Draw() override
	{


		UIManager::Draw();
	}

	virtual void DeInitialize() override
	{
	}
};

typedef  Singleton<TestState> TheTestState;


int main(int argc, char* argv[])
{
	TheSDLScreenHandeler::Pointer()->Initialize("SDL RPG Game", Size(1024, 768));
	TheSDLScreenHandeler::Pointer()->SetBackBufferColor(Color{ 100, 149, 237, 255 });
	TheSDLGameStateManager::Pointer()->SetState(TheTestState::Pointer());
	TheSDLGameStateManager::Pointer()->Run();

	return 0;
}