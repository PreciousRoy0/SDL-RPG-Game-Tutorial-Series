#pragma once

#include <SDL.h>
#include <string>
#include "Singleton.h"
#include "Size.h"
#include "Color.h"
#include "Rectangle2D.h"

class SDL_ScreenHandeler : public UnCopyable
{
	friend class Singleton<SDL_ScreenHandeler>;
	SDL_ScreenHandeler() {}

	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	Color m_BackBufferColor;

public:

	bool Initialize(std::string windowName, Size windowSize);
	void SetBackBufferColor(std::string& HexColor);
	void SetBackBufferColor(const Color& color);
	void SetBackBufferColor(int r, int g, int b, int a);
	void Flip();

	SDL_Renderer* GetRenderer();

	//helper
	void DrawRect(Rectangle rect, Color color);

	~SDL_ScreenHandeler();
};

typedef Singleton<SDL_ScreenHandeler> TheSDLScreenHandeler;