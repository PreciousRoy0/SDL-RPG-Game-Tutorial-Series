#include "SDL_TileSheet.h"

#include "SDL_ScreenHandeler.h"
#include <SDL.h>

void SDL_TileSheet::CalculateCellSize(Size CellSize, int spacing)
{
	if (Calculated) //we only want to do this once
		return;

	int columns = ((m_TextureSize.Width - CellSize.Width) / (CellSize.Width + spacing)) + 1;
	int rows = ((m_TextureSize.Height - CellSize.Height) / (CellSize.Height + spacing)) + 1;


	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < columns; c++)
		{
			Rectangle rect;

			rect.X = c * (CellSize.Width + spacing);
			rect.Y = r * (CellSize.Height + spacing);

			rect.Width = CellSize.Width;
			rect.Height = CellSize.Height;

			m_Rectangles.push_back(rect);
		}
	}

	Calculated = true;
}

Rectangle SDL_TileSheet::TranslateCell(const int Cell)
{
	if (Cell > (int)m_Rectangles.size())
	{
		printf("Requesting a SDL_TileSheet cell that is out of bounds: %i\n", Cell);
		return Rectangle();
	}

	return m_Rectangles[Cell];
}

bool SDL_TileSheet::Load(const std::string & file)
{
	bool res = SDL_Image::Load(file);
	return res;
}

void SDL_TileSheet::Draw(const int cell, const Vector2F& location)
{
	if (m_Rectangles.size() > 0)
	{
		RectangleF source;
		source = m_Rectangles[cell];

		RectangleF destination;
		destination.X = location.X;
		destination.Y = location.Y;
		destination.Width = source.Width;
		destination.Height = source.Height;

		SDL_Image::Draw(source, destination);
	}
}

void SDL_TileSheet::Draw(const int Cell, const RectangleF& Destenation)
{
	if (m_Rectangles.size() > 0)
	{
		RectangleF source;
		source = m_Rectangles[Cell];

		SDL_Image::Draw(source, Destenation);
	}
}