#pragma once

#include "SDL_SpriteFont.h"

class SDL_TTFFont: public SDL_SpriteFont
{
	std::string m_FileName;

	bool RenderFont();

public:

	void SetSize(int size);
	bool Load(std::string TTFfont);
};

