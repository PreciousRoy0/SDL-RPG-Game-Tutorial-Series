#pragma once

#include "SDL_Image.h"
#include "IFont.h"
#include "XML.h"

class SDL_SpriteFont : public IFont, protected SDL_Image
{
	XML* m_XMLDocument;
	std::string m_ImageFile;

	using SDL_Image::Draw;

public:
	bool Load(XML* priteFontFile);

	virtual void DrawString(std::string string, Vector2 location) override;
};