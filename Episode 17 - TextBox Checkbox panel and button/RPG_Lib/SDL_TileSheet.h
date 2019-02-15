#pragma once

#include <vector>
#include "Size.h"
#include "Rectangle2D.h"
#include "SDL_Image.h"
#include "IAsset.h"
//#include <SDL.h>
struct SDL_Rect;

class SDL_TileSheet : public SDL_Image
{
	std::vector<Rectangle> m_Rectangles;

	bool Calculated = false;

public:
	void CalculateCellSize(Size CellSize, int spacing);

	Rectangle TranslateCell(const int cell);
	virtual bool Load(const std::string& file) override; //, const Size& cellSize
	void Draw(const int cell, const Vector2F& location);
	void Draw(const int Cell, const RectangleF& Destenation);
};