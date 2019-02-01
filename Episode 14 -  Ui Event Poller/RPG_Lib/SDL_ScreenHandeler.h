#pragma once

#include <SDL.h>
#include <string>
#include "Singleton.h"
#include "Size.h"

class SDL_ScreenHandeler : public UnCopyable
{
	friend class Singleton<SDL_ScreenHandeler>;
	SDL_ScreenHandeler() {}

	SDL_Window* m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;

	SDL_Color m_BackBufferColor;

public:

	bool Initialize(std::string windowName, Size windowSize);
	void SetBackBufferColor(SDL_Color color);
	void Flip();

	SDL_Renderer* GetRenderer();

	~SDL_ScreenHandeler();
};

typedef Singleton<SDL_ScreenHandeler> TheSDLScreenHandeler;