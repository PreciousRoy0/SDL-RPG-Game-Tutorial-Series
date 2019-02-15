#pragma once

#include "SDL_SpriteFont.h"
#include "IAsset.h"

class SDL_TTFFont: public SDL_SpriteFont
{
	std::string m_FileName;

	bool RenderFont();

public:

	void SetSize(int size);
	virtual bool Load(const std::string& TTFfont) override;

};

