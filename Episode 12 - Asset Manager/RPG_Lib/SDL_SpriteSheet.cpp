#include "SDL_SpriteSheet.h"

#include "SDL_ScreenHandeler.h"
#include <SDL.h>

void SDL_SpriteSheet::SetCellSize(Size CellSize)
{
	m_CellSize = CellSize;
	m_CellsXY.X = (m_TextureSize.Width / m_CellSize.Width);
	m_CellsXY.Y = (m_TextureSize.Height / m_CellSize.Height);
}

int SDL_SpriteSheet::GetCellWidth()
{
	return m_CellSize.Width;
}

int SDL_SpriteSheet::GetCellHeight()
{
	return m_CellSize.Height;
}

SDL_Rect SDL_SpriteSheet::TranslateCell(const int Cell)
{
	SDL_Rect res;
	res.x = m_CellSize.Width * (Cell % m_CellsXY.X);
	res.y = m_CellSize.Height * (Cell / m_CellsXY.Y);
	res.w = m_CellSize.Width;
	res.h = m_CellSize.Height;
	return res;
}

bool SDL_SpriteSheet::Load(const std::string & file)
{
	bool res = SDL_Image::Load(file);
	//SetCellSize(cellSize);
	return res;
}

void SDL_SpriteSheet::Draw(const int cell, const Vector2 & location)
{
	if (cell < 0 || cell > (m_CellsXY.X * m_CellsXY.Y))
		printf("Attempting to draw an unknown cell number : %i.\n", cell);

	SDL_Rect source = TranslateCell(cell);

	SDL_Rect destination;
	destination.x = location.X;
	destination.y = location.Y;
	destination.w = source.w;
	destination.h = source.h;

	SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(),
		m_Texture,
		&source,
		&destination);
}
