#include "SDL_SpriteFont.h"
#include "SDL_ScreenHandeler.h"
#include <SDL.h>

#include "AssetManager.h"

bool SDL_SpriteFont::Load(XML* priteFontFile)
{
	if (!priteFontFile)
		return false;

	m_XMLDocument = priteFontFile;

	xml_node<>* rootnode = m_XMLDocument->GetDocument()->first_node("BitmapFont");

	for (xml_attribute<>* at = rootnode->first_attribute(); at; at = at->next_attribute())
	{
		std::string name = at->name();

		if (name == "SpriteSheet")
			m_ImageFile = at->value();
		else if (name == "FontSize")
			m_Size = atoi(at->value());
	}

	if (SDL_Image::Load(m_ImageFile))
		return true;

	for (xml_node<>* n = rootnode->first_node("Letter"); n; n = n->next_sibling())
	{
		char letter = ' ';
		RectangleF rect;

		for (xml_attribute<>* at = n->first_attribute(); at; at = at->next_attribute())
		{
			std::string name = at->name();
			std::string value = at->value();

			if (name == "Char")
				letter = value[0];
			if (name == "X")
				rect.X = (float)atof(value.c_str());
			if (name == "Y")
				rect.Y = (float)atof(value.c_str());
			if (name == "Width")
				rect.Width = (float)atof(value.c_str());
			if (name == "Height")
				rect.Height = (float)atof(value.c_str());
		}

		m_Charecters[letter] = rect;
	}

	return false;
}

bool SDL_SpriteFont::Load(const std::string& XMLFile)
{
	bool res = TheAssetManager::Pointer()->LoadAsset<XML>(XMLFile);
	if (res)
		return true;

	XML* asset = TheAssetManager::Pointer()->GetAsset<XML>(XMLFile);
	res = Load(asset);

	return res;
}

void SDL_SpriteFont::DrawString(std::string string, Vector2 location)
{
	Vector2F loc = location;
	for (unsigned int i = 0; i < string.size(); i++)
	{
		RectangleF letter = m_Charecters[string[i]];
		SDL_Rect source
		{
			(int)letter.X,
			(int)letter.Y,
			(int)letter.Width,
			(int)letter.Height
		};

		SDL_Rect destination;
		destination.x = (int)loc.X;
		destination.y = (int)loc.Y;
		destination.w = source.w;
		destination.h = source.h;

		SDL_RenderCopy(TheSDLScreenHandeler::Pointer()->GetRenderer(),
			m_Texture,
			&source,
			&destination);

		loc.X += letter.Width;
	}
}
