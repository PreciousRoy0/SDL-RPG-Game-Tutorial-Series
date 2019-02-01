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
#include "MouseUpEvent.h"


class TestState : public IGameState
{
	friend Singleton<TestState>;
	TestState() {}

	SDL_Image img;
	SDL_TileSheet spr;
	SDL_SpriteSheet spr2;
	EventListener spr2list;
	Vector2 spr2loc = Vector2(300, 200);

	Vector2F location;

	XML xmlDoc;
	SDL_SpriteFont font;
	SDL_TTFFont font2;



public:

	void OnMousUpEvent(IEvent* ev)
	{
		MouseUpEvent* mev = dynamic_cast<MouseUpEvent*>(ev);
		spr2loc.X = mev->x;
		spr2loc.Y = mev->y;
	}

	virtual void Initialize()
	{
		img.Load("Media/PRoy.jpg");
		spr.Load("Media/tilemap_packed.png");
		spr.SetCellSize(Size(16, 16));

		spr2.Load("Media/greySheet.xml");

		location = { 10, 300 };

		xmlDoc.Load("Media/KenPixel.xml");
		font.Load(&xmlDoc);

		font2.Load("Media/kenpixel_blocks.ttf");
		font2.SetSize(30);

		spr2list.AddListener(spr2list.Bind(&TestState::OnMousUpEvent, this));
	}

	virtual void Update() override
	{
		KeyboardState state = Keyboard::GetState();
		MouseState mState = Mouse::GetState();

		if (state.IsKeyDown(Keys::SPACE))
		{
			MouseUpEvent* ev = new MouseUpEvent;
			ev->x = mState.Location.X;
			ev->y = mState.Location.Y;
			spr2list.SetEvent(ev);
		}

		//if(state.IsKeyDown(Keys::d))
		//	location.X += SDL_Timer::GetDT() * 100;
		//if (state.IsKeyDown(Keys::a))
		//	location.X -= SDL_Timer::GetDT() * 100;

		location = mState.Location;
	}

	virtual void Draw() override
	{
		img.Draw(Vector2(40, 40));
		spr.Draw(23, location);

		spr2.Draw("grey_button00", spr2loc);

		font.DrawString("<Hello wold ;}> & \"", Vector2(50, 300));

		font2.DrawString("<Hello wold 2 ;}> & \"", Vector2(50, 400));
	}

	virtual void DeInitialize() override
	{
	}
};

typedef  Singleton<TestState> TheTestState;

class TestType : public IAsset
{
	int i = 0;

public:

	virtual bool Load(const std::string & fileName) override
	{
		i = 1000;
		return false;
	}

};

class TestType2 : public IAsset
{
	char i = ' ';

public:

	virtual bool Load(const std::string & fileName) override
	{
		i = 'd';
		return false;
	}

};

int main(int argc, char* argv[])
{
	//TheAssetManager::Pointer()->LoadAsset<TestType>("Fake");
	//TestType2* tmp = TheAssetManager::Pointer()->GetAsset<TestType2>("Fake");
	
	TheSDLScreenHandeler::Pointer()->Initialize("SDL RPG Game", Size(1024, 768));
	TheSDLScreenHandeler::Pointer()->SetBackBufferColor(SDL_Color{ 100, 149, 237, 255 });
	TheSDLGameStateManager::Pointer()->SetState(TheTestState::Pointer());
	TheSDLGameStateManager::Pointer()->Run();

	return 0;
}