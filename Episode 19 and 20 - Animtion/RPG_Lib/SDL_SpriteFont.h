#pragma once

#include "SDL_Image.h"
#include "IFont.h"
#include "XML.h"

class SDL_SpriteFont : public IFont, public SDL_Image
{
	XML* m_XMLDocument;
	std::string m_ImageFile;

	using SDL_Image::Draw;

public:
	virtual bool Load(const std::string& XMLFile) override;
	bool Load(XML* priteFontFile);

	virtual SizeF MeasureString(const std::string text) override;
	virtual void DrawString(const std::string& string, Vector2F location) override;
	virtual void DrawString(const std::string& string, RectangleF location) override;
};