#pragma once

#include "Size.h"
#include "Rectangle2D.h"
#include "SDL_Image.h"
//#include <SDL.h>
struct SDL_Rect;

class SDL_SpriteSheet : public SDL_Image
{
	Size m_CellSize;

public:
	void SetCellSize(Size CellSize);
	int GetCellWidth();
	int GetCellHeight();

	SDL_Rect TranslateCell(const int cell);
	bool Load(const std::string& file, const Size& cellSize);
	void Draw(const int cell, const Vector2& location);
};