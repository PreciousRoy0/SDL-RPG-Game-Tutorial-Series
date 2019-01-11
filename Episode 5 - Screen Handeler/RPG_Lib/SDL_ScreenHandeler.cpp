#include "SDL_ScreenHandeler.h"

bool SDL_ScreenHandeler::Initialize(std::string windowName, Size windowSize)
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		// Unrecoverable error, exit here.
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return true;
	}

	m_Window = SDL_CreateWindow(windowName.c_str(), 10, 100, windowSize.Width, windowSize.Height, 0);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderClear(m_Renderer);

	return false;
}

void SDL_ScreenHandeler::SetBackBufferColor(SDL_Color color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}

void SDL_ScreenHandeler::Flip()
{
	
	SDL_RenderPresent(m_Renderer);
	SDL_RenderClear(m_Renderer);
}

SDL_Renderer* SDL_ScreenHandeler::GetRenderer()
{
	return m_Renderer;
}

SDL_ScreenHandeler::~SDL_ScreenHandeler()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}
