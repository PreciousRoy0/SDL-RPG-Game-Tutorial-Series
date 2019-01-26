#pragma once

#include "Size.h"
#include "Rectangle2D.h"
#include "SDL_Image.h"
#include "IAsset.h"
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
	virtual bool Load(const std::string& file) override; //, const Size& cellSize
	void Draw(const int cell, const Vector2& location);
};