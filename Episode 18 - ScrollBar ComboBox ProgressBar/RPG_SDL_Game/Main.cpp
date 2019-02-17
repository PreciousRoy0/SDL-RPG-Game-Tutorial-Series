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

#include "SDL_Time.h"
#include "EventPoller.h"
#include "UIManager.h"

#include "CheckedEvent.h"

#include "TextBox.h"
#include "UI_Lable.h"
#include "Button.h"
#include "CheckBox.h"
#include "ProgressBar.h"
#include "VScrollbar.h"
#include "Panel.h"
#include "ComboBox.h"

class TestState : public IGameState, protected UIManager
{
	friend Singleton<TestState>;
	TestState() {}

	SDL_TileSheet* UiSheet;
	SDL_TTFFont* font20;
	SDL_TTFFont* font12;

	UI_Lable* label;
	TextBox* box;
	Button* button;
	Button* Iconbutton;
	CheckBox* cBox;
	ProgressBar* bar;
	VScrollBar* vbar;
	Panel* pan;
	ComboBox* Combox;

	SDL_Timer time;

public:

	void OnMouseUp(void* sender, IEvent* ev)
	{

	}

	void OnCheckBoxChecked(void* sender, IEvent* ev)
	{
		SetDebugMode(((CheckedEvent*)ev)->CheckedState);
	}

	void OnScroll(void* sender, IEvent* ev)
	{
		pan->SetLocation(Vector2(240, 100) + Vector2(vbar->GetValue(), 0));
	}

	virtual void Initialize()
	{
		SetDebugMode(false);
		//TheAssetManager::Pointer()->LoadAsset<SDL_SpriteSheet>("Media/greySheet.xml");
		TheAssetManager::Pointer()->LoadAsset<SDL_TTFFont>("Media/kenvector_future_thin.ttf");
		font20 = TheAssetManager::Pointer()->GetAsset<SDL_TTFFont>("Media/kenvector_future_thin.ttf");
		font20->SetSize(20);

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
		bar = CreateControl<ProgressBar>();
		vbar = CreateControl<VScrollBar>();
		pan = CreateControl<Panel>();
		Combox = CreateControl<ComboBox>();

		label->SetText("Label test.");
		label->SetFont(font12);
		label->SetLocation({ 20, 10 });

		box->SetText("text");
		box->SetFont(font12);
		box->SetLocation({ 20, 50 });
		box->SetSize(font12->MeasureString(box->GetText()));
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

		bar->SetFont(font12);
		bar->SetLocation({ 20, 210 });
		bar->SetSize(Size(250, 28));

		vbar->SetLocation({ 200, 100 });
		vbar->SetSize(Size(32, 200));
		vbar->SetMaxValue(100);
		vbar->SetValue(50);
		vbar->OnScroll.AddListener(Bind<TestState>(&TestState::OnScroll, this));

		pan->SetLocation(Vector2(240, 100) + Vector2(vbar->GetValue(), 0));
		pan->SetSize(Size(300, 300));
		pan->AddControl(label);
		pan->AddControl(box);
		pan->AddControl(button);
		pan->AddControl(Iconbutton);
		pan->AddControl(cBox);
		pan->AddControl(bar);
		pan->AddControl(Combox);

		pan->SetBG(true);

		Combox->SetFont(font12);
		Combox->SetLocation(Vector2(20, 250));
		Combox->SetSize(Size(200, 32));

		Combox->AddItem("1 banana");
		Combox->AddItem("2 jellyfish");
		Combox->AddItem("3 banana");
		Combox->AddItem("4 jellyfish");
		Combox->AddItem("5 banana");
		Combox->AddItem("6 jellyfish");
		Combox->AddItem("7 banana");
		Combox->AddItem("8 jellyfish");
		Combox->AddItem("9 banana");
		Combox->AddItem("10 jellyfish");

		Controls.push_back(vbar);
		Controls.push_back(pan);

		time.SetInterval(120);
		time.Start();
	}

	virtual void Update() override
	{
		static int v = 100;
		if (time.TimerHitR())
			v++;

		if (v > 100)
			v = 0;

		bar->SetValue(v);

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
	TheSDLScreenHandeler::Pointer()->SetBackBufferColor(Color(100, 149, 237, 255));
	TheSDLGameStateManager::Pointer()->SetState(TheTestState::Pointer());
	TheSDLGameStateManager::Pointer()->Run();

	return 0;
}