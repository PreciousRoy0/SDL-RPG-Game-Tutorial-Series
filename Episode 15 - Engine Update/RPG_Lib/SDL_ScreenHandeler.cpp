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

void SDL_ScreenHandeler::SetBackBufferColor(std::string& HexColor)
{
	Color c = ColorHexToRGB(HexColor);
	SetBackBufferColor(c);
}

void SDL_ScreenHandeler::SetBackBufferColor(const Color & color)
{
	m_BackBufferColor = color;
	SetBackBufferColor(color.R, color.G, color.B, color.A);
}

void SDL_ScreenHandeler::SetBackBufferColor(int r, int g, int b, int a)
{
	m_BackBufferColor.R = r;
	m_BackBufferColor.G = g;
	m_BackBufferColor.B = b;
	m_BackBufferColor.A = a;

	SDL_SetRenderDrawColor(m_Renderer, r, g, b, 0);
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

void SDL_ScreenHandeler::DrawRect(Rectangle rect, Color color)
{
	SetBackBufferColor(color);
	SDL_Rect r
	{
		rect.X,
		rect.Y,
		rect.Width,
		rect.Height
	};
	int error = SDL_RenderDrawRect(m_Renderer, &r);

	if (error < 0)
		throw "failed to draw rect";

	SetBackBufferColor(m_BackBufferColor);
}

SDL_ScreenHandeler::~SDL_ScreenHandeler()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}
