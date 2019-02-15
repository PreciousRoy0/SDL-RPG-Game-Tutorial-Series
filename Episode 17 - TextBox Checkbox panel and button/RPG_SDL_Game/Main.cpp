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
#include "TextBox.h"
#include "Button.h"
#include "CheckBox.h"
#include "Panel.h"

#include "CheckedEvent.h"



class TestState : public IGameState, public UIManager
{
	friend Singleton<TestState>;
	TestState() {}

	SDL_TileSheet* UiSheet;
	SDL_TTFFont* font12;

	UI_Lable* label;
	TextBox* box;
	Button* button;
	Button* Iconbutton;
	CheckBox* cBox;
	Panel* pan;

public:

	void OnCheckBoxChecked(void* sender, IEvent* ev)
	{
		SetDebugMode(((CheckedEvent*)ev)->CheckedState);
	}

	virtual void Initialize()
	{
		SetDebugMode(true);

		TheAssetManager::Pointer()->LoadAsset<SDL_TTFFont>("Media/kenvector_future12.ttf");
		font12 = TheAssetManager::Pointer()->GetAsset<SDL_TTFFont>("Media/kenvector_future12.ttf");
		font12->SetSize(12);

		TheAssetManager::Pointer()->LoadAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");
		UiSheet = TheAssetManager::Pointer()->GetAsset<SDL_TileSheet>("Media/UIpackSheet_transparent32.png");

		//dont forget to calculate the tiles
		UiSheet->CalculateCellSize(Size(32, 32), 4);

		label = CreateControl<UI_Lable>();
		box = CreateControl<TextBox>();
		button = CreateControl<Button>();
		Iconbutton = CreateControl<Button>();
		cBox = CreateControl<CheckBox>();
		pan = CreateControl<Panel>();

		label->SetText("Label test.");
		label->SetFont(font12);
		label->SetLocation({ 20, 10 });

		box->SetText("");
		box->SetFont(font12);
		box->SetLocation({ 20, 50 });
		box->SetSize(font12->MeasureString("s"));
		box->GetSize().Width = 200;
		box->SetBG(true);

		button->SetText("Button test.");
		button->SetFont(font12);
		button->SetLocation({ 20, 90 });
		button->SetSize(Size(130, 32));

		Iconbutton->SetFont(font12);
		Iconbutton->SetLocation({ 20, 130 });
		Iconbutton->SetSize(Size(32, 32));
		Iconbutton->SetButtonType(ButtonType::ICON_ONLY);
		Iconbutton->SetIcon(275);

		cBox->SetFont(font12);
		cBox->SetLocation({ 20, 170 });
		cBox->SetSize(Size(32, 32)); //does not include lable
		cBox->SetText("Checked lable");
		cBox->SetChecked(GetDebugMode());
		cBox->OnChecked.AddListener(Bind(&TestState::OnCheckBoxChecked, this));

		pan->SetLocation(Vector2(240, 100));
		pan->SetSize(Size(300, 300));
		pan->AddControl(label);
		pan->AddControl(box);
		pan->AddControl(button);
		pan->AddControl(Iconbutton);
		pan->AddControl(cBox);

		pan->SetBG(true);

		Controls.push_back(pan);
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