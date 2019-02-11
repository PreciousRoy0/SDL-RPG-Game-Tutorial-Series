#pragma once

#include <map>
#include "XML.h"
#include "Size.h"
#include "Rectangle2D.h"
#include "SDL_Image.h"
#include "IAsset.h"
//#include <SDL.h>
struct SDL_Rect;

class SDL_SpriteSheet : public SDL_Image
{
	XML* m_XMLDocument;
	std::map<std::string, Rectangle> m_Sprites;

	bool Load(XML* priteFontFile);

public:

	virtual bool Load(const std::string& xmlfile) override;
	void Draw(const std::string& sprite, const Vector2& location);
};